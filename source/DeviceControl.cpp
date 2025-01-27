#include <iostream>
#include <thread>
#include <chrono>

#include "DeviceControl.h"
#include "MachineController.h"
#include "EmergencyStop.h"


/**
 * @brief 核心設備控制的無限迴圈函式。
 *
 * 透過 `runDeviceControl()`，系統會不斷地檢查以下狀態：
 *   1. **急停 (EmergencyStop)**：若偵測到 `Input::EmergencyStop == true`，則先確保已切換至復歸模式 (X13)，
 *      再呼叫 `emergencyStop.handleReset()` 進行復歸流程。
 *   2. **復歸模式 (ModeSwitch_Left)**：若偵測到復歸模式，則將 `currentMode` 設定為 "Reset"，
 *      並在模式發生變化時呼叫 `handleReset()`，將設備回到原點。
 *   3. **工作模式 (ModeSwitch_Right)**：若偵測到工作模式，根據手動/連續/單一循環來設定 `currentMode`，
 *      並在模式改變時呼叫對應的 `runManual()`、`runContinuous()` 或 `runSingle()`。
 *   4. **模式未改變時的特殊處理**：
 *      - 對於單一循環模式，若先前已執行完成 (`isCycleRunning() == false`)，可再次啟動新的單一循環。
 *
 * 流程說明：
 *   - 使用者於外部 UI 切換模式時，系統會在本函式的 while 迴圈中檢測到，
 *     並立即呼叫相應的函式執行後續動作 (例如 `machineCtrl.runManual()`)。
 *   - 若發生急停，則跳過後續模式判斷，優先處理復歸，確保安全。
 *   - 為避免佔用過多 CPU，最後以 `std::this_thread::sleep_for(...)` 做短暫延遲再重複檢查。
 *
 * @param ioMap      共享的 IOMap，用以讀/寫輸入輸出狀態。
 * @param machineCtrl 機器控制器，內含手動、單一循環、連續循環等模式實作。
 *
 * @note 每次迴圈都使用 `previousMode` 與 `currentMode` 來判斷模式是否改變，
 *       若改變才執行對應動作，避免重複進入同一模式。
 */
void runDeviceControl(IOMap& ioMap, MachineController& machineCtrl) {

    // 使用傳遞進來的 MachineController 實例
    EmergencyStop emergencyStop(ioMap);
    std::string previousMode = "Idle"; // 上次模式
    std::string currentMode = "Idle";  // 目前模式

    // 進入系統循環
    while (true) {
        // -----------------------------------------------------
        // (1) 檢查急停狀態
        // -----------------------------------------------------
        if (ioMap.readInput(Input::EmergencyStop)) {
            std::cerr << "[DEBUG] Emergency stop triggered!" << std::endl;

            // 做完停機動作之後
            // ioMap.setInputState(Input::EmergencyStop, false);

            // 須切換到復歸模式 (X13)
            if (!ioMap.readInput(Input::ModeSwitch_Left)) {
                std::cerr << "[ERROR] ModeSwitch is not in Reset Mode. Please switch to Reset Mode." << std::endl;
                // 回到最外層 while 重新檢查
                continue;
            }

            // 執行復歸邏輯
            std::cout << "[DEBUG] Emergency stop released. Resetting system..." << std::endl;
            emergencyStop.handleReset();
        }

        // -----------------------------------------------------
        // (2) 檢查復歸狀態
        // -----------------------------------------------------
        else if (ioMap.readInput(Input::ModeSwitch_Left)){

            currentMode = "Reset";

            // 復歸模式
            if (currentMode != previousMode) {
                previousMode = currentMode;
                std::cout << "Switch to Reset => calling handleReset()" << std::endl;

                // 做完復歸動作之後
                // ioMap.setInputState(Input::ModeSwitch_Left, false);

                emergencyStop.handleReset();
            }
            else {
                // 已經在 Reset
            }
        }

        // -----------------------------------------------------
        // (3) 檢查工作模式選擇
        // -----------------------------------------------------
        else if (ioMap.readInput(Input::ModeSwitch_Right)) {

            // 根據手動/連續/單一的開關來確定目前模式
            if (ioMap.readInput(Input::ModeSwitch_Manual)) {
                currentMode = "Manual"; // 執行手動模式
            }
            else if (ioMap.readInput(Input::ModeSwitch_Continuous)) {
                currentMode = "Continuous"; // 執行連續循環流程
            }
            else if (ioMap.readInput(Input::ModeSwitch_SingleCycle)) {
                currentMode = "SingleCycle"; // 執行單一循環流程
            }
            else {
                currentMode = "NoMode"; // 還沒選擇任何模式
            }

            // 如果模式與之前不同 -> 呼叫對應函式
            if (currentMode != previousMode) {
                previousMode = currentMode;

                if (currentMode == "Manual") {
                    std::cout << "[DEBUG] System is in Manual Mode. Waiting for manual control..." << std::endl;
                    machineCtrl.runManual();
                }
                else if (currentMode == "Continuous") {
                    std::cout << "[DEBUG] System is in Continuous Cycle Mode. Running process..." << std::endl;
                    machineCtrl.runContinuous();
                }
                else if (currentMode == "SingleCycle") {
                    std::cout << "[DEBUG] System is in Single Cycle Mode. Running process..." << std::endl;
                    machineCtrl.runSingle();
                }
                else {
                    std::cout << "[DEBUG] No mode selected yet. Waiting for user to choose a mode..." << std::endl;
                }
            }
            else { // 模式未改變
                // SingleCycle 模式下，若還沒開始或流程結束，可以重複啟動
                if (currentMode == "SingleCycle" && !machineCtrl.isCycleRunning()) {
                    std::cout << "[DEBUG] Mode: Single Cycle. Starting a new cycle..." << std::endl;
                    machineCtrl.runSingle();
                }
            }
        }
        else {
            // 未選擇任何模式 => idle
            std::cout << "[DEBUG] No mode selected. System is idle." << std::endl;
        }
        // 防止 CPU 過度使用 => sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

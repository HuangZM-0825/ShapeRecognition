#include <iostream>
#include <thread>
#include <chrono>

#include "DeviceControl.h"
#include "MachineController.h"
#include "EmergencyStop.h"

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

#include "EmergencyStop.h"

EmergencyStop::EmergencyStop(IOMap& ioMap) : ioMap(ioMap) {}

void EmergencyStop::handleReset() {
    std::cout << "[RESET] Starting system reset..." << std::endl;
    resetCompleted = false;

    // -----------------------------
    // Step 1: 確認已在復歸模式 (X13)
    // Step 2: 不允許在手動模式 (X15)
    // -----------------------------
    while (true) {
        if (!ioMap.readInput(Input::ModeSwitch_Left)) {
            // 需要在復歸模式
            std::cerr << "[RESET] Error: Not in Reset Mode (X13 == false). "
                << "Please switch to Reset Mode..." << std::endl;
            return;
        }
        else if (ioMap.readInput(Input::ModeSwitch_Manual)) {
            // 不能在手動模式
            std::cerr << "[RESET] Error: System is in Manual Mode (X15 == true). "
                << "Reset not allowed. Please switch off Manual Mode..." << std::endl;
            continue;
        }
        else {
            // 條件都符合，可以進入下一步
            std::cout << "[RESET] Good! Now in Reset Mode & not in Manual. Proceed..." << std::endl;
            break; // 跳出這個 while
        }

        // 若還沒符合 => 等待一小段時間後再檢查
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // -----------------------------
    // Step 3: 等待 StartReset (X20) 按鈕
    // -----------------------------
    std::cout << "Waiting for StartReset button to be pressed..." << std::endl;
    while (!ioMap.readInput(Input::StartReset)) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 等待 StartReset
    }

    std::cout << "StartReset button pressed. Beginning reset process..." << std::endl;

    // Step 4: 開始閃爍復歸燈
    std::thread yellowLightBlinker([this]() {
        while (!resetCompleted) { // 當復歸未完成時持續閃爍
            ioMap.writeOutput(Output::YellowLight, true);
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 黃燈亮 0.5 秒
            ioMap.writeOutput(Output::YellowLight, false);
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 黃燈滅 0.5 秒
        }
        });

    // Step 5: 垂直缸上升，確認感測器狀態
    std::cout << "Raising cylinder to up position..." << std::endl;
    ioMap.writeOutput(Output::CylinderDown, false); // 停止下降
    ioMap.setInputState(Input::CylinderDownLimit, false); // 模擬下限感測器未觸發
    ioMap.setInputState(Input::CylinderUpLimit, true);    // 模擬上限感測器觸發
    delay(1000); // 模擬垂直缸上升過程

    // Step 6: 執行氣壓夾爪釋放
    std::cout << "Releasing gripper (B-)..." << std::endl;
    ioMap.writeOutput(Output::GripperOpen, true); // 執行 B-
    delay(1000); // 模擬 T4 計時 1 秒
    ioMap.writeOutput(Output::GripperOpen, false); // 停止 B-

    // Step 7: 龍門右移到初始位置
    std::cout << "Moving gantry arm to initial position (M2-)..." << std::endl;
    ioMap.writeOutput(Output::ArmMoveRight, true); // 啟動右移
    delay(3000); // 模擬移動

    ioMap.writeOutput(Output::ArmMoveRight, false); // 停止右移

    // 龍門手臂回到原點位置
    ioMap.setInputState(Input::ArmPosition, true);  // 龍門手臂原點位置

    // Step 8: 完成復歸，更新燈號
    resetCompleted = true; // 設置復歸完成狀態
    yellowLightBlinker.join(); // 等待黃燈閃爍線程結束
    ioMap.writeOutput(Output::YellowLight, false); // 確保黃燈熄滅
    ioMap.writeOutput(Output::GreenLight, true);   // 綠燈亮，完成復歸


    // Step 9: 按鈕訊號復歸，否則切回工作模式會自動啟動流程
    ioMap.setInputState(Input::StartReset, false);
    ioMap.setInputState(Input::EmergencyStop, false);
    ioMap.setInputState(Input::ModeSwitch_Left, false);

    std::cout << "System reset completed. System is ready." << std::endl;
}

// 模擬計時器的延遲
void EmergencyStop::delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

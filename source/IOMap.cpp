#include "IOMap.h"
#include <iostream>

IOMap::IOMap() {
    // 初始化輸入點狀態（模擬）
    inputState[Input::CylinderDownLimit] = false;
    inputState[Input::CylinderUpLimit] = false;
    inputState[Input::MaterialSensor] = false;
    inputState[Input::ShapeCircleSensor] = false;
    inputState[Input::ArmPosition] = false;
    inputState[Input::CircleEjector] = false;
    inputState[Input::SquareEjector] = false;
    inputState[Input::ManualConveyor] = false;
    inputState[Input::ManualACylinder] = false;
    inputState[Input::ManualArmLeft] = false;
    inputState[Input::ManualArmRight] = false;
    inputState[Input::ModeSwitch_Left] = false;
    inputState[Input::ModeSwitch_Right] = false;
    inputState[Input::ModeSwitch_Manual] = false;
    inputState[Input::ModeSwitch_Continuous] = false;
    inputState[Input::ModeSwitch_SingleCycle] = false;
    inputState[Input::StartReset] = false;
    inputState[Input::EmergencyStop] = false;

    // 初始化輸出點狀態（模擬）
    outputState[Output::CylinderDown] = false;
    outputState[Output::ConveyorMotor] = false;
    outputState[Output::ArmMoveLeft] = false;
    outputState[Output::ArmMoveRight] = false;
    outputState[Output::GripperClose] = false;
    outputState[Output::GripperOpen] = false;
    outputState[Output::RedLight] = false;
    outputState[Output::YellowLight] = false;
    outputState[Output::GreenLight] = false;
}


/**
 * @brief 讀取指定輸入點的布林狀態 (true/false)。
 *
 * @param input 枚舉型別 Input，表示要讀取的輸入點位編號 (如 CylinderDownLimit、EmergencyStop 等)。
 * @return 若能在 inputState 查到該輸入點，則返回其狀態 (true/false)；若找不到，印出錯誤並返回 false。
 */
bool IOMap::readInput(Input input) {
    // 檢查是否能在 inputState 中找到指定的輸入點
    if (inputState.find(input) != inputState.end()) {
        // 如果找到該輸入點，返回它的狀態（true 或 false）
        return inputState[input];
    }
    else {
        // 如果找不到該輸入點，輸出錯誤信息，並返回 false
        std::cerr << "Input not found!" << std::endl;
        return false;
    }
}


/**
 * @brief 讀取指定輸出點的布林狀態 (true/false)。
 *
 * @param output 枚舉型別 Output，表示要讀取的輸出點位編號 (如 CylinderDown、GreenLight 等)。
 * @return 若能在 outputState 查到該輸出點，則返回其狀態 (true/false)；若找不到，預設返回 false。
 */
bool IOMap::readOutput(Output output) const {
    auto it = outputState.find(output);
    if (it != outputState.end()) {
        return it->second;  // 如果找到該輸出點，返回其狀態
    }
    return false;  // 預設為 false
}


/**
 * @brief 寫入指定輸出點的布林狀態 (true/false)。
 *
 * @param output 枚舉型別 Output，要設置的輸出點。
 * @param state 要設置的狀態 (true 表示 ON，false 表示 OFF)。
 *
 * 若成功找到對應的輸出點，則更新其狀態並印出提示；若找不到則印出錯誤。
 */
void IOMap::writeOutput(Output output, bool state) {
    // 檢查是否能在 outputState 中找到指定的輸出點
    if (outputState.find(output) != outputState.end()) {
        // 如果找到該輸出點，將它的狀態設為指定值（state）
        outputState[output] = state;
        // 輸出成功設置的提示信息
        std::cout << "Output " << static_cast<int>(output)
            << " set to " << (state ? "ON" : "OFF") << std::endl;
    }
    else {
        // 如果找不到該輸出點，輸出錯誤信息
        std::cerr << "Output not found!" << std::endl;
    }
}


/**
 * @brief 更新指定輸入點的布林狀態 (true/false)。
 *
 * @param input 枚舉型別 Input，要更新的輸入點。
 * @param state 新的狀態 (true/false)。
 *
 * 若能在 inputState 找到該輸入點，則更新其狀態；否則印出錯誤訊息。
 */
void IOMap::setInputState(Input input, bool state) {
    if (inputState.find(input) != inputState.end()) { // 確保感測器存在
        inputState[input] = state; // 更新狀態
    }
    else {
        std::cerr << "Error: Input " << static_cast<int>(input) << " not found in IOMap!" << std::endl;
    }
}

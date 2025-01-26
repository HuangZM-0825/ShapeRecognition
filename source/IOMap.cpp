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


bool IOMap::readOutput(Output output) const {
    auto it = outputState.find(output);
    if (it != outputState.end()) {
        return it->second;  // 如果找到該輸出點，返回其狀態
    }
    return false;  // 預設為 false
}


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


void IOMap::setInputState(Input input, bool state) {
    if (inputState.find(input) != inputState.end()) { // 確保感測器存在
        inputState[input] = state; // 更新狀態
    }
    else {
        std::cerr << "Error: Input " << static_cast<int>(input) << " not found in IOMap!" << std::endl;
    }
}

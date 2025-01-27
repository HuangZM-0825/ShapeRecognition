#include "IOMap.h"
#include <iostream>

IOMap::IOMap() {
    // ��l�ƿ�J�I���A�]�����^
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

    // ��l�ƿ�X�I���A�]�����^
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
 * @brief Ū�����w��J�I�����L���A (true/false)�C
 *
 * @param input �T�|���O Input�A��ܭnŪ������J�I��s�� (�p CylinderDownLimit�BEmergencyStop ��)�C
 * @return �Y��b inputState �d��ӿ�J�I�A�h��^�䪬�A (true/false)�F�Y�䤣��A�L�X���~�ê�^ false�C
 */
bool IOMap::readInput(Input input) {
    // �ˬd�O�_��b inputState �������w����J�I
    if (inputState.find(input) != inputState.end()) {
        // �p�G���ӿ�J�I�A��^�������A�]true �� false�^
        return inputState[input];
    }
    else {
        // �p�G�䤣��ӿ�J�I�A��X���~�H���A�ê�^ false
        std::cerr << "Input not found!" << std::endl;
        return false;
    }
}


/**
 * @brief Ū�����w��X�I�����L���A (true/false)�C
 *
 * @param output �T�|���O Output�A��ܭnŪ������X�I��s�� (�p CylinderDown�BGreenLight ��)�C
 * @return �Y��b outputState �d��ӿ�X�I�A�h��^�䪬�A (true/false)�F�Y�䤣��A�w�]��^ false�C
 */
bool IOMap::readOutput(Output output) const {
    auto it = outputState.find(output);
    if (it != outputState.end()) {
        return it->second;  // �p�G���ӿ�X�I�A��^�䪬�A
    }
    return false;  // �w�]�� false
}


/**
 * @brief �g�J���w��X�I�����L���A (true/false)�C
 *
 * @param output �T�|���O Output�A�n�]�m����X�I�C
 * @param state �n�]�m�����A (true ��� ON�Afalse ��� OFF)�C
 *
 * �Y���\����������X�I�A�h��s�䪬�A�æL�X���ܡF�Y�䤣��h�L�X���~�C
 */
void IOMap::writeOutput(Output output, bool state) {
    // �ˬd�O�_��b outputState �������w����X�I
    if (outputState.find(output) != outputState.end()) {
        // �p�G���ӿ�X�I�A�N�������A�]�����w�ȡ]state�^
        outputState[output] = state;
        // ��X���\�]�m�����ܫH��
        std::cout << "Output " << static_cast<int>(output)
            << " set to " << (state ? "ON" : "OFF") << std::endl;
    }
    else {
        // �p�G�䤣��ӿ�X�I�A��X���~�H��
        std::cerr << "Output not found!" << std::endl;
    }
}


/**
 * @brief ��s���w��J�I�����L���A (true/false)�C
 *
 * @param input �T�|���O Input�A�n��s����J�I�C
 * @param state �s�����A (true/false)�C
 *
 * �Y��b inputState ���ӿ�J�I�A�h��s�䪬�A�F�_�h�L�X���~�T���C
 */
void IOMap::setInputState(Input input, bool state) {
    if (inputState.find(input) != inputState.end()) { // �T�O�P�����s�b
        inputState[input] = state; // ��s���A
    }
    else {
        std::cerr << "Error: Input " << static_cast<int>(input) << " not found in IOMap!" << std::endl;
    }
}

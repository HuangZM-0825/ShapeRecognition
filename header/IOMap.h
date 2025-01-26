#ifndef IOMAP_H
#define IOMAP_H

#include <unordered_map>
#include <string>

enum class Input {
    CylinderDownLimit,  // X0
    CylinderUpLimit,    // X1
    MaterialSensor,     // X2
    ShapeCircleSensor,  // X3 true == ��� / false == ���
    ArmPosition,        // X4
    CircleEjector,      // X5
    SquareEjector,      // X6
    ManualConveyor,     // X7
    ManualACylinder,    // X10
    ManualArmLeft,      // X11
    ManualArmRight,     // X12
    ModeSwitch_Left,        // X13 true == �_�k�Ҧ�
    ModeSwitch_Right,       // X14 true == �u�@�Ҧ�
    ModeSwitch_Manual,      // X15 true == ��ʾޱ�
    ModeSwitch_Continuous,  // X16 true == �s��`��
    ModeSwitch_SingleCycle, // X17 true == ��@�`��
    StartReset,         // X20
    EmergencyStop       // X21
};

enum class Output {
    CylinderDown,       // Y0
    ConveyorMotor,      // Y2
    ArmMoveLeft,        // Y4
    ArmMoveRight,       // Y5
    GripperClose,       // Y6
    GripperOpen,        // Y7
    RedLight,           // Y15
    YellowLight,        // Y16
    GreenLight          // Y17
};


class IOMap {
public:
    IOMap(); // Constructor

    // Input �M Output �O��ȡA�ӫD�����ާ@����H�C
    bool readInput(Input input);            // Ū����J�I�쪬�A�A�äϬM�b UI �W�C
    bool readOutput(Output output) const;   // Ū����X�I�쪬�A�A�äϬM�b UI �W�C
    void writeOutput(Output output, bool state); // �]�m��X�I�쪬�A
    void setInputState(Input input, bool state); // �ק� Input ���A
    
private:
    // �ާ@����ڼƾڨӦ� Input �M Output�A�o�O��l�ƫ᪺�ƾڵ��c�C
    std::unordered_map<Input, bool> inputState;   // ������J�I���A
    std::unordered_map<Output, bool> outputState; // ������X�I���A
};

#endif // IOMAP_H

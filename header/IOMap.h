#ifndef IOMAP_H
#define IOMAP_H

#include <unordered_map>
#include <string>

enum class Input {
    CylinderDownLimit,  // X0
    CylinderUpLimit,    // X1
    MaterialSensor,     // X2
    ShapeCircleSensor,  // X3 true == 圓料 / false == 方料
    ArmPosition,        // X4
    CircleEjector,      // X5
    SquareEjector,      // X6
    ManualConveyor,     // X7
    ManualACylinder,    // X10
    ManualArmLeft,      // X11
    ManualArmRight,     // X12
    ModeSwitch_Left,        // X13 true == 復歸模式
    ModeSwitch_Right,       // X14 true == 工作模式
    ModeSwitch_Manual,      // X15 true == 手動操控
    ModeSwitch_Continuous,  // X16 true == 連續循環
    ModeSwitch_SingleCycle, // X17 true == 單一循環
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

    // Input 和 Output 是鍵值，而非直接操作的對象。
    bool readInput(Input input);            // 讀取輸入點位狀態，並反映在 UI 上。
    bool readOutput(Output output) const;   // 讀取輸出點位狀態，並反映在 UI 上。
    void writeOutput(Output output, bool state); // 設置輸出點位狀態
    void setInputState(Input input, bool state); // 修改 Input 狀態
    
private:
    // 操作的實際數據來自 Input 和 Output，這是初始化後的數據結構。
    std::unordered_map<Input, bool> inputState;   // 模擬輸入點狀態
    std::unordered_map<Output, bool> outputState; // 模擬輸出點狀態
};

#endif // IOMAP_H

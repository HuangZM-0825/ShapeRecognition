#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <QButtonGroup>


// 建構子：接收同一個 IOMap & 與 MachineController &
// 這表示沒有在 MainWindow 內部自行建構新的 IOMap 或 MachineController，而是使用外部傳進來的「同一個物件」，用參考（&）存起來。
MainWindow::MainWindow(IOMap& ioRef, MachineController& mCtrl, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ioMap(ioRef)
    , machineCtrl(mCtrl)
{
    ui->setupUi(this);
    // 手動呼叫
    // 否則，使用者在 UI 上勾選 CheckBox 或按下 PushButton 時，不會真正更新到 ioMap 的狀態。
    setupConnections();

    // 建立一個 QTimer，每 100ms 呼叫一次 updateIOStatus()
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateIOStatus);
    timer->start(100); // 100 毫秒

    // 先更新一次
    updateIOStatus(); // 信號槽連結
    updateCounts(machineCtrl.getCircleCount(), machineCtrl.getSquareCount()); // 顯示計數器
}


MainWindow::~MainWindow()
{
    delete ui;
}


// <三色燈> 單一 Label / 單一 bool 用的三色樣式切換
void MainWindow::updateLightStatus(QLabel* label, bool lightOn,
    const QString& onStyle,
    const QString& offStyle)
{
    label->setStyleSheet(lightOn ? onStyle : offStyle);
}
static const QString triColorDefaultStyle =
"background-color: lightgray; border: 1px solid black; border-radius: 5px; color: darkblue; font-size: 10px; font-weight: bold; padding: 5px;";
static const QString redLightStyle =
"background-color: red; border: 1px solid black; border-radius: 5px; color: darkblue; font-size: 10px; font-weight: bold; padding: 5px;";
static const QString yellowLightStyle =
"background-color: yellow; border: 1px solid black; border-radius: 5px; color: darkblue; font-size: 10px; font-weight: bold; padding: 5px;";
static const QString greenLightStyle =
"background-color: green; border: 1px solid black; border-radius: 5px; color: darkblue; font-size: 10px; font-weight: bold; padding: 5px;";


// 新增信號槽連結方法
void MainWindow::setupConnections()
{
   // -----------------------------------------------------
   // 使用 QButtonGroup 手動分組，使成為「互不干擾的獨立群組」。
   // groupA 「第一組」: radioButton_Rst, radioButton_Work
   // groupB 「第一組」: radioButton_Continuous, radioButton_Manual, radioButton_SingleCycle
   // -----------------------------------------------------
    QButtonGroup* groupA = new QButtonGroup(this);
    groupA->addButton(ui->radioButton_Rst);
    groupA->addButton(ui->radioButton_Work);

    QButtonGroup* groupB = new QButtonGroup(this);
    groupB->addButton(ui->radioButton_Continuous);
    groupB->addButton(ui->radioButton_Manual);
    groupB->addButton(ui->radioButton_SingleCycle);


    // 連結 radioButton 與 IOMap
    connect(ui->radioButton_Rst, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_Left, checked);
        if (checked) {
            // 取消其他模式
            ui->radioButton_Work->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Right, false);
        }
        });

    connect(ui->radioButton_Work, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_Right, checked);
        if (checked) {
            // 取消其他模式
            ui->radioButton_Rst->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Left, false);
        }
        });

    connect(ui->radioButton_SingleCycle, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_SingleCycle, checked);
        if (checked) {
            // 取消其他模式
            ui->radioButton_Manual->setChecked(false);
            ui->radioButton_Continuous->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Manual, false);
            ioMap.setInputState(Input::ModeSwitch_Continuous, false);
        }
    });

    connect(ui->radioButton_Continuous, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_Continuous, checked);
        if (checked) {
            // 取消其他模式
            ui->radioButton_Manual->setChecked(false);
            ui->radioButton_SingleCycle->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Manual, false);
            ioMap.setInputState(Input::ModeSwitch_SingleCycle, false);
        }
    });

    connect(ui->radioButton_Manual, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_Manual, checked);
        if (checked) {
            // 取消其他模式
            ui->radioButton_Continuous->setChecked(false);
            ui->radioButton_SingleCycle->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Continuous, false);
            ioMap.setInputState(Input::ModeSwitch_SingleCycle, false);
        }
    });

    // 連結 countsUpdated 信號到 updateCounts 槽
    connect(&machineCtrl, &MachineController::countsUpdated, this, &MainWindow::updateCounts);

    // 連結 pushButton 與 IOMap
    connect(ui->pushButton_St_Rst, &QPushButton::clicked, this, [this](bool checked) {
        ioMap.setInputState(Input::StartReset, true);
        if (checked) {
            // 取消其他模式
            ui->pushButton_EMS->setChecked(false);
            ioMap.setInputState(Input::EmergencyStop, false);
        }
        });

    connect(ui->pushButton_EMS, &QPushButton::clicked, this, [this](bool checked) {
        ioMap.setInputState(Input::EmergencyStop, true);
        if (checked) {
            // 取消其他模式
            ui->pushButton_St_Rst->setChecked(false); 
            ioMap.setInputState(Input::StartReset, false);
        }
        });

    // 連結 pushButton(手動) 與 IOMap
    connect(ui->pushButton_ManualACylinder, &QPushButton::pressed, this, [this]() {
        ioMap.setInputState(Input::ManualACylinder, true);
        });
    connect(ui->pushButton_ManualACylinder, &QPushButton::released, this, [this]() {
        ioMap.setInputState(Input::ManualACylinder, false);
        });

    connect(ui->pushButton_ManualArmLeft, &QPushButton::pressed, this, [this]() {
        ioMap.setInputState(Input::ManualArmLeft, true);
        });
    connect(ui->pushButton_ManualArmLeft, &QPushButton::released, this, [this]() {
        ioMap.setInputState(Input::ManualArmLeft, false);
        });

    connect(ui->pushButton_ManualArmRight, &QPushButton::pressed, this, [this]() {
        ioMap.setInputState(Input::ManualArmRight, true);
        });
    connect(ui->pushButton_ManualArmRight, &QPushButton::released, this, [this]() {
        ioMap.setInputState(Input::ManualArmRight, false);
        });

    connect(ui->pushButton_ManualConveyor, &QPushButton::pressed, this, [this]() {
        ioMap.setInputState(Input::ManualConveyor, true);
        });
    connect(ui->pushButton_ManualConveyor, &QPushButton::released, this, [this]() {
        ioMap.setInputState(Input::ManualConveyor, false);
        });


    // 連結 pushButton(圓、方料) 與 IOMap
    // 1. 按下「圓料 +1」按鈕
    connect(ui->pushButton_AddCircle, &QPushButton::clicked, this, [this]() {
        // machineController 是 MainWindow 擁有的一個物件或參考
        machineCtrl.setCircleCount(machineCtrl.getCircleCount() + 1);
        });

    // 2. 按下「圓料 -1」按鈕
    connect(ui->pushButton_SubCircle, &QPushButton::clicked, this, [this]() {
        int current = machineCtrl.getCircleCount();
        if (current > 0) {
            machineCtrl.setCircleCount(current - 1);
        }
        });

    // 3. 按下「方料 +1」按鈕
    connect(ui->pushButton_AddSquare, &QPushButton::clicked, this, [this]() {
        machineCtrl.setSquareCount(machineCtrl.getSquareCount() + 1);
        });

    // 4. 按下「方料 -1」按鈕
    connect(ui->pushButton_SubSquare, &QPushButton::clicked, this, [this]() {
        int current = machineCtrl.getSquareCount();
        if (current > 0) {
            machineCtrl.setSquareCount(current - 1);
        }
        });
}

// 更新 QLCDNumber
void MainWindow::updateCounts(int circleCount, int squareCount) 
{
    // 更新 QLCDNumber
    ui->lcdNumber_Circle->display(circleCount);
    ui->lcdNumber_Square->display(squareCount);
}

// 新增信號槽連結方法
void MainWindow::updateIOStatus()
{   
    // 輸入訊號
    // 使用 Input::CylinderDownLimit 作為鍵值，從 inputState 查找當前狀態
    // CylinderUpLimit
    updateLabelStatus(ui->label_a0, ioMap.readInput(Input::CylinderUpLimit));
    // CylinderDownLimit
    updateLabelStatus(ui->label_a1, ioMap.readInput(Input::CylinderDownLimit));
    // MaterialSensor
    updateLabelStatus(ui->label_s0, ioMap.readInput(Input::MaterialSensor));
    // ShapeCircleSensor
    updateLabelStatus(ui->label_s1, ioMap.readInput(Input::ShapeCircleSensor));
    // ArmPosition
    updateLabelStatus(ui->label_p0, ioMap.readInput(Input::ArmPosition));
    // CircleEjector
    updateLabelStatus(ui->label_p1, ioMap.readInput(Input::CircleEjector));
    // SquareEjector
    updateLabelStatus(ui->label_p2, ioMap.readInput(Input::SquareEjector));

    // 輸出訊號
    // CylinderDown
    updateLabelStatus(ui->label_A, ioMap.readOutput(Output::CylinderDown));
    // GripperOpen
    updateLabelStatus(ui->label_N_B, ioMap.readOutput(Output::GripperOpen));
    // GripperClose
    updateLabelStatus(ui->label_P_B, ioMap.readOutput(Output::GripperClose));
    // ConveyorMotor
    updateLabelStatus(ui->label_R1, ioMap.readOutput(Output::ConveyorMotor));
    // ArmMoveLeft
    updateLabelStatus(ui->label_R2, ioMap.readOutput(Output::ArmMoveLeft));
    // ArmMoveRight
    updateLabelStatus(ui->label_R3, ioMap.readOutput(Output::ArmMoveRight));

    // 三色燈，各自一個 Label、一個 bool
    updateLightStatus(ui->label_RL, ioMap.readOutput(Output::RedLight),
        redLightStyle, triColorDefaultStyle);
    updateLightStatus(ui->label_YL, ioMap.readOutput(Output::YellowLight),
        yellowLightStyle, triColorDefaultStyle);
    updateLightStatus(ui->label_GL, ioMap.readOutput(Output::GreenLight),
        greenLightStyle, triColorDefaultStyle);
}

// 更新 UI 的輸入/輸出的狀態，改變顏色
void MainWindow::updateLabelStatus(QLabel* label, bool status)
{
    const QString binaryActiveStyle =
        "background-color: green; "
        "border: 1px solid black; "
        "border-radius: 5px; "
        "color: darkblue; "
        "font-size: 10px; "
        "font-weight: bold; "
        "padding: 5px;"
        "text-align: center; "
        "min-width: 50px; "
        "min-height: 20px; ";

    const QString binaryDefaultStyle =
        "background-color: lightgray; "
        "border: 1px solid black; "
        "border-radius: 5px; "
        "color: darkblue; "
        "font-size: 10px; "
        "font-weight: bold; "
        "padding: 5px;"
        "text-align: center; "
        "min-width: 50px; "
        "min-height: 20px; ";

    label->setStyleSheet(status ? binaryActiveStyle : binaryDefaultStyle);
}

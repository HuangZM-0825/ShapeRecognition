#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <QButtonGroup>


// �غc�l�G�����P�@�� IOMap & �P MachineController &
// �o��ܨS���b MainWindow �����ۦ�غc�s�� IOMap �� MachineController�A�ӬO�ϥΥ~���Ƕi�Ӫ��u�P�@�Ӫ���v�A�ΰѦҡ]&�^�s�_�ӡC
MainWindow::MainWindow(IOMap& ioRef, MachineController& mCtrl, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ioMap(ioRef)
    , machineCtrl(mCtrl)
{
    ui->setupUi(this);
    // ��ʩI�s
    // �_�h�A�ϥΪ̦b UI �W�Ŀ� CheckBox �Ϋ��U PushButton �ɡA���|�u����s�� ioMap �����A�C
    setupConnections();

    // �إߤ@�� QTimer�A�C 100ms �I�s�@�� updateIOStatus()
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateIOStatus);
    timer->start(100); // 100 �@��

    // ����s�@��
    updateIOStatus(); // �H���ѳs��
    updateCounts(machineCtrl.getCircleCount(), machineCtrl.getSquareCount()); // ��ܭp�ƾ�
}


MainWindow::~MainWindow()
{
    delete ui;
}


// <�T��O> ��@ Label / ��@ bool �Ϊ��T��˦�����
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


// �s�W�H���ѳs����k
void MainWindow::setupConnections()
{
   // -----------------------------------------------------
   // �ϥ� QButtonGroup ��ʤ��աA�Ϧ����u�����z�Z���W�߸s�աv�C
   // groupA �u�Ĥ@�աv: radioButton_Rst, radioButton_Work
   // groupB �u�Ĥ@�աv: radioButton_Continuous, radioButton_Manual, radioButton_SingleCycle
   // -----------------------------------------------------
    QButtonGroup* groupA = new QButtonGroup(this);
    groupA->addButton(ui->radioButton_Rst);
    groupA->addButton(ui->radioButton_Work);

    QButtonGroup* groupB = new QButtonGroup(this);
    groupB->addButton(ui->radioButton_Continuous);
    groupB->addButton(ui->radioButton_Manual);
    groupB->addButton(ui->radioButton_SingleCycle);


    // �s�� radioButton �P IOMap
    connect(ui->radioButton_Rst, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_Left, checked);
        if (checked) {
            // ������L�Ҧ�
            ui->radioButton_Work->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Right, false);
        }
        });

    connect(ui->radioButton_Work, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_Right, checked);
        if (checked) {
            // ������L�Ҧ�
            ui->radioButton_Rst->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Left, false);
        }
        });

    connect(ui->radioButton_SingleCycle, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_SingleCycle, checked);
        if (checked) {
            // ������L�Ҧ�
            ui->radioButton_Manual->setChecked(false);
            ui->radioButton_Continuous->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Manual, false);
            ioMap.setInputState(Input::ModeSwitch_Continuous, false);
        }
    });

    connect(ui->radioButton_Continuous, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_Continuous, checked);
        if (checked) {
            // ������L�Ҧ�
            ui->radioButton_Manual->setChecked(false);
            ui->radioButton_SingleCycle->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Manual, false);
            ioMap.setInputState(Input::ModeSwitch_SingleCycle, false);
        }
    });

    connect(ui->radioButton_Manual, &QRadioButton::toggled, this, [this](bool checked) {
        ioMap.setInputState(Input::ModeSwitch_Manual, checked);
        if (checked) {
            // ������L�Ҧ�
            ui->radioButton_Continuous->setChecked(false);
            ui->radioButton_SingleCycle->setChecked(false);
            ioMap.setInputState(Input::ModeSwitch_Continuous, false);
            ioMap.setInputState(Input::ModeSwitch_SingleCycle, false);
        }
    });

    // �s�� countsUpdated �H���� updateCounts ��
    connect(&machineCtrl, &MachineController::countsUpdated, this, &MainWindow::updateCounts);

    // �s�� pushButton �P IOMap
    connect(ui->pushButton_St_Rst, &QPushButton::clicked, this, [this](bool checked) {
        ioMap.setInputState(Input::StartReset, true);
        if (checked) {
            // ������L�Ҧ�
            ui->pushButton_EMS->setChecked(false);
            ioMap.setInputState(Input::EmergencyStop, false);
        }
        });

    connect(ui->pushButton_EMS, &QPushButton::clicked, this, [this](bool checked) {
        ioMap.setInputState(Input::EmergencyStop, true);
        if (checked) {
            // ������L�Ҧ�
            ui->pushButton_St_Rst->setChecked(false); 
            ioMap.setInputState(Input::StartReset, false);
        }
        });

    // �s�� pushButton(���) �P IOMap
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


    // �s�� pushButton(��B���) �P IOMap
    // 1. ���U�u��� +1�v���s
    connect(ui->pushButton_AddCircle, &QPushButton::clicked, this, [this]() {
        // machineController �O MainWindow �֦����@�Ӫ���ΰѦ�
        machineCtrl.setCircleCount(machineCtrl.getCircleCount() + 1);
        });

    // 2. ���U�u��� -1�v���s
    connect(ui->pushButton_SubCircle, &QPushButton::clicked, this, [this]() {
        int current = machineCtrl.getCircleCount();
        if (current > 0) {
            machineCtrl.setCircleCount(current - 1);
        }
        });

    // 3. ���U�u��� +1�v���s
    connect(ui->pushButton_AddSquare, &QPushButton::clicked, this, [this]() {
        machineCtrl.setSquareCount(machineCtrl.getSquareCount() + 1);
        });

    // 4. ���U�u��� -1�v���s
    connect(ui->pushButton_SubSquare, &QPushButton::clicked, this, [this]() {
        int current = machineCtrl.getSquareCount();
        if (current > 0) {
            machineCtrl.setSquareCount(current - 1);
        }
        });
}

// ��s QLCDNumber
void MainWindow::updateCounts(int circleCount, int squareCount) 
{
    // ��s QLCDNumber
    ui->lcdNumber_Circle->display(circleCount);
    ui->lcdNumber_Square->display(squareCount);
}

// �s�W�H���ѳs����k
void MainWindow::updateIOStatus()
{   
    // ��J�T��
    // �ϥ� Input::CylinderDownLimit �@����ȡA�q inputState �d���e���A
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

    // ��X�T��
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

    // �T��O�A�U�ۤ@�� Label�B�@�� bool
    updateLightStatus(ui->label_RL, ioMap.readOutput(Output::RedLight),
        redLightStyle, triColorDefaultStyle);
    updateLightStatus(ui->label_YL, ioMap.readOutput(Output::YellowLight),
        yellowLightStyle, triColorDefaultStyle);
    updateLightStatus(ui->label_GL, ioMap.readOutput(Output::GreenLight),
        greenLightStyle, triColorDefaultStyle);
}

// ��s UI ����J/��X�����A�A�����C��
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

#include "MachineController.h"
#include <iostream>
#include <QCoreApplication>        
#include <thread>
#include <chrono>


MachineController::MachineController(IOMap& ioMapRef, QObject* parent)
    : QObject(parent)
    , ioMap(ioMapRef)
    , isCircle(false)
    , skipToStep2(false)
    , circleCount(0)
    , squareCount(0)
    , isRunningCycle(false)
{
    // -----------------------------------------------------
    // ��l�ƥi�H�g�b�o
    // -----------------------------------------------------
    
    // �O���]�w
    ioMap.writeOutput(Output::GreenLight, true);   // �}�ҫݾ��O
    ioMap.writeOutput(Output::YellowLight, false); // �����_�k�O
    ioMap.writeOutput(Output::RedLight, false);    // �����B��O

    // ���I�]�w
    ioMap.setInputState(Input::CylinderUpLimit, true);  // ������I��m
    ioMap.setInputState(Input::ArmPosition, true);      // �s�����u���I��m
}


// (�������)
void MachineController::delay(int milliseconds) 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


// ��^��e�`���B�檬�A
bool MachineController::isCycleRunning() const 
{
    std::lock_guard<std::mutex> lock(cycleMutex);
    return isRunningCycle;
}


// �ˬd�氱���s
bool MachineController::checkEmergencyStop()
{
    // �ˬd ioMap �O�_Ū��氱���s
    if (ioMap.readInput(Input::EmergencyStop)) {
        std::cout << "[DEBUG] Detected E-Stop inside MachineController, halting system..." << std::endl;

        // ������J�I���A
        ioMap.setInputState(Input::CylinderDownLimit, false);
        ioMap.setInputState(Input::CylinderUpLimit, false);
        ioMap.setInputState(Input::MaterialSensor, false);
        ioMap.setInputState(Input::ShapeCircleSensor, false);
        ioMap.setInputState(Input::ArmPosition, false);
        ioMap.setInputState(Input::CircleEjector, false);
        ioMap.setInputState(Input::SquareEjector, false);

        // ������X�I���A
        ioMap.writeOutput(Output::CylinderDown, false);
        ioMap.writeOutput(Output::ConveyorMotor, false);
        ioMap.writeOutput(Output::ArmMoveLeft, false);
        ioMap.writeOutput(Output::ArmMoveRight, false);
        ioMap.writeOutput(Output::GripperClose, false);
        ioMap.writeOutput(Output::GripperOpen, false);

        // �O������(�̻ݨD�վ�)
        ioMap.writeOutput(Output::RedLight, false);
        ioMap.writeOutput(Output::YellowLight, false);
        ioMap.writeOutput(Output::GreenLight, false);

        // �^�� true ��ܰ�����氱
        return true;
    }
    // �_�h�S���氱
    return false;
}


//�]��ʼҦ��^
void MachineController::runManual() 
{
    std::cout << "[DEBUG] Entering Manual Mode." << std::endl;

    // �b��ʼҦ��� while �̡A�C�@�鳣�ˬd�O�_�w�Q������
    while (true)
    {
        // -----------------------------------------------------
        // �ˬd�ާ@�Ҧ�������
        // -----------------------------------------------------
        // (a) �ˬd�O�_�������b�u�u�@�Ҧ� Right + ��ʼҦ� Manual�v
        if (!ioMap.readInput(Input::ModeSwitch_Right) || !ioMap.readInput(Input::ModeSwitch_Manual)) {
            std::cout << "[DEBUG] Manual Mode switched off. Break runManual()." << std::endl;
            break;
        }
        // (b) �p�G�Q�䴩�u�������� SingleCycle or Continuous�v�A�]�i�H�b�o�̧P�_
        if (ioMap.readInput(Input::ModeSwitch_SingleCycle) || ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] Detected user switching to Single/Continuous. Break runManual()." << std::endl;
            break;
        }
        // (c) �p�G�Q�䴩�u�������� ModeSwitch_Left�v�A�]�i�H�b�o�̧P�_
        if (ioMap.readInput(Input::ModeSwitch_Left)) {
            std::cout << "[DEBUG] Detected user switched to Reset. Breaking manual loop..." << std::endl;
            break; 
        }
        
        // -----------------------------------------------------
        // ��ʾާ@
        // -----------------------------------------------------
        // ������O�A�åB�}�Ҷ��O
        ioMap.writeOutput(Output::GreenLight, false);
        ioMap.writeOutput(Output::YellowLight, true);

        // 1. PB1�G��e�a����
        if (ioMap.readInput(Input::ManualConveyor)) { // PB1 ���U��
            std::cout << "Manual operation: Conveyor running." << std::endl;
            ioMap.writeOutput(Output::ConveyorMotor, true); // �Ұʿ�e�a
        }
        else {
            ioMap.writeOutput(Output::ConveyorMotor, false); // �����e�a
        }

        // 2. PB2�G����������
        if (ioMap.readInput(Input::ManualACylinder)) { // PB2 ���U��
            if (!ioMap.readInput(Input::CylinderDownLimit)) { // �p�G�U���P������Ĳ�o
                std::cout << "Manual operation: Cylinder moving down." << std::endl;
                ioMap.writeOutput(Output::CylinderDown, true); // �q�q�A�������U��

                // �����P�������A�ܤ�
                ioMap.setInputState(Input::CylinderDownLimit, true); // �U���P����Ĳ�o
                ioMap.setInputState(Input::CylinderUpLimit, false);  // �W���P������Ĳ�o
            }
            else {
                std::cerr << "Warning: Cylinder already at down limit." << std::endl;
            }
        }
        else { // ��} PB2 ��
            std::cout << "Manual operation: Cylinder moving up." << std::endl;
            ioMap.writeOutput(Output::CylinderDown, false); // �۰ʴ_��A�������W�ɡ]���q�q�^

            // �����P�������A�ܤ�
            ioMap.setInputState(Input::CylinderDownLimit, false); // �U���P������Ĳ�o
            ioMap.setInputState(Input::CylinderUpLimit, true);    // �W���P����Ĳ�o
        }

        // 3. PB3�G�s�����u����
        if (ioMap.readInput(Input::ManualArmLeft)) { // PB3 ���U��
            std::cout << "Manual operation: Arm moving left." << std::endl;
            ioMap.writeOutput(Output::ArmMoveLeft, true); // �s�����u����
            ioMap.setInputState(Input::ArmPosition, false);  // �s�����u�w�Q���ʡA���I���h�ݭn���s�_�k�C
        }
        else {
            ioMap.writeOutput(Output::ArmMoveLeft, false); // �����s�����u����
        }

        // 4. PB4�G�s�����u�k��
        if (ioMap.readInput(Input::ManualArmRight)) { // PB4 ���U��
            std::cout << "Manual operation: Arm moving right." << std::endl;
            ioMap.writeOutput(Output::ArmMoveRight, true); // �s�����u�k��
            ioMap.setInputState(Input::ArmPosition, false);  // �s�����u�w�Q���ʡA���I���h�ݭn���s�_�k�C
        }
        else {
            ioMap.writeOutput(Output::ArmMoveRight, false); // �����s�����u�k��
        }

        // �C���`��������A�קK�L���ˬd
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    ioMap.writeOutput(Output::YellowLight, false); // ���X��ʫ�A���O���C
    std::cout << "Exiting Manual Mode." << std::endl;
}


// �]�s��`���Ҧ��^
void MachineController::runContinuous() {

    std::cout << "System is in Continuous Cycle Mode. Running continuous process..." << std::endl;

    while (true) 
    {
        // -----------------------------------------------------
        // �ˬd�ާ@�Ҧ�������
        // -----------------------------------------------------
        // (a) �����O�_�w�������}�u�s��Ҧ��v
        if (!ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] Continuous Mode switched off. Break runContinuous()." << std::endl;
            break;
        }
        // (b) �Y�Q�����O�_�Q���� Manual �� Single
        if (ioMap.readInput(Input::ModeSwitch_Manual) || ioMap.readInput(Input::ModeSwitch_SingleCycle)) {
            std::cout << "[DEBUG] Detected user switching to Manual/SingleCycle. Break runContinuous()." << std::endl;
            break;
        }
        // (c) �p�G�Q�䴩�u�������� ModeSwitch_Left�v�A�]�i�H�b�o�̧P�_
        if (ioMap.readInput(Input::ModeSwitch_Left)) {
            std::cout << "[DEBUG] Detected user switched to Reset. Breaking manual loop..." << std::endl;
            break;
        }

        // �����l�Ƭy�{
        ioMap.writeOutput(Output::GreenLight, true);
        ioMap.writeOutput(Output::RedLight, false);  
        runMainProcess();

        // �氱�ˬd
        if (ioMap.readInput(Input::EmergencyStop)) { 
            std::cerr << "Emergency stop triggered during Continuous Cycle!" << std::endl;
            break; // ���_�s��`��
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // ����L���W�c
    }
    std::cout << "Exiting Continuous Cycle Mode." << std::endl;
}


// �]��@�`���Ҧ��^
void MachineController::runSingle() 
{
    {
        std::lock_guard<std::mutex> lock(cycleMutex);
        // �Y�w�b�����@�`���A�N���A����
        if (isRunningCycle) {
            std::cout << "[DEBUG] Cycle already running. Exiting runSingle." << std::endl;
            return;
        }
        isRunningCycle = true;
    }

    std::cout << "[DEBUG] Entering Single Cycle Mode. Running single process..." << std::endl;

    while (true)
    {
        // -----------------------------------------------------
        // (1) �ˬd�ާ@�Ҧ�������
        // -----------------------------------------------------
        // (a) �Y�������A�O�u��@�`���v(X17)�A�N���}
        if (!ioMap.readInput(Input::ModeSwitch_SingleCycle)) {
            std::cout << "[DEBUG] SingleCycle Mode switched off. Break runSingle()." << std::endl;
            break;
        }

        // (b) �Y����������(X15)�γs��Ҧ�(X16)�A�]�n���}
        if (ioMap.readInput(Input::ModeSwitch_Manual) || ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] Detected user switching to Manual/Continuous. Break runSingle()." << std::endl;
            break;
        }

        // (c) �p�G�Q�䴩�u���������_�k (ModeSwitch_Left)(X13)�v�A�]�i�H�b�o�̧P�_
        if (ioMap.readInput(Input::ModeSwitch_Left)) {
            std::cout << "[DEBUG] Detected user switched to Reset (Left). Break runSingle()." << std::endl;
            break;
        }

        // -----------------------------------------------------
        // (2) ����@���D�y�{
        // -----------------------------------------------------
        ioMap.writeOutput(Output::GreenLight, true);
        ioMap.writeOutput(Output::RedLight, false);
        runMainProcess();

        // -----------------------------------------------------
        // (3) �ˬd�氱
        // -----------------------------------------------------
        if (ioMap.readInput(Input::EmergencyStop)) {
            std::cerr << "[DEBUG] Emergency stop triggered during Single Cycle! Break runSingle()." << std::endl;
            break;
        }

        // ��@�`���u����@���A�G���槹 mainProcess ��ߧY break
        std::cout << "[DEBUG] Single cycle main process done. Break runSingle() loop." << std::endl;
        break;
    }

    // ���X while (true) ����A�N���ӳ�@�`���y�{����
    {
        std::lock_guard<std::mutex> lock(cycleMutex);
        isRunningCycle = false;
    }

    std::cout << "[DEBUG] Exiting Single Cycle Mode." << std::endl;
}


// �]�]�ƼҦ������P�_ & ���I�Ұʱ���^
void MachineController::runMainProcess() {
    std::cout << "Main process starting..." << std::endl;

    // �s�W�޿�G�P�_�O�_���L�B�J 1
    if (skipToStep2) {
        std::cout << "Skipping Step 1 as per continuous mode logic. Proceeding directly to Step 2..." << std::endl;
        skipToStep2 = false; // ���m���L�лx�A�T�O�U�����楿�`
        runStep2();          // �����i�J�B�J 2
        return;
    }

    // �B�J 1�G��l�ƪ��A�T�{
    if (ioMap.readInput(Input::ModeSwitch_Left) || ioMap.readInput(Input::EmergencyStop)) {
        std::cerr << "[ERROR] System is not ready for operation. Check Reset Mode or Emergency Stop." << std::endl;
        // Reset isRunningCycle if step 1 fails
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        return;
    }

    // �O���]�w
    /*
    ioMap.writeOutput(Output::GreenLight, true);   // �}�ҫݾ��O
    ioMap.writeOutput(Output::YellowLight, false); // �����_�k�O
    ioMap.writeOutput(Output::RedLight, false);    // �����B��O
    */

   // -----------------------------------------------------
   // (1) �Ĥ@�h�j�j��:
   //     �b�o���ˬd�p�G�O��� => ���� return,
   //     �p�G�O��@�γs�� => break (���U��),
   //     �_�h�N�d�b�j����[��C
   // -----------------------------------------------------
    while (true)
    {
        // (a) �Y������ Manual => ���� return
        if (ioMap.readInput(Input::ModeSwitch_Manual)) {
            std::cout << "[DEBUG] Detected Manual => return from runMainProcess()" << std::endl;
            return; // ������Ө禡
        }

        // (b) �Y������ SingleCycle / Continuous => break
        if (ioMap.readInput(Input::ModeSwitch_SingleCycle) || ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] Detected Single or Continuous => break first loop" << std::endl;
            break; // ���} while(true)�A���U����
        }

        //     �קK�]�o���W�c�Asleep�@�I�ɶ�
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // -----------------------------------------------------
    // (2) �ĤG�h�j��:
    //     ����o�̡A��ܤw�g�b�Ĥ@�h�P�_���ubreak�v�X�ӡA
    //     �]�N�O������ثe�O SingleCycle / Continuous �Ҧ�
    //     => ���۶i�J�ĤG�h�p�j��A���� StartReset�C
    // -----------------------------------------------------
    std::cout << "[DEBUG] Waiting for StartReset button to be pressed..." << std::endl;
    while (!ioMap.readInput(Input::StartReset))
    {
        // ���p�b���� StartReset ���L�{���A�S���� Manual => �N���� return
        if (ioMap.readInput(Input::ModeSwitch_Manual)) {
            std::cout << "[DEBUG] Switch to Manual => return from runMainProcess()" << std::endl;
            return;
        }

        // �]�i�H�A�ˬd�G�p�G Single/Continuous �Q���F�A��ܤ��A�ݭn���U�h
        if (!ioMap.readInput(Input::ModeSwitch_SingleCycle) &&
            !ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] No longer in Single/Continuous => return" << std::endl;
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // �C 0.5 ���ˬd�@��
    }
    std::cout << "[DEBUG] StartReset button pressed. Proceeding to Step 2..." << std::endl;

    // -----------------------------------------------------
    // (3) ���I�����ˬd (�ˬd ArmPosition & CylinderUpLimit)
    //     �Y�ŦX => ����U�@���q�y�{: runStep2()
    //     ���m StartReset �� false
    // -----------------------------------------------------
    if (!ioMap.readInput(Input::ArmPosition) || !ioMap.readInput(Input::CylinderUpLimit)) 
    {
        std::cerr << "[ERROR] Cannot start runStep2(): Arm or Cylinder not at origin!" << std::endl;
        // ���� return�A������᭱
        return;
    }
    else
    {
        ioMap.setInputState(Input::StartReset, false); // �T�����s
        runStep2();  // �i�J�B�J 2
    }
}

void MachineController::runStep2()
{
    // �B�J 1�G�P�_���S����
    // (���] circleCount+squareCount>0 �N��ܦ���)
    if ((circleCount + squareCount) > 0) {

        // [1] �ˬd�氱
        if (checkEmergencyStop()) return;

        // ��ܦ��� => �˴����\
        delay(1000); // �ݭn�w�@�U�A�_�h���| UI �G (MaterialSensor)
        ioMap.setInputState(Input::MaterialSensor, true); // �ƥ�P�����w����

        // �Ұʬy�{�O��
        ioMap.writeOutput(Output::GreenLight, false);  // �����ݾ��O
        ioMap.writeOutput(Output::RedLight, true);     // �ҰʿO�G�_

        // �B�J 1.1�G��e�a�Ұ�
        std::cout << "Conveyor starting..." << std::endl;
        ioMap.writeOutput(Output::ConveyorMotor, true); // �Ұʿ�e�a
        delay(5000); // ���� T0 �p�� 5 ��

        // �����e�a
        std::cout << "Conveyor stopping..." << std::endl;
        ioMap.writeOutput(Output::ConveyorMotor, false);

        // [2] �ˬd�氱
        if (checkEmergencyStop()) return;


        // �B�J 2�G�P�_���ƧΪ� (ShapeCircleSensor) 
        // �P�z�A�p�G circleCount > 0�A�N�� ShapeCircleSensor �]�� true
        bool isCircle = false;
        if (circleCount > 0) {
            ioMap.setInputState(Input::ShapeCircleSensor, true);
            isCircle = true;  // ���
        }
        else {
            ioMap.setInputState(Input::ShapeCircleSensor, false);
            isCircle = false; // ���
        }

        // [3] �ˬd�氱
        if (checkEmergencyStop()) return;

        // �B�J 2.1�GŪ�� Sensor �����
        delay(1000); // ���� T1 �p�� 1 ��
        if (ioMap.readInput(Input::ShapeCircleSensor)) {
            std::cout << "Detected material: Circle." << std::endl;
        }
        else {
            std::cout << "Detected material: Square." << std::endl;
        }

        // [4] �ˬd�氱
        if (checkEmergencyStop()) return;

        // �B�J 3�G�������U��
        std::cout << "Cylinder moving down..." << std::endl;

        // �����������U�����ʧ@
        ioMap.writeOutput(Output::CylinderDown, true);  // �Ұʫ������U��

        // �����������U�����L�{
        delay(1000);

        // ��s�P�������A
        ioMap.setInputState(Input::CylinderDownLimit, true); // �����U���P����Ĳ�o
        ioMap.setInputState(Input::CylinderUpLimit, false);  // �����W���P������Ĳ�o

        // [5] �ˬd�氱
        if (checkEmergencyStop()) return;

        // �T�O�������w�g��F�U��
        if (!ioMap.readInput(Input::CylinderDownLimit)) {
            std::cerr << "Error: Cylinder failed to reach down position!" << std::endl;
            // Reset isRunningCycle if step 3 fails
            {
                std::lock_guard<std::mutex> lock(cycleMutex);
                isRunningCycle = false;
            }
            return; // �פ�y�{
        }

        std::cout << "Cylinder reached down position. Proceeding to next step..." << std::endl;

        // [6] �ˬd�氱
        if (checkEmergencyStop()) return;

        // �B�J 4�G�����������X
        std::cout << "Gripper closing..." << std::endl;

        // �Ұʧ������X
        ioMap.writeOutput(Output::GripperClose, true); // �Ұʧ������X�ʧ@

        // ���� T2 �p�� 1 ��
        delay(1000);

        // ��������X
        ioMap.writeOutput(Output::GripperClose, false); // ��������X�ʧ@

        std::cout << "Gripper closed. Proceeding to next step..." << std::endl;

        // [7] �ˬd�氱
        if (checkEmergencyStop()) return;

        // �B�J 5�G�������W��
        std::cout << "Cylinder moving up..." << std::endl;

        // �Ұʫ������W��
        ioMap.writeOutput(Output::CylinderDown, false); // �������W��

        // �����������W�ɪ��L�{
        delay(1000);

        // ��s�P�������A
        ioMap.setInputState(Input::CylinderDownLimit, false); // �����U���P������Ĳ�o
        ioMap.setInputState(Input::CylinderUpLimit, true); // �ҰʤW�ɰʧ@
        ioMap.setInputState(Input::MaterialSensor, false); // �ƥ�P����������
        ioMap.setInputState(Input::ShapeCircleSensor, false); // �ƥ󦹮ɤw�Q����

        // �T�O�������w�g��F�W��
        if (!ioMap.readInput(Input::CylinderUpLimit)) {
            std::cerr << "[ERROR] Cylinder failed to reach up position!" << std::endl;
            // Reset isRunningCycle if step 5 fails
            {
                std::lock_guard<std::mutex> lock(cycleMutex);
                isRunningCycle = false;
            }
            return; // �פ�y�{
        }

        std::cout << "[DEBUG] Cylinder reached up position. Proceeding to next step..." << std::endl;

        // [8] �ˬd�氱
        if (checkEmergencyStop()) return;

        // �B�J 6�G�s�����u����
        std::cout << "Moving gantry arm left..." << std::endl;

        if (isCircle) {
            handleCircleMaterial(); // �I�s��ƪ��B�z�禡
        }
        else {
            handleSquareMaterial(); // �I�s��ƪ��B�z�禡
        }

        std::cout << "Gantry arm moved to position. Proceeding to next step..." << std::endl;
        return;
    }
}


// ��ƳB�z�禡
void MachineController::handleCircleMaterial() {
    std::cout << "Handling circle material. Moving gantry arm left..." << std::endl;

    // [1] �ˬd�氱
    if (checkEmergencyStop()) return;

    ioMap.writeOutput(Output::ArmMoveLeft, true);   // �Ұʥ���
    ioMap.setInputState(Input::ArmPosition, false);  // �s�����u�D���I��m
    delay(3000); // ���� 3 ���ʮɶ��]��ơ^

    // [2] �ˬd�氱
    if (checkEmergencyStop()) return;

    // �B�J 7�G����ʤ��u�A��������������}
    std::cout << "Stopping gantry arm and releasing gripper (B-)..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveLeft, false); // �����
    ioMap.writeOutput(Output::GripperOpen, true);  // ���槨�����}�ʧ@�]B-�^

    delay(1000); // ���� 1 ��

    ioMap.writeOutput(Output::GripperOpen, false); // ������ʧ@
    std::cout << "Gripper released. Proceeding to next step..." << std::endl;

    //  �B�J 7.1�G��ƱƮƦ�
    ioMap.setInputState(Input::CircleEjector, true);
    delay(1500); // ���� 1.5 ��
    ioMap.setInputState(Input::CircleEjector, false);

    // [3] �ˬd�氱
    if (checkEmergencyStop()) return;


    // �B�J 8�G�s�����u�k���^��l��m
    std::cout << "Moving gantry arm right to initial position..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveRight, true); // �Ұʥk��
    delay(3000); // ���� 3 ���ʮɶ�

    std::cout << "Gantry arm returned to initial position. Proceeding to next step..." << std::endl;


    // �B�J 9�G���������u����B�M���O��
    std::cout << "Stopping gantry arm and clearing memory..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveRight, false); // ����k��

    // �s�����u�^����I��m
    ioMap.setInputState(Input::ArmPosition, true);  // �s�����u���I��m

    // [4] �ˬd�氱
    if (checkEmergencyStop()) return;

    // �b�y�{������, ��]circleCount �� 1�^
    if (circleCount > 0) {
        circleCount--;
        std::cout << "circleCount now = " << circleCount << std::endl;
        emit countsUpdated(circleCount, squareCount);
    }

    // �P�_�Ҧ��èM�w�y�{
    if (ioMap.readInput(Input::ModeSwitch_Continuous)) { // �P�_�O�_���s��`���Ҧ�
        std::cout << "Mode: Continuous Cycle. Returning to step 2." << std::endl;
        skipToStep2 = true; // �]�m�лx�A���L�B�J 1
        runContinuous(); // �^��s��`���Ҧ��A�A���ˬd���s�O�_���ܪ��A
    }
    else {
        std::cout << "Mode: Single Cycle. Returning to idle state." << std::endl;
        skipToStep2 = false; // �M���лx
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        emit countsUpdated(circleCount, squareCount);
    }
}

// ��ƳB�z�禡
void MachineController::handleSquareMaterial() {
    std::cout << "Handling square material. Moving gantry arm left..." << std::endl;

    // [1] �ˬd�氱
    if (checkEmergencyStop()) return;

    // �B�J 17-1�G�Ұʤ��u����
    ioMap.writeOutput(Output::ArmMoveLeft, true);    // �Ұʥ���
    ioMap.setInputState(Input::ArmPosition, false);  // �s�����u�D���I��m
    delay(5000); // ���� 5 ���ʮɶ��]��ơ^

    // �B�J 17-2�G����ʤ��u�A�������U��
    std::cout << "Stopping gantry arm and Cylinder moving down..." << std::endl;

    // [2] �ˬd�氱
    if (checkEmergencyStop()) return;

    // ����ʤ��u�A�Ұʫ������U��
    ioMap.writeOutput(Output::ArmMoveLeft, false); // �����
    ioMap.writeOutput(Output::CylinderDown, true); // �������U��

    // [3] �ˬd�氱
    if (checkEmergencyStop()) return;

    // �����������U�����L�{
    delay(1000);

    // ��s�P�������A
    ioMap.setInputState(Input::CylinderDownLimit, true); // �����U���P����Ĳ�o
    ioMap.setInputState(Input::CylinderUpLimit, false);  // �����W���P������Ĳ�o

    // �T�O�������w�g��F�U��
    if (!ioMap.readInput(Input::CylinderDownLimit)) {
        std::cerr << "Error: Cylinder failed to reach down position!" << std::endl;
        // Reset isRunningCycle if step 17-2 fails
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        return; // �פ�y�{
    }

    std::cout << "Cylinder reached down position. Proceeding to next step..." << std::endl;

    // [4] �ˬd�氱
    if (checkEmergencyStop()) return;


    // �B�J 18�G�����������}
    std::cout << "Gripper opening (B-)..." << std::endl;

    // �Ұʧ������}�ʧ@
    ioMap.writeOutput(Output::GripperOpen, true);  // ���槨�����}�ʧ@�]B-�^

    delay(1000); // ���� 1 ��

    // ������ʧ@
    ioMap.writeOutput(Output::GripperOpen, false); // ������ʧ@

    std::cout << "Gripper released. Proceeding to next step..." << std::endl;

    //  �B�J 18.1�G��ƱƮƦ�
    ioMap.setInputState(Input::SquareEjector, true);
    delay(1500); // ���� 1.5 ��
    ioMap.setInputState(Input::SquareEjector, false);

    // [5] �ˬd�氱
    if (checkEmergencyStop()) return;

    //�B�J 19�G�������W��
    std::cout << "Cylinder moving up..." << std::endl;

    // �Ұʫ������W��
    ioMap.writeOutput(Output::CylinderDown, false);

    // �����������U�����L�{
    delay(1000);

    // ��s�P�������A
    ioMap.setInputState(Input::CylinderDownLimit, false); // �����U���P������Ĳ�o
    ioMap.setInputState(Input::CylinderUpLimit, true);  // �����W���P����Ĳ�o

    // �T�O�������w�g��F�W��
    if (!ioMap.readInput(Input::CylinderUpLimit)) {
        std::cerr << "Error: Cylinder failed to reach up position!" << std::endl;
        // Reset isRunningCycle if step 19 fails
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        return; // �פ�y�{
    }

    std::cout << "Cylinder reached up position successfully. Proceeding to next step..." << std::endl;

    // [6] �ˬd�氱
    if (checkEmergencyStop()) return;


    // �B�J 8�G�s�����u�k���^��l��m
    std::cout << "Moving gantry arm right to initial position..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveRight, true); // �Ұʥk��
    delay(3000); // ���� 3 ���ʮɶ�

    std::cout << "Gantry arm returned to initial position. Proceeding to next step..." << std::endl;


    // �B�J 9�G���������u����B�M���O��
    std::cout << "Stopping gantry arm and clearing memory..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveRight, false); // ����k��

    // �s�����u�^����I��m
    ioMap.setInputState(Input::ArmPosition, true);  // �s�����u���I��m

    // [7] �ˬd�氱
    if (checkEmergencyStop()) return;

    // �b�y�{������, ��]squareCount �� 1�^
    if (squareCount > 0) {
        squareCount--;
        std::cout << "squareCount now = " << squareCount << std::endl;
        emit countsUpdated(circleCount, squareCount);
    }

    // �P�_�Ҧ��èM�w�y�{
    if (ioMap.readInput(Input::ModeSwitch_Continuous)) { // �P�_�O�_���s��`���Ҧ�
        std::cout << "Mode: Continuous Cycle. Returning to step 2." << std::endl;
        skipToStep2 = true; // �]�m�лx�A���L�B�J 1
        runContinuous(); // �^��s��`���Ҧ��A�A���ˬd���s�O�_���ܪ��A
    }
    else {
        std::cout << "Mode: Single Cycle. Returning to idle state." << std::endl;
        skipToStep2 = false; // �M���лx
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        emit countsUpdated(circleCount, squareCount);
    }
}

// �]�w��ƭp��
void MachineController::setCircleCount(int count) 
{
    {
        std::lock_guard<std::mutex> lock(countMutex);
        circleCount = count;
    }
    std::cout << "[DEBUG] circleCount set to " << circleCount << std::endl;
    emit countsUpdated(circleCount, squareCount);
}

// �]�w��ƭp��
void MachineController::setSquareCount(int count) 
{
    {
        std::lock_guard<std::mutex> lock(countMutex);
        squareCount = count;
    }
    std::cout << "[DEBUG] squareCount set to " << squareCount << std::endl;
    emit countsUpdated(circleCount, squareCount);
}

#include <iostream>
#include <thread>
#include <chrono>

#include "DeviceControl.h"
#include "MachineController.h"
#include "EmergencyStop.h"

void runDeviceControl(IOMap& ioMap, MachineController& machineCtrl) {

    // �ϥζǻ��i�Ӫ� MachineController ���
    EmergencyStop emergencyStop(ioMap);
    std::string previousMode = "Idle"; // �W���Ҧ�
    std::string currentMode = "Idle";  // �ثe�Ҧ�

    // �i�J�t�δ`��
    while (true) {
        // -----------------------------------------------------
        // (1) �ˬd�氱���A
        // -----------------------------------------------------
        if (ioMap.readInput(Input::EmergencyStop)) {
            std::cerr << "[DEBUG] Emergency stop triggered!" << std::endl;

            // ���������ʧ@����
            // ioMap.setInputState(Input::EmergencyStop, false);

            // ��������_�k�Ҧ� (X13)
            if (!ioMap.readInput(Input::ModeSwitch_Left)) {
                std::cerr << "[ERROR] ModeSwitch is not in Reset Mode. Please switch to Reset Mode." << std::endl;
                // �^��̥~�h while ���s�ˬd
                continue;
            }

            // ����_�k�޿�
            std::cout << "[DEBUG] Emergency stop released. Resetting system..." << std::endl;
            emergencyStop.handleReset();
        }

        // -----------------------------------------------------
        // (2) �ˬd�_�k���A
        // -----------------------------------------------------
        else if (ioMap.readInput(Input::ModeSwitch_Left)){

            currentMode = "Reset";

            // �_�k�Ҧ�
            if (currentMode != previousMode) {
                previousMode = currentMode;
                std::cout << "Switch to Reset => calling handleReset()" << std::endl;

                // �����_�k�ʧ@����
                // ioMap.setInputState(Input::ModeSwitch_Left, false);

                emergencyStop.handleReset();
            }
            else {
                // �w�g�b Reset
            }
        }

        // -----------------------------------------------------
        // (3) �ˬd�u�@�Ҧ����
        // -----------------------------------------------------
        else if (ioMap.readInput(Input::ModeSwitch_Right)) {

            // �ھڤ��/�s��/��@���}���ӽT�w�ثe�Ҧ�
            if (ioMap.readInput(Input::ModeSwitch_Manual)) {
                currentMode = "Manual"; // �����ʼҦ�
            }
            else if (ioMap.readInput(Input::ModeSwitch_Continuous)) {
                currentMode = "Continuous"; // ����s��`���y�{
            }
            else if (ioMap.readInput(Input::ModeSwitch_SingleCycle)) {
                currentMode = "SingleCycle"; // �����@�`���y�{
            }
            else {
                currentMode = "NoMode"; // �٨S��ܥ���Ҧ�
            }

            // �p�G�Ҧ��P���e���P -> �I�s�����禡
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
            else { // �Ҧ�������
                // SingleCycle �Ҧ��U�A�Y�٨S�}�l�άy�{�����A�i�H���ƱҰ�
                if (currentMode == "SingleCycle" && !machineCtrl.isCycleRunning()) {
                    std::cout << "[DEBUG] Mode: Single Cycle. Starting a new cycle..." << std::endl;
                    machineCtrl.runSingle();
                }
            }
        }
        else {
            // ����ܥ���Ҧ� => idle
            std::cout << "[DEBUG] No mode selected. System is idle." << std::endl;
        }
        // ���� CPU �L�רϥ� => sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

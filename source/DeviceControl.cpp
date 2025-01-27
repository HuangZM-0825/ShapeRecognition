#include <iostream>
#include <thread>
#include <chrono>

#include "DeviceControl.h"
#include "MachineController.h"
#include "EmergencyStop.h"


/**
 * @brief �֤߳]�Ʊ���L���j��禡�C
 *
 * �z�L `runDeviceControl()`�A�t�η|���_�a�ˬd�H�U���A�G
 *   1. **�氱 (EmergencyStop)**�G�Y������ `Input::EmergencyStop == true`�A�h���T�O�w�����ܴ_�k�Ҧ� (X13)�A
 *      �A�I�s `emergencyStop.handleReset()` �i��_�k�y�{�C
 *   2. **�_�k�Ҧ� (ModeSwitch_Left)**�G�Y������_�k�Ҧ��A�h�N `currentMode` �]�w�� "Reset"�A
 *      �æb�Ҧ��o���ܤƮɩI�s `handleReset()`�A�N�]�Ʀ^����I�C
 *   3. **�u�@�Ҧ� (ModeSwitch_Right)**�G�Y������u�@�Ҧ��A�ھڤ��/�s��/��@�`���ӳ]�w `currentMode`�A
 *      �æb�Ҧ����ܮɩI�s������ `runManual()`�B`runContinuous()` �� `runSingle()`�C
 *   4. **�Ҧ������ܮɪ��S��B�z**�G
 *      - ����@�`���Ҧ��A�Y���e�w���槹�� (`isCycleRunning() == false`)�A�i�A���Ұʷs����@�`���C
 *
 * �y�{�����G
 *   - �ϥΪ̩�~�� UI �����Ҧ��ɡA�t�η|�b���禡�� while �j�餤�˴���A
 *     �åߧY�I�s�������禡�������ʧ@ (�Ҧp `machineCtrl.runManual()`)�C
 *   - �Y�o�ͫ氱�A�h���L����Ҧ��P�_�A�u���B�z�_�k�A�T�O�w���C
 *   - ���קK���ιL�h CPU�A�̫�H `std::this_thread::sleep_for(...)` ���u�ȩ���A�����ˬd�C
 *
 * @param ioMap      �@�ɪ� IOMap�A�ΥHŪ/�g��J��X���A�C
 * @param machineCtrl ��������A���t��ʡB��@�`���B�s��`�����Ҧ���@�C
 *
 * @note �C���j�鳣�ϥ� `previousMode` �P `currentMode` �ӧP�_�Ҧ��O�_���ܡA
 *       �Y���ܤ~��������ʧ@�A�קK���ƶi�J�P�@�Ҧ��C
 */
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

#include "EmergencyStop.h"

EmergencyStop::EmergencyStop(IOMap& ioMap) : ioMap(ioMap) {}

void EmergencyStop::handleReset() {
    std::cout << "[RESET] Starting system reset..." << std::endl;
    resetCompleted = false;

    // -----------------------------
    // Step 1: �T�{�w�b�_�k�Ҧ� (X13)
    // Step 2: �����\�b��ʼҦ� (X15)
    // -----------------------------
    while (true) {
        if (!ioMap.readInput(Input::ModeSwitch_Left)) {
            // �ݭn�b�_�k�Ҧ�
            std::cerr << "[RESET] Error: Not in Reset Mode (X13 == false). "
                << "Please switch to Reset Mode..." << std::endl;
            return;
        }
        else if (ioMap.readInput(Input::ModeSwitch_Manual)) {
            // ����b��ʼҦ�
            std::cerr << "[RESET] Error: System is in Manual Mode (X15 == true). "
                << "Reset not allowed. Please switch off Manual Mode..." << std::endl;
            continue;
        }
        else {
            // ���󳣲ŦX�A�i�H�i�J�U�@�B
            std::cout << "[RESET] Good! Now in Reset Mode & not in Manual. Proceed..." << std::endl;
            break; // ���X�o�� while
        }

        // �Y�٨S�ŦX => ���ݤ@�p�q�ɶ���A�ˬd
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // -----------------------------
    // Step 3: ���� StartReset (X20) ���s
    // -----------------------------
    std::cout << "Waiting for StartReset button to be pressed..." << std::endl;
    while (!ioMap.readInput(Input::StartReset)) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // ���� StartReset
    }

    std::cout << "StartReset button pressed. Beginning reset process..." << std::endl;

    // Step 4: �}�l�{�{�_�k�O
    std::thread yellowLightBlinker([this]() {
        while (!resetCompleted) { // ��_�k�������ɫ���{�{
            ioMap.writeOutput(Output::YellowLight, true);
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // ���O�G 0.5 ��
            ioMap.writeOutput(Output::YellowLight, false);
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // ���O�� 0.5 ��
        }
        });

    // Step 5: �������W�ɡA�T�{�P�������A
    std::cout << "Raising cylinder to up position..." << std::endl;
    ioMap.writeOutput(Output::CylinderDown, false); // ����U��
    ioMap.setInputState(Input::CylinderDownLimit, false); // �����U���P������Ĳ�o
    ioMap.setInputState(Input::CylinderUpLimit, true);    // �����W���P����Ĳ�o
    delay(1000); // �����������W�ɹL�{

    // Step 6: ���������������
    std::cout << "Releasing gripper (B-)..." << std::endl;
    ioMap.writeOutput(Output::GripperOpen, true); // ���� B-
    delay(1000); // ���� T4 �p�� 1 ��
    ioMap.writeOutput(Output::GripperOpen, false); // ���� B-

    // Step 7: �s���k�����l��m
    std::cout << "Moving gantry arm to initial position (M2-)..." << std::endl;
    ioMap.writeOutput(Output::ArmMoveRight, true); // �Ұʥk��
    delay(3000); // ��������

    ioMap.writeOutput(Output::ArmMoveRight, false); // ����k��

    // �s�����u�^����I��m
    ioMap.setInputState(Input::ArmPosition, true);  // �s�����u���I��m

    // Step 8: �����_�k�A��s�O��
    resetCompleted = true; // �]�m�_�k�������A
    yellowLightBlinker.join(); // ���ݶ��O�{�{�u�{����
    ioMap.writeOutput(Output::YellowLight, false); // �T�O���O����
    ioMap.writeOutput(Output::GreenLight, true);   // ��O�G�A�����_�k


    // Step 9: ���s�T���_�k�A�_�h���^�u�@�Ҧ��|�۰ʱҰʬy�{
    ioMap.setInputState(Input::StartReset, false);
    ioMap.setInputState(Input::EmergencyStop, false);
    ioMap.setInputState(Input::ModeSwitch_Left, false);

    std::cout << "System reset completed. System is ready." << std::endl;
}

// �����p�ɾ�������
void EmergencyStop::delay(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

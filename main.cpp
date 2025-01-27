#include "mainwindow.h"

#include <QApplication>
#include <thread>                 // for std::thread

#include "header/IOMap.h"         // �]�t IOMap
#include "header/DeviceControl.h" // �]�t runDeviceControl()
#include "header/MachineController.h"

/**
 * @brief �D�禡�J�f�I�A�a�� (argc, argv) �H�䴩�R�O�C�ѼơC
 *
 * �o�O C++ ���з� main() �禡�A�� Qt �{���ϥήɤ]�|�N argc/argv �൹ QApplication�A�Ω��l�� GUI ���ҡC
 * 
 * Qt �{���q�`�ݭn�q main �禡�ǻ��ѼƵ� QApplication�A
 * �H���T��l�� Qt ��������]�ƥ�j��BGUI ��ܵ��^�C
 */
int main(int argc, char* argv[])
{
    /**
     * @brief �إ� Qt ���ε{������ (QApplication)�C
     *
     * ������t�d�޲z��� GUI �ƥ�j��B�귽�P��l�Ƭy�{�C
     * `argc`�B`argv` �i�Ω�ѪR�R�O�C�ѼơA�Y�L�S�O�ݭn�]�i�����a�J�C
     * 
     * �q�`�n�b�D�禡�̫e���إߡA�̫� a.exec() �i�J�ƥ�j��A�� GUI �ब�ʡC
     */
    QApplication a(argc, argv);

    // (1) ���ͤ@�� IOMap ����A�éR�W sharedIOMap�C  
    // �z�L�ѦҩΫ��ШӦs�����A�N��O�ҩҦ� I/O ���A�O�@�P�B�P�B���C
    IOMap sharedIOMap;

    // (2) �إ߰ߤ@�� MachineController ����A�B�N sharedIOMap �ǤJ�غc�l�C
    //     �o�� machineCtrl �P���� DeviceControl�BMainWindow ���|���V�P�@�Ӫ���A���|�U�ۦb�{���̦A�ؤ@�� MachineController�C
    MachineController machineCtrl(sharedIOMap); // �D���

    // (3) �}�Ҥ@�Ӱ�����] runDeviceControl(...)
    //     �ǻ� sharedIOMap �M machineCtrl ���ޥ�
    std::thread devThread(runDeviceControl, std::ref(sharedIOMap), std::ref(machineCtrl));

    // (4) �N�P�@�� sharedIOMap �P machineCtrl �ǵ� MainWindow�A�H�K UI �ݥi�H�]�Ҧp�^�b�u�[�@�Ӥ�ơv�ɩI�s machineCtrl.setSquareCount(...)�C
    //     �A�ݭn�b MainWindow ���غc�l�̼g:
    //     MainWindow(IOMap& ioMap, MachineController& machineCtrl, QWidget* parent = nullptr);
    MainWindow w(sharedIOMap, machineCtrl);
    w.show();

    // (5) ����������]�ήھڻݨD��� join�^
    devThread.detach(); // �p�G�A�Ʊ������W�߹B��A���ݭn���ݥ�����
    // devThread.join(); // �p�G�A�Ʊ�D��������� devThread ����

    // (6) �i�J Qt �ƥ�j��
    return a.exec();
}
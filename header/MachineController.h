#ifndef MACHINECONTROLLER_H // �p�G MACHINECONTROLLER_H �|���w�q
#define MACHINECONTROLLER_H // �w�q MACHINECONTROLLER_H

#include "IOMap.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <QObject>
#include <QTimer>
#include <mutex>


class MachineController : public QObject
{
    Q_OBJECT

public:
    // -----------------------------------------------------
    // ��MachineController ���O���غc�l (Constructor)
    // �Ѽ� IOMap& ioMap �G���V���t�Ϊ� I/O ������A�Ψ�Ū���P�������g�J�X�ʿ�X�C
    // �Ѽ� QObject* parent �G���F�ŦX Qt ����h�šA�w�]�� nullptr ��ܦ�����L���C
    // ���覡�i�O�ҵ{�����u���@�ӥD�n IOMap�A���� I/O ���A�@�P�C
    // -----------------------------------------------------
    explicit MachineController(IOMap& ioMap, QObject* parent = nullptr);

    void runManual();      // �����ʼҦ�
    void runContinuous();  // ����s��`���y�{
    void runSingle();      // �����@�`���y�{
    void runMainProcess(); // �D�y�{���

    // �D�����˴������f�G�}�l�i�J�uStep2�v�y�{
    void runStep2();

    // �]�w�p�� (�Y�q�~�� UI �Ƕi��)
    void setCircleCount(int count);
    void setSquareCount(int count);
    // ���o�p�� (�Y UI �nŪ�^�����)
    int getCircleCount() const { return circleCount; }
    int getSquareCount() const { return squareCount; }

    // �^���u�ثe�O�_���b����`�� (Cycle)�v�����A
    // �u�b isCycleRunning() == false �ɡA�~�A���Ұʳ�@�`���y�{�C
    bool isCycleRunning() const;


signals:
    // -----------------------------------------------------
    // Qt �� signal
    // �� MachineController ������s�F�u��Ƽƶq (circleCount)�v�Ρu��Ƽƶq (squareCount)�v�ɡA�N�|�o�X�ӰT���C
    // Qt ����]�p UI ���� MainWindow�^�i�H�z�L connect(...) ��ť���T���A�æb����ɶi�椶����s�C
    // UI �ݥu�n�����o�ӰT���A�N�న�W��̷s�ƶq��ܨ� UI �W�C
    // -----------------------------------------------------
    void countsUpdated(int circleCount, int squareCount);


private:
    IOMap& ioMap; // �ޥ� IOMap�A�P IO �椬�A���|���� IOMap�A�ӬO�����ާ@�ǻ��i�Ӫ� IOMap ��ҡC
    // �קK�����}�P : ���j������A�������|���O���s�M�p��귽�C
    // �O���@�P�� : �p�G���h�ӼҲջݭn�ާ@�P�@�� IOMap�A�ϥΤޥνT�O�Ҧ��Ҳլݨ쪺�O�P�@�� IOMap ��ҡC

    // �D���ˬd�氱
    bool checkEmergencyStop();

    // �\��禡
    void handleCircleMaterial(); // �B�z����޿�
    void handleSquareMaterial(); // �B�z����޿�

    // �������U���
    void delay(int milliseconds); // �����ʧ@����

    bool isCircle;    // �Ω�O����e�ƥ�����
    bool skipToStep2; // �Ω�O���O�_���L�B�J 1

    // �Ω�O����e�ƥ�ƶq
    // mutable std::mutex countMutex; // �O�@ circleCount �M squareCount
    int circleCount = 0;
    int squareCount = 0;

    mutable std::mutex countMutex; // �O�@ circleCount �M squareCount
    mutable std::mutex cycleMutex; // �O�@ isRunningCycle

    bool isRunningCycle; // �`�����A�лx
};

#endif // MACHINECONTROLLER_H

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

    bool isCycleRunning() const;

signals:
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

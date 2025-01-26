#ifndef EMERGENCYSTOP_H
#define EMERGENCYSTOP_H

#include "IOMap.h"
#include <chrono>
#include <thread>
#include <iostream>

class EmergencyStop {
public:
    explicit EmergencyStop(IOMap& ioMap); // �c�y���

    // �_�k�y�{
    void handleReset();

    // �_�k�����X��
    std::atomic_bool resetCompleted{ false };

private:
    IOMap& ioMap;                         // IOMap ���ޥ�          
    void delay(int milliseconds);         // ��������
};

#endif // EMERGENCYSTOP_H

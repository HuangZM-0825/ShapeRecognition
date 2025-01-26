#ifndef EMERGENCYSTOP_H
#define EMERGENCYSTOP_H

#include "IOMap.h"
#include <chrono>
#include <thread>
#include <iostream>

class EmergencyStop {
public:
    explicit EmergencyStop(IOMap& ioMap); // 構造函數

    // 復歸流程
    void handleReset();

    // 復歸完成旗標
    std::atomic_bool resetCompleted{ false };

private:
    IOMap& ioMap;                         // IOMap 的引用          
    void delay(int milliseconds);         // 模擬延遲
};

#endif // EMERGENCYSTOP_H

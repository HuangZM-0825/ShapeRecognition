#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#include "IOMap.h"
#include "MachineController.h"

// 這個函式負責跑設備控制的無限迴圈邏輯
// 注意：它可能會堵塞當前執行緒。
void runDeviceControl(IOMap& ioMap, MachineController& machineCtrl);

#endif // DEVICECONTROL_H

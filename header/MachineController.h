#ifndef MACHINECONTROLLER_H // 如果 MACHINECONTROLLER_H 尚未定義
#define MACHINECONTROLLER_H // 定義 MACHINECONTROLLER_H

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

    void runManual();      // 執行手動模式
    void runContinuous();  // 執行連續循環流程
    void runSingle();      // 執行單一循環流程
    void runMainProcess(); // 主流程函數

    // 非阻塞檢測的接口：開始進入「Step2」流程
    void runStep2();

    // 設定計數 (若從外部 UI 傳進來)
    void setCircleCount(int count);
    void setSquareCount(int count);
    // 取得計數 (若 UI 要讀回來顯示)
    int getCircleCount() const { return circleCount; }
    int getSquareCount() const { return squareCount; }

    bool isCycleRunning() const;

signals:
    void countsUpdated(int circleCount, int squareCount);

private:
    IOMap& ioMap; // 引用 IOMap，與 IO 交互，不會拷貝 IOMap，而是直接操作傳遞進來的 IOMap 實例。
    // 避免拷貝開銷 : 較大的物件，拷貝它會浪費內存和計算資源。
    // 保持一致性 : 如果有多個模組需要操作同一個 IOMap，使用引用確保所有模組看到的是同一個 IOMap 實例。

    // 主動檢查急停
    bool checkEmergencyStop();

    // 功能函式
    void handleCircleMaterial(); // 處理圓料邏輯
    void handleSquareMaterial(); // 處理方料邏輯

    // 內部輔助函數
    void delay(int milliseconds); // 模擬動作延遲

    bool isCircle;    // 用於記錄當前料件類型
    bool skipToStep2; // 用於記錄是否跳過步驟 1

    // 用於記錄當前料件數量
    // mutable std::mutex countMutex; // 保護 circleCount 和 squareCount
    int circleCount = 0;
    int squareCount = 0;

    mutable std::mutex countMutex; // 保護 circleCount 和 squareCount
    mutable std::mutex cycleMutex; // 保護 isRunningCycle

    bool isRunningCycle; // 循環狀態標誌
};

#endif // MACHINECONTROLLER_H

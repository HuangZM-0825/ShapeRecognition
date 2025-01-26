#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QLCDNumber>
#include <QTimer>

#include "header/IOMap.h"
#include "MachineController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT  //這個類別能使用 Qt 的 signal/slot、metaobject 系統


public:
    // 接收 IOMap & 以及 MachineController &
    // 這就保證在 UI 層面只拿到外部創建好的那同一個 IOMap、同一個 MachineController。不會自行建立新的物件。
    // explicit : 以防止任何不小心的隱式轉換。
    explicit MainWindow(IOMap& ioRef, MachineController& mCtrl, QWidget* parent = nullptr);
    ~MainWindow() override; // 加上解構子的宣告


public slots:
    void updateCounts(int circleCount, int squareCount); // 更新料件計數的槽函式


// 私有成員
private:
    // 這裡存放參考（reference）給 UI 用，不會在 MainWindow 內部重新宣告或 new 出新的 IOMap/MachineController。
    // 確保只有一個真正的物件實例。UI 只是拿到引用。
    Ui::MainWindow* ui;
    IOMap& ioMap;
    MachineController& machineCtrl;  // 引用主實例

    // 新增方法：更新按鈕與 QT 進行連動
    void setupConnections(); // 新增 setupConnections 聲明
    // 新增方法：更新 IO 點位與 QT 進行連動
    void updateIOStatus(); // 更新所有 Label 的狀態
    // 新增方法：更新元件觸發後 UI 顯示變化
    void updateLabelStatus(QLabel* label, bool status); // 更新 Label 狀態
    // 新增方法：更新三色燈號顯示
    void updateLightStatus(QLabel* label, bool lightOn, const QString& onStyle, const QString& offStyle);
};

#endif // MAINWINDOW_H

#include "mainwindow.h"

#include <QApplication>
#include <thread>                 // for std::thread

#include "header/IOMap.h"         // 包含 IOMap
#include "header/DeviceControl.h" // 包含 runDeviceControl()
#include "header/MachineController.h"

/**
 * @brief 主函式入口點，帶有 (argc, argv) 以支援命令列參數。
 *
 * 這是 C++ 的標準 main() 函式，但 Qt 程式使用時也會將 argc/argv 轉給 QApplication，用於初始化 GUI 環境。
 * 
 * Qt 程式通常需要從 main 函式傳遞參數給 QApplication，
 * 以正確初始化 Qt 內部機制（事件迴圈、GUI 顯示等）。
 */
int main(int argc, char* argv[])
{
    /**
     * @brief 建立 Qt 應用程式物件 (QApplication)。
     *
     * 此物件負責管理整個 GUI 事件迴圈、資源與初始化流程。
     * `argc`、`argv` 可用於解析命令列參數，若無特別需要也可直接帶入。
     * 
     * 通常要在主函式最前面建立，最後 a.exec() 進入事件迴圈，使 GUI 能互動。
     */
    QApplication a(argc, argv);

    // (1) 產生一次 IOMap 物件，並命名 sharedIOMap。  
    // 透過參考或指標來存取它，就能保證所有 I/O 狀態是一致且同步的。
    IOMap sharedIOMap;

    // (2) 建立唯一的 MachineController 物件，且將 sharedIOMap 傳入建構子。
    //     這樣 machineCtrl 與後續 DeviceControl、MainWindow 都會指向同一個物件，不會各自在程式裡再建一個 MachineController。
    MachineController machineCtrl(sharedIOMap); // 主實例

    // (3) 開啟一個執行緒跑 runDeviceControl(...)
    //     傳遞 sharedIOMap 和 machineCtrl 的引用
    std::thread devThread(runDeviceControl, std::ref(sharedIOMap), std::ref(machineCtrl));

    // (4) 將同一個 sharedIOMap 與 machineCtrl 傳給 MainWindow，以便 UI 端可以（例如）在「加一個方料」時呼叫 machineCtrl.setSquareCount(...)。
    //     你需要在 MainWindow 的建構子裡寫:
    //     MainWindow(IOMap& ioMap, MachineController& machineCtrl, QWidget* parent = nullptr);
    MainWindow w(sharedIOMap, machineCtrl);
    w.show();

    // (5) 分離執行緒（或根據需求選擇 join）
    devThread.detach(); // 如果你希望執行緒獨立運行，不需要等待它結束
    // devThread.join(); // 如果你希望主執行緒等待 devThread 結束

    // (6) 進入 Qt 事件迴圈
    return a.exec();
}
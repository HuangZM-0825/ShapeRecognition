#include "MachineController.h"
#include <iostream>
#include <QCoreApplication>        
#include <thread>
#include <chrono>


MachineController::MachineController(IOMap& ioMapRef, QObject* parent)
    : QObject(parent)
    , ioMap(ioMapRef)
    , isCircle(false)
    , skipToStep2(false)
    , circleCount(0)
    , squareCount(0)
    , isRunningCycle(false)
{
    // -----------------------------------------------------
    // 初始化可以寫在這
    // -----------------------------------------------------
    
    // 燈號設定
    ioMap.writeOutput(Output::GreenLight, true);   // 開啟待機燈
    ioMap.writeOutput(Output::YellowLight, false); // 熄滅復歸燈
    ioMap.writeOutput(Output::RedLight, false);    // 熄滅運轉燈

    // 原點設定
    ioMap.setInputState(Input::CylinderUpLimit, true);  // 氣缸原點位置
    ioMap.setInputState(Input::ArmPosition, true);      // 龍門手臂原點位置
}


// (延遲模擬)
void MachineController::delay(int milliseconds) 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


// 返回當前循環運行狀態
bool MachineController::isCycleRunning() const 
{
    std::lock_guard<std::mutex> lock(cycleMutex);
    return isRunningCycle;
}


// 檢查急停按鈕
bool MachineController::checkEmergencyStop()
{
    // 檢查 ioMap 是否讀到急停按鈕
    if (ioMap.readInput(Input::EmergencyStop)) {
        std::cout << "[DEBUG] Detected E-Stop inside MachineController, halting system..." << std::endl;

        // 關閉輸入點狀態
        ioMap.setInputState(Input::CylinderDownLimit, false);
        ioMap.setInputState(Input::CylinderUpLimit, false);
        ioMap.setInputState(Input::MaterialSensor, false);
        ioMap.setInputState(Input::ShapeCircleSensor, false);
        ioMap.setInputState(Input::ArmPosition, false);
        ioMap.setInputState(Input::CircleEjector, false);
        ioMap.setInputState(Input::SquareEjector, false);

        // 關閉輸出點狀態
        ioMap.writeOutput(Output::CylinderDown, false);
        ioMap.writeOutput(Output::ConveyorMotor, false);
        ioMap.writeOutput(Output::ArmMoveLeft, false);
        ioMap.writeOutput(Output::ArmMoveRight, false);
        ioMap.writeOutput(Output::GripperClose, false);
        ioMap.writeOutput(Output::GripperOpen, false);

        // 燈號全關(依需求調整)
        ioMap.writeOutput(Output::RedLight, false);
        ioMap.writeOutput(Output::YellowLight, false);
        ioMap.writeOutput(Output::GreenLight, false);

        // 回傳 true 表示偵測到急停
        return true;
    }
    // 否則沒有急停
    return false;
}


//（手動模式）
void MachineController::runManual() 
{
    std::cout << "[DEBUG] Entering Manual Mode." << std::endl;

    // 在手動模式的 while 裡，每一圈都檢查是否已被切換走
    while (true)
    {
        // -----------------------------------------------------
        // 檢查操作模式的切換
        // -----------------------------------------------------
        // (a) 檢查是否仍維持在「工作模式 Right + 手動模式 Manual」
        if (!ioMap.readInput(Input::ModeSwitch_Right) || !ioMap.readInput(Input::ModeSwitch_Manual)) {
            std::cout << "[DEBUG] Manual Mode switched off. Break runManual()." << std::endl;
            break;
        }
        // (b) 如果想支援「偵測切成 SingleCycle or Continuous」，也可以在這裡判斷
        if (ioMap.readInput(Input::ModeSwitch_SingleCycle) || ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] Detected user switching to Single/Continuous. Break runManual()." << std::endl;
            break;
        }
        // (c) 如果想支援「偵測切成 ModeSwitch_Left」，也可以在這裡判斷
        if (ioMap.readInput(Input::ModeSwitch_Left)) {
            std::cout << "[DEBUG] Detected user switched to Reset. Breaking manual loop..." << std::endl;
            break; 
        }
        
        // -----------------------------------------------------
        // 手動操作
        // -----------------------------------------------------
        // 關閉綠燈，並且開啟黃燈
        ioMap.writeOutput(Output::GreenLight, false);
        ioMap.writeOutput(Output::YellowLight, true);

        // 1. PB1：輸送帶控制
        if (ioMap.readInput(Input::ManualConveyor)) { // PB1 按下時
            std::cout << "Manual operation: Conveyor running." << std::endl;
            ioMap.writeOutput(Output::ConveyorMotor, true); // 啟動輸送帶
        }
        else {
            ioMap.writeOutput(Output::ConveyorMotor, false); // 停止輸送帶
        }

        // 2. PB2：垂直缸控制
        if (ioMap.readInput(Input::ManualACylinder)) { // PB2 按下時
            if (!ioMap.readInput(Input::CylinderDownLimit)) { // 如果下限感測器未觸發
                std::cout << "Manual operation: Cylinder moving down." << std::endl;
                ioMap.writeOutput(Output::CylinderDown, true); // 通電，垂直缸下降

                // 模擬感測器狀態變化
                ioMap.setInputState(Input::CylinderDownLimit, true); // 下限感測器觸發
                ioMap.setInputState(Input::CylinderUpLimit, false);  // 上限感測器不觸發
            }
            else {
                std::cerr << "Warning: Cylinder already at down limit." << std::endl;
            }
        }
        else { // 放開 PB2 時
            std::cout << "Manual operation: Cylinder moving up." << std::endl;
            ioMap.writeOutput(Output::CylinderDown, false); // 自動復位，垂直缸上升（不通電）

            // 模擬感測器狀態變化
            ioMap.setInputState(Input::CylinderDownLimit, false); // 下限感測器不觸發
            ioMap.setInputState(Input::CylinderUpLimit, true);    // 上限感測器觸發
        }

        // 3. PB3：龍門手臂左移
        if (ioMap.readInput(Input::ManualArmLeft)) { // PB3 按下時
            std::cout << "Manual operation: Arm moving left." << std::endl;
            ioMap.writeOutput(Output::ArmMoveLeft, true); // 龍門手臂左移
            ioMap.setInputState(Input::ArmPosition, false);  // 龍門手臂已被移動，原點失去需要重新復歸。
        }
        else {
            ioMap.writeOutput(Output::ArmMoveLeft, false); // 停止龍門手臂左移
        }

        // 4. PB4：龍門手臂右移
        if (ioMap.readInput(Input::ManualArmRight)) { // PB4 按下時
            std::cout << "Manual operation: Arm moving right." << std::endl;
            ioMap.writeOutput(Output::ArmMoveRight, true); // 龍門手臂右移
            ioMap.setInputState(Input::ArmPosition, false);  // 龍門手臂已被移動，原點失去需要重新復歸。
        }
        else {
            ioMap.writeOutput(Output::ArmMoveRight, false); // 停止龍門手臂右移
        }

        // 每次循環的延遲，避免過度檢查
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    ioMap.writeOutput(Output::YellowLight, false); // 跳出手動後，黃燈滅。
    std::cout << "Exiting Manual Mode." << std::endl;
}


// （連續循環模式）
void MachineController::runContinuous() {

    std::cout << "System is in Continuous Cycle Mode. Running continuous process..." << std::endl;

    while (true) 
    {
        // -----------------------------------------------------
        // 檢查操作模式的切換
        // -----------------------------------------------------
        // (a) 偵測是否已切換離開「連續模式」
        if (!ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] Continuous Mode switched off. Break runContinuous()." << std::endl;
            break;
        }
        // (b) 若想偵測是否被切到 Manual 或 Single
        if (ioMap.readInput(Input::ModeSwitch_Manual) || ioMap.readInput(Input::ModeSwitch_SingleCycle)) {
            std::cout << "[DEBUG] Detected user switching to Manual/SingleCycle. Break runContinuous()." << std::endl;
            break;
        }
        // (c) 如果想支援「偵測切成 ModeSwitch_Left」，也可以在這裡判斷
        if (ioMap.readInput(Input::ModeSwitch_Left)) {
            std::cout << "[DEBUG] Detected user switched to Reset. Breaking manual loop..." << std::endl;
            break;
        }

        // 執行初始化流程
        ioMap.writeOutput(Output::GreenLight, true);
        ioMap.writeOutput(Output::RedLight, false);  
        runMainProcess();

        // 急停檢查
        if (ioMap.readInput(Input::EmergencyStop)) { 
            std::cerr << "Emergency stop triggered during Continuous Cycle!" << std::endl;
            break; // 中斷連續循環
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 防止過於頻繁
    }
    std::cout << "Exiting Continuous Cycle Mode." << std::endl;
}


// （單一循環模式）
void MachineController::runSingle() 
{
    {
        std::lock_guard<std::mutex> lock(cycleMutex);
        // 若已在執行單一循環，就不再重複
        if (isRunningCycle) {
            std::cout << "[DEBUG] Cycle already running. Exiting runSingle." << std::endl;
            return;
        }
        isRunningCycle = true;
    }

    std::cout << "[DEBUG] Entering Single Cycle Mode. Running single process..." << std::endl;

    while (true)
    {
        // -----------------------------------------------------
        // (1) 檢查操作模式的切換
        // -----------------------------------------------------
        // (a) 若偵測不再是「單一循環」(X17)，就離開
        if (!ioMap.readInput(Input::ModeSwitch_SingleCycle)) {
            std::cout << "[DEBUG] SingleCycle Mode switched off. Break runSingle()." << std::endl;
            break;
        }

        // (b) 若偵測切到手動(X15)或連續模式(X16)，也要離開
        if (ioMap.readInput(Input::ModeSwitch_Manual) || ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] Detected user switching to Manual/Continuous. Break runSingle()." << std::endl;
            break;
        }

        // (c) 如果想支援「偵測切成復歸 (ModeSwitch_Left)(X13)」，也可以在這裡判斷
        if (ioMap.readInput(Input::ModeSwitch_Left)) {
            std::cout << "[DEBUG] Detected user switched to Reset (Left). Break runSingle()." << std::endl;
            break;
        }

        // -----------------------------------------------------
        // (2) 執行一次主流程
        // -----------------------------------------------------
        ioMap.writeOutput(Output::GreenLight, true);
        ioMap.writeOutput(Output::RedLight, false);
        runMainProcess();

        // -----------------------------------------------------
        // (3) 檢查急停
        // -----------------------------------------------------
        if (ioMap.readInput(Input::EmergencyStop)) {
            std::cerr << "[DEBUG] Emergency stop triggered during Single Cycle! Break runSingle()." << std::endl;
            break;
        }

        // 單一循環只執行一次，故執行完 mainProcess 後立即 break
        std::cout << "[DEBUG] Single cycle main process done. Break runSingle() loop." << std::endl;
        break;
    }

    // 跳出 while (true) 之後，代表整個單一循環流程結束
    {
        std::lock_guard<std::mutex> lock(cycleMutex);
        isRunningCycle = false;
    }

    std::cout << "[DEBUG] Exiting Single Cycle Mode." << std::endl;
}


// （設備模式切換判斷 & 原點啟動條件）
void MachineController::runMainProcess() {
    std::cout << "Main process starting..." << std::endl;

    // 新增邏輯：判斷是否跳過步驟 1
    if (skipToStep2) {
        std::cout << "Skipping Step 1 as per continuous mode logic. Proceeding directly to Step 2..." << std::endl;
        skipToStep2 = false; // 重置跳過標誌，確保下次執行正常
        runStep2();          // 直接進入步驟 2
        return;
    }

    // 步驟 1：初始化狀態確認
    if (ioMap.readInput(Input::ModeSwitch_Left) || ioMap.readInput(Input::EmergencyStop)) {
        std::cerr << "[ERROR] System is not ready for operation. Check Reset Mode or Emergency Stop." << std::endl;
        // Reset isRunningCycle if step 1 fails
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        return;
    }

    // 燈號設定
    /*
    ioMap.writeOutput(Output::GreenLight, true);   // 開啟待機燈
    ioMap.writeOutput(Output::YellowLight, false); // 熄滅復歸燈
    ioMap.writeOutput(Output::RedLight, false);    // 熄滅運轉燈
    */

   // -----------------------------------------------------
   // (1) 第一層大迴圈:
   //     在這裡檢查如果是手動 => 直接 return,
   //     如果是單一或連續 => break (往下走),
   //     否則就留在迴圈裡觀望。
   // -----------------------------------------------------
    while (true)
    {
        // (a) 若偵測為 Manual => 直接 return
        if (ioMap.readInput(Input::ModeSwitch_Manual)) {
            std::cout << "[DEBUG] Detected Manual => return from runMainProcess()" << std::endl;
            return; // 結束整個函式
        }

        // (b) 若偵測到 SingleCycle / Continuous => break
        if (ioMap.readInput(Input::ModeSwitch_SingleCycle) || ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] Detected Single or Continuous => break first loop" << std::endl;
            break; // 離開 while(true)，往下執行
        }

        //     避免跑得太頻繁，sleep一點時間
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // -----------------------------------------------------
    // (2) 第二層迴圈:
    //     走到這裡，表示已經在第一層判斷中「break」出來，
    //     也就是偵測到目前是 SingleCycle / Continuous 模式
    //     => 接著進入第二層小迴圈，等待 StartReset。
    // -----------------------------------------------------
    std::cout << "[DEBUG] Waiting for StartReset button to be pressed..." << std::endl;
    while (!ioMap.readInput(Input::StartReset))
    {
        // 假如在等待 StartReset 的過程中，又切到 Manual => 就直接 return
        if (ioMap.readInput(Input::ModeSwitch_Manual)) {
            std::cout << "[DEBUG] Switch to Manual => return from runMainProcess()" << std::endl;
            return;
        }

        // 也可以再檢查：如果 Single/Continuous 被關了，表示不再需要走下去
        if (!ioMap.readInput(Input::ModeSwitch_SingleCycle) &&
            !ioMap.readInput(Input::ModeSwitch_Continuous)) {
            std::cout << "[DEBUG] No longer in Single/Continuous => return" << std::endl;
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 每 0.5 秒檢查一次
    }
    std::cout << "[DEBUG] StartReset button pressed. Proceeding to Step 2..." << std::endl;

    // -----------------------------------------------------
    // (3) 原點條件檢查 (檢查 ArmPosition & CylinderUpLimit)
    //     若符合 => 執行下一階段流程: runStep2()
    //     重置 StartReset 為 false
    // -----------------------------------------------------
    if (!ioMap.readInput(Input::ArmPosition) || !ioMap.readInput(Input::CylinderUpLimit)) 
    {
        std::cerr << "[ERROR] Cannot start runStep2(): Arm or Cylinder not at origin!" << std::endl;
        // 直接 return，不執行後面
        return;
    }
    else
    {
        ioMap.setInputState(Input::StartReset, false); // 訊號重製
        runStep2();  // 進入步驟 2
    }
}

void MachineController::runStep2()
{
    // 步驟 1：判斷有沒有料
    // (假設 circleCount+squareCount>0 就表示有料)
    if ((circleCount + squareCount) > 0) {

        // [1] 檢查急停
        if (checkEmergencyStop()) return;

        // 表示有料 => 檢測成功
        delay(1000); // 需要緩一下，否則不會 UI 亮 (MaterialSensor)
        ioMap.setInputState(Input::MaterialSensor, true); // 料件感測器已偵測

        // 啟動流程燈號
        ioMap.writeOutput(Output::GreenLight, false);  // 熄滅待機燈
        ioMap.writeOutput(Output::RedLight, true);     // 啟動燈亮起

        // 步驟 1.1：輸送帶啟動
        std::cout << "Conveyor starting..." << std::endl;
        ioMap.writeOutput(Output::ConveyorMotor, true); // 啟動輸送帶
        delay(5000); // 模擬 T0 計時 5 秒

        // 停止輸送帶
        std::cout << "Conveyor stopping..." << std::endl;
        ioMap.writeOutput(Output::ConveyorMotor, false);

        // [2] 檢查急停
        if (checkEmergencyStop()) return;


        // 步驟 2：判斷物料形狀 (ShapeCircleSensor) 
        // 同理，如果 circleCount > 0，就把 ShapeCircleSensor 設為 true
        bool isCircle = false;
        if (circleCount > 0) {
            ioMap.setInputState(Input::ShapeCircleSensor, true);
            isCircle = true;  // 圓料
        }
        else {
            ioMap.setInputState(Input::ShapeCircleSensor, false);
            isCircle = false; // 方料
        }

        // [3] 檢查急停
        if (checkEmergencyStop()) return;

        // 步驟 2.1：讀取 Sensor 來顯示
        delay(1000); // 模擬 T1 計時 1 秒
        if (ioMap.readInput(Input::ShapeCircleSensor)) {
            std::cout << "Detected material: Circle." << std::endl;
        }
        else {
            std::cout << "Detected material: Square." << std::endl;
        }

        // [4] 檢查急停
        if (checkEmergencyStop()) return;

        // 步驟 3：垂直缸下降
        std::cout << "Cylinder moving down..." << std::endl;

        // 模擬垂直缸下降的動作
        ioMap.writeOutput(Output::CylinderDown, true);  // 啟動垂直缸下降

        // 模擬垂直缸下降的過程
        delay(1000);

        // 更新感測器狀態
        ioMap.setInputState(Input::CylinderDownLimit, true); // 模擬下限感測器觸發
        ioMap.setInputState(Input::CylinderUpLimit, false);  // 模擬上限感測器未觸發

        // [5] 檢查急停
        if (checkEmergencyStop()) return;

        // 確保垂直缸已經到達下限
        if (!ioMap.readInput(Input::CylinderDownLimit)) {
            std::cerr << "Error: Cylinder failed to reach down position!" << std::endl;
            // Reset isRunningCycle if step 3 fails
            {
                std::lock_guard<std::mutex> lock(cycleMutex);
                isRunningCycle = false;
            }
            return; // 終止流程
        }

        std::cout << "Cylinder reached down position. Proceeding to next step..." << std::endl;

        // [6] 檢查急停
        if (checkEmergencyStop()) return;

        // 步驟 4：氣壓夾爪關合
        std::cout << "Gripper closing..." << std::endl;

        // 啟動夾爪關合
        ioMap.writeOutput(Output::GripperClose, true); // 啟動夾爪關合動作

        // 模擬 T2 計時 1 秒
        delay(1000);

        // 停止夾爪關合
        ioMap.writeOutput(Output::GripperClose, false); // 停止夾爪關合動作

        std::cout << "Gripper closed. Proceeding to next step..." << std::endl;

        // [7] 檢查急停
        if (checkEmergencyStop()) return;

        // 步驟 5：垂直缸上升
        std::cout << "Cylinder moving up..." << std::endl;

        // 啟動垂直缸上升
        ioMap.writeOutput(Output::CylinderDown, false); // 垂直缸上升

        // 模擬垂直缸上升的過程
        delay(1000);

        // 更新感測器狀態
        ioMap.setInputState(Input::CylinderDownLimit, false); // 模擬下限感測器未觸發
        ioMap.setInputState(Input::CylinderUpLimit, true); // 啟動上升動作
        ioMap.setInputState(Input::MaterialSensor, false); // 料件感測器未偵測
        ioMap.setInputState(Input::ShapeCircleSensor, false); // 料件此時已被夾走

        // 確保垂直缸已經到達上限
        if (!ioMap.readInput(Input::CylinderUpLimit)) {
            std::cerr << "[ERROR] Cylinder failed to reach up position!" << std::endl;
            // Reset isRunningCycle if step 5 fails
            {
                std::lock_guard<std::mutex> lock(cycleMutex);
                isRunningCycle = false;
            }
            return; // 終止流程
        }

        std::cout << "[DEBUG] Cylinder reached up position. Proceeding to next step..." << std::endl;

        // [8] 檢查急停
        if (checkEmergencyStop()) return;

        // 步驟 6：龍門手臂左移
        std::cout << "Moving gantry arm left..." << std::endl;

        if (isCircle) {
            handleCircleMaterial(); // 呼叫圓料的處理函式
        }
        else {
            handleSquareMaterial(); // 呼叫方料的處理函式
        }

        std::cout << "Gantry arm moved to position. Proceeding to next step..." << std::endl;
        return;
    }
}


// 圓料處理函式
void MachineController::handleCircleMaterial() {
    std::cout << "Handling circle material. Moving gantry arm left..." << std::endl;

    // [1] 檢查急停
    if (checkEmergencyStop()) return;

    ioMap.writeOutput(Output::ArmMoveLeft, true);   // 啟動左移
    ioMap.setInputState(Input::ArmPosition, false);  // 龍門手臂非原點位置
    delay(3000); // 模擬 3 秒移動時間（圓料）

    // [2] 檢查急停
    if (checkEmergencyStop()) return;

    // 步驟 7：停止移動手臂，執行氣壓夾爪打開
    std::cout << "Stopping gantry arm and releasing gripper (B-)..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveLeft, false); // 停止左移
    ioMap.writeOutput(Output::GripperOpen, true);  // 執行夾爪打開動作（B-）

    delay(1000); // 模擬 1 秒

    ioMap.writeOutput(Output::GripperOpen, false); // 停止夾爪動作
    std::cout << "Gripper released. Proceeding to next step..." << std::endl;

    //  步驟 7.1：圓料排料位
    ioMap.setInputState(Input::CircleEjector, true);
    delay(1500); // 模擬 1.5 秒
    ioMap.setInputState(Input::CircleEjector, false);

    // [3] 檢查急停
    if (checkEmergencyStop()) return;


    // 步驟 8：龍門手臂右移回初始位置
    std::cout << "Moving gantry arm right to initial position..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveRight, true); // 啟動右移
    delay(3000); // 模擬 3 秒移動時間

    std::cout << "Gantry arm returned to initial position. Proceeding to next step..." << std::endl;


    // 步驟 9：螺桿機械手臂停止、清除記憶
    std::cout << "Stopping gantry arm and clearing memory..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveRight, false); // 停止右移

    // 龍門手臂回到原點位置
    ioMap.setInputState(Input::ArmPosition, true);  // 龍門手臂原點位置

    // [4] 檢查急停
    if (checkEmergencyStop()) return;

    // 在流程結束時, 把（circleCount 減 1）
    if (circleCount > 0) {
        circleCount--;
        std::cout << "circleCount now = " << circleCount << std::endl;
        emit countsUpdated(circleCount, squareCount);
    }

    // 判斷模式並決定流程
    if (ioMap.readInput(Input::ModeSwitch_Continuous)) { // 判斷是否為連續循環模式
        std::cout << "Mode: Continuous Cycle. Returning to step 2." << std::endl;
        skipToStep2 = true; // 設置標誌，跳過步驟 1
        runContinuous(); // 回到連續循環模式，再次檢查按鈕是否改變狀態
    }
    else {
        std::cout << "Mode: Single Cycle. Returning to idle state." << std::endl;
        skipToStep2 = false; // 清除標誌
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        emit countsUpdated(circleCount, squareCount);
    }
}

// 方料處理函式
void MachineController::handleSquareMaterial() {
    std::cout << "Handling square material. Moving gantry arm left..." << std::endl;

    // [1] 檢查急停
    if (checkEmergencyStop()) return;

    // 步驟 17-1：啟動手臂左移
    ioMap.writeOutput(Output::ArmMoveLeft, true);    // 啟動左移
    ioMap.setInputState(Input::ArmPosition, false);  // 龍門手臂非原點位置
    delay(5000); // 模擬 5 秒移動時間（方料）

    // 步驟 17-2：停止移動手臂，垂直缸下降
    std::cout << "Stopping gantry arm and Cylinder moving down..." << std::endl;

    // [2] 檢查急停
    if (checkEmergencyStop()) return;

    // 停止移動手臂，啟動垂直缸下降
    ioMap.writeOutput(Output::ArmMoveLeft, false); // 停止左移
    ioMap.writeOutput(Output::CylinderDown, true); // 垂直缸下降

    // [3] 檢查急停
    if (checkEmergencyStop()) return;

    // 模擬垂直缸下降的過程
    delay(1000);

    // 更新感測器狀態
    ioMap.setInputState(Input::CylinderDownLimit, true); // 模擬下限感測器觸發
    ioMap.setInputState(Input::CylinderUpLimit, false);  // 模擬上限感測器未觸發

    // 確保垂直缸已經到達下限
    if (!ioMap.readInput(Input::CylinderDownLimit)) {
        std::cerr << "Error: Cylinder failed to reach down position!" << std::endl;
        // Reset isRunningCycle if step 17-2 fails
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        return; // 終止流程
    }

    std::cout << "Cylinder reached down position. Proceeding to next step..." << std::endl;

    // [4] 檢查急停
    if (checkEmergencyStop()) return;


    // 步驟 18：氣壓夾爪打開
    std::cout << "Gripper opening (B-)..." << std::endl;

    // 啟動夾爪打開動作
    ioMap.writeOutput(Output::GripperOpen, true);  // 執行夾爪打開動作（B-）

    delay(1000); // 模擬 1 秒

    // 停止夾爪動作
    ioMap.writeOutput(Output::GripperOpen, false); // 停止夾爪動作

    std::cout << "Gripper released. Proceeding to next step..." << std::endl;

    //  步驟 18.1：方料排料位
    ioMap.setInputState(Input::SquareEjector, true);
    delay(1500); // 模擬 1.5 秒
    ioMap.setInputState(Input::SquareEjector, false);

    // [5] 檢查急停
    if (checkEmergencyStop()) return;

    //步驟 19：垂直缸上降
    std::cout << "Cylinder moving up..." << std::endl;

    // 啟動垂直缸上降
    ioMap.writeOutput(Output::CylinderDown, false);

    // 模擬垂直缸下降的過程
    delay(1000);

    // 更新感測器狀態
    ioMap.setInputState(Input::CylinderDownLimit, false); // 模擬下限感測器未觸發
    ioMap.setInputState(Input::CylinderUpLimit, true);  // 模擬上限感測器觸發

    // 確保垂直缸已經到達上限
    if (!ioMap.readInput(Input::CylinderUpLimit)) {
        std::cerr << "Error: Cylinder failed to reach up position!" << std::endl;
        // Reset isRunningCycle if step 19 fails
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        return; // 終止流程
    }

    std::cout << "Cylinder reached up position successfully. Proceeding to next step..." << std::endl;

    // [6] 檢查急停
    if (checkEmergencyStop()) return;


    // 步驟 8：龍門手臂右移回初始位置
    std::cout << "Moving gantry arm right to initial position..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveRight, true); // 啟動右移
    delay(3000); // 模擬 3 秒移動時間

    std::cout << "Gantry arm returned to initial position. Proceeding to next step..." << std::endl;


    // 步驟 9：螺桿機械手臂停止、清除記憶
    std::cout << "Stopping gantry arm and clearing memory..." << std::endl;

    ioMap.writeOutput(Output::ArmMoveRight, false); // 停止右移

    // 龍門手臂回到原點位置
    ioMap.setInputState(Input::ArmPosition, true);  // 龍門手臂原點位置

    // [7] 檢查急停
    if (checkEmergencyStop()) return;

    // 在流程結束時, 把（squareCount 減 1）
    if (squareCount > 0) {
        squareCount--;
        std::cout << "squareCount now = " << squareCount << std::endl;
        emit countsUpdated(circleCount, squareCount);
    }

    // 判斷模式並決定流程
    if (ioMap.readInput(Input::ModeSwitch_Continuous)) { // 判斷是否為連續循環模式
        std::cout << "Mode: Continuous Cycle. Returning to step 2." << std::endl;
        skipToStep2 = true; // 設置標誌，跳過步驟 1
        runContinuous(); // 回到連續循環模式，再次檢查按鈕是否改變狀態
    }
    else {
        std::cout << "Mode: Single Cycle. Returning to idle state." << std::endl;
        skipToStep2 = false; // 清除標誌
        {
            std::lock_guard<std::mutex> lock(cycleMutex);
            isRunningCycle = false;
        }
        emit countsUpdated(circleCount, squareCount);
    }
}

// 設定圓料計數
void MachineController::setCircleCount(int count) 
{
    {
        std::lock_guard<std::mutex> lock(countMutex);
        circleCount = count;
    }
    std::cout << "[DEBUG] circleCount set to " << circleCount << std::endl;
    emit countsUpdated(circleCount, squareCount);
}

// 設定方料計數
void MachineController::setSquareCount(int count) 
{
    {
        std::lock_guard<std::mutex> lock(countMutex);
        squareCount = count;
    }
    std::cout << "[DEBUG] squareCount set to " << squareCount << std::endl;
    emit countsUpdated(circleCount, squareCount);
}

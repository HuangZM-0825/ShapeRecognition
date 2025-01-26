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
    Q_OBJECT  //�o�����O��ϥ� Qt �� signal/slot�Bmetaobject �t��


public:
    // ���� IOMap & �H�� MachineController &
    // �o�N�O�Ҧb UI �h���u����~���Ыئn�����P�@�� IOMap�B�P�@�� MachineController�C���|�ۦ�إ߷s������C
    // explicit : �H������󤣤p�ߪ������ഫ�C
    explicit MainWindow(IOMap& ioRef, MachineController& mCtrl, QWidget* parent = nullptr);
    ~MainWindow() override; // �[�W�Ѻc�l���ŧi


public slots:
    void updateCounts(int circleCount, int squareCount); // ��s�ƥ�p�ƪ��Ѩ禡


// �p������
private:
    // �o�̦s��Ѧҡ]reference�^�� UI �ΡA���|�b MainWindow �������s�ŧi�� new �X�s�� IOMap/MachineController�C
    // �T�O�u���@�ӯu���������ҡCUI �u�O����ޥΡC
    Ui::MainWindow* ui;
    IOMap& ioMap;
    MachineController& machineCtrl;  // �ޥΥD���

    // �s�W��k�G��s���s�P QT �i��s��
    void setupConnections(); // �s�W setupConnections �n��
    // �s�W��k�G��s IO �I��P QT �i��s��
    void updateIOStatus(); // ��s�Ҧ� Label �����A
    // �s�W��k�G��s����Ĳ�o�� UI ����ܤ�
    void updateLabelStatus(QLabel* label, bool status); // ��s Label ���A
    // �s�W��k�G��s�T��O�����
    void updateLightStatus(QLabel* label, bool lightOn, const QString& onStyle, const QString& offStyle);
};

#endif // MAINWINDOW_H

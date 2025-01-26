/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_Left_3;
    QLabel *label_Model;
    QRadioButton *radioButton_SingleCycle;
    QRadioButton *radioButton_Continuous;
    QRadioButton *radioButton_Manual;
    QVBoxLayout *verticalLayout_Left_6;
    QLabel *label_Y;
    QLabel *label_A;
    QLabel *label_R1;
    QLabel *label_R2;
    QLabel *label_R3;
    QLabel *label_P_B;
    QLabel *label_N_B;
    QLabel *label_RL;
    QLabel *label_YL;
    QLabel *label_GL;
    QFrame *verticalFrame_Top;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_Top;
    QVBoxLayout *verticalLayout_Left_5;
    QLabel *label_X;
    QLabel *label_a1;
    QLabel *label_a0;
    QLabel *label_s0;
    QLabel *label_s1;
    QLabel *label_p0;
    QLabel *label_p1;
    QLabel *label_p2;
    QVBoxLayout *verticalLayout_Left_1;
    QLabel *label_Manual;
    QPushButton *pushButton_ManualConveyor;
    QPushButton *pushButton_ManualACylinder;
    QPushButton *pushButton_ManualArmLeft;
    QPushButton *pushButton_ManualArmRight;
    QVBoxLayout *verticalLayout_Left_2;
    QLabel *label_Operate;
    QCheckBox *checkBox_Rst;
    QRadioButton *radioButton__Work;
    QPushButton *pushButton_St_Rst;
    QPushButton *pushButton_EMS;
    QVBoxLayout *verticalLayout_Left_4;
    QLabel *label_material;
    QLCDNumber *lcdNumber_Circle;
    QPushButton *pushButton_AddCircle;
    QPushButton *pushButton_SubCircle;
    QLCDNumber *lcdNumber_Square;
    QPushButton *pushButton_AddSquare;
    QPushButton *pushButton_SubSquare;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(950, 546);
        MainWindow->setMaximumSize(QSize(950, 546));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(212, 255, 250);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_Left_3 = new QVBoxLayout();
        verticalLayout_Left_3->setObjectName("verticalLayout_Left_3");
        label_Model = new QLabel(centralwidget);
        label_Model->setObjectName("label_Model");
        label_Model->setMinimumSize(QSize(0, 50));
        label_Model->setMaximumSize(QSize(16777215, 50));
        label_Model->setStyleSheet(QString::fromUtf8("QLabel#label_Model {\n"
"    font-size: 15px;       /* \345\255\227\351\253\224\345\244\247\345\260\217 */\n"
"    font-weight: bold;     /* \347\262\227\351\253\224 */\n"
"    color: #2E86C1;        /* \345\255\227\351\253\224\351\241\217\350\211\262 */\n"
"    text-align: center;    /* \345\261\205\344\270\255\345\260\215\351\275\212 */\n"
"    background-color: #F4F6F7; /* \350\203\214\346\231\257\351\241\217\350\211\262 */\n"
"    border: 2px solid #ABB2B9; /* \351\202\212\346\241\206\346\250\243\345\274\217 */\n"
"    padding: 10px;         /* \345\205\247\351\202\212\350\267\235 */\n"
"    border-radius: 5px;    /* \351\202\212\345\257\254\345\234\223\350\247\222 */\n"
"}"));
        label_Model->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_Left_3->addWidget(label_Model);

        radioButton_SingleCycle = new QRadioButton(centralwidget);
        radioButton_SingleCycle->setObjectName("radioButton_SingleCycle");
        radioButton_SingleCycle->setMaximumSize(QSize(16777215, 40));
        radioButton_SingleCycle->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}"));

        verticalLayout_Left_3->addWidget(radioButton_SingleCycle);

        radioButton_Continuous = new QRadioButton(centralwidget);
        radioButton_Continuous->setObjectName("radioButton_Continuous");
        radioButton_Continuous->setMaximumSize(QSize(16777215, 40));
        radioButton_Continuous->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}"));

        verticalLayout_Left_3->addWidget(radioButton_Continuous);

        radioButton_Manual = new QRadioButton(centralwidget);
        radioButton_Manual->setObjectName("radioButton_Manual");
        radioButton_Manual->setMaximumSize(QSize(16777215, 40));
        radioButton_Manual->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}"));

        verticalLayout_Left_3->addWidget(radioButton_Manual);


        gridLayout->addLayout(verticalLayout_Left_3, 3, 2, 1, 1);

        verticalLayout_Left_6 = new QVBoxLayout();
        verticalLayout_Left_6->setObjectName("verticalLayout_Left_6");
        label_Y = new QLabel(centralwidget);
        label_Y->setObjectName("label_Y");
        label_Y->setMinimumSize(QSize(0, 50));
        label_Y->setMaximumSize(QSize(16777215, 50));
        label_Y->setStyleSheet(QString::fromUtf8("QLabel#label_Y {\n"
"    font-size: 15px;       /* \345\255\227\351\253\224\345\244\247\345\260\217 */\n"
"    font-weight: bold;     /* \347\262\227\351\253\224 */\n"
"    color: #2E86C1;        /* \345\255\227\351\253\224\351\241\217\350\211\262 */\n"
"    text-align: center;    /* \345\261\205\344\270\255\345\260\215\351\275\212 */\n"
"    background-color: #F4F6F7; /* \350\203\214\346\231\257\351\241\217\350\211\262 */\n"
"    border: 2px solid #ABB2B9; /* \351\202\212\346\241\206\346\250\243\345\274\217 */\n"
"    padding: 10px;         /* \345\205\247\351\202\212\350\267\235 */\n"
"    border-radius: 5px;    /* \351\202\212\345\257\254\345\234\223\350\247\222 */\n"
"}"));
        label_Y->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_Left_6->addWidget(label_Y);

        label_A = new QLabel(centralwidget);
        label_A->setObjectName("label_A");
        label_A->setMaximumSize(QSize(16777215, 40));
        label_A->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_6->addWidget(label_A);

        label_R1 = new QLabel(centralwidget);
        label_R1->setObjectName("label_R1");
        label_R1->setMaximumSize(QSize(16777215, 40));
        label_R1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_6->addWidget(label_R1);

        label_R2 = new QLabel(centralwidget);
        label_R2->setObjectName("label_R2");
        label_R2->setMaximumSize(QSize(16777215, 40));
        label_R2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_6->addWidget(label_R2);

        label_R3 = new QLabel(centralwidget);
        label_R3->setObjectName("label_R3");
        label_R3->setMaximumSize(QSize(16777215, 40));
        label_R3->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_6->addWidget(label_R3);

        label_P_B = new QLabel(centralwidget);
        label_P_B->setObjectName("label_P_B");
        label_P_B->setMaximumSize(QSize(16777215, 40));
        label_P_B->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_6->addWidget(label_P_B);

        label_N_B = new QLabel(centralwidget);
        label_N_B->setObjectName("label_N_B");
        label_N_B->setMaximumSize(QSize(16777215, 40));
        label_N_B->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_6->addWidget(label_N_B);

        label_RL = new QLabel(centralwidget);
        label_RL->setObjectName("label_RL");
        label_RL->setMaximumSize(QSize(16777215, 40));
        label_RL->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_6->addWidget(label_RL);

        label_YL = new QLabel(centralwidget);
        label_YL->setObjectName("label_YL");
        label_YL->setMaximumSize(QSize(16777215, 40));
        label_YL->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_6->addWidget(label_YL);

        label_GL = new QLabel(centralwidget);
        label_GL->setObjectName("label_GL");
        label_GL->setMaximumSize(QSize(16777215, 40));
        label_GL->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_6->addWidget(label_GL);


        gridLayout->addLayout(verticalLayout_Left_6, 3, 5, 1, 1);

        verticalFrame_Top = new QFrame(centralwidget);
        verticalFrame_Top->setObjectName("verticalFrame_Top");
        verticalFrame_Top->setMinimumSize(QSize(0, 60));
        verticalFrame_Top->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_8 = new QHBoxLayout(verticalFrame_Top);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_Top = new QLabel(verticalFrame_Top);
        label_Top->setObjectName("label_Top");
        label_Top->setEnabled(true);
        label_Top->setMinimumSize(QSize(0, 50));
        label_Top->setMaximumSize(QSize(16777215, 50));
        label_Top->setStyleSheet(QString::fromUtf8("QLabel#label_Top {\n"
"    font-size: 24px;       /* \345\255\227\351\253\224\345\244\247\345\260\217 */\n"
"    font-weight: bold;     /* \347\262\227\351\253\224 */\n"
"    color: #2E86C1;        /* \345\255\227\351\253\224\351\241\217\350\211\262 */\n"
"    text-align: center;    /* \345\261\205\344\270\255\345\260\215\351\275\212 */\n"
"    background-color: #F4F6F7; /* \350\203\214\346\231\257\351\241\217\350\211\262 */\n"
"    border: 2px solid #ABB2B9; /* \351\202\212\346\241\206\346\250\243\345\274\217 */\n"
"    padding: 10px;         /* \345\205\247\351\202\212\350\267\235 */\n"
"    border-radius: 5px;    /* \351\202\212\345\257\254\345\234\223\350\247\222 */\n"
"}"));
        label_Top->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_8->addWidget(label_Top);


        gridLayout->addWidget(verticalFrame_Top, 2, 0, 1, 6);

        verticalLayout_Left_5 = new QVBoxLayout();
        verticalLayout_Left_5->setObjectName("verticalLayout_Left_5");
        label_X = new QLabel(centralwidget);
        label_X->setObjectName("label_X");
        label_X->setMinimumSize(QSize(0, 50));
        label_X->setMaximumSize(QSize(16777215, 50));
        label_X->setStyleSheet(QString::fromUtf8("QLabel#label_X {\n"
"    font-size: 15px;       /* \345\255\227\351\253\224\345\244\247\345\260\217 */\n"
"    font-weight: bold;     /* \347\262\227\351\253\224 */\n"
"    color: #2E86C1;        /* \345\255\227\351\253\224\351\241\217\350\211\262 */\n"
"    text-align: center;    /* \345\261\205\344\270\255\345\260\215\351\275\212 */\n"
"    background-color: #F4F6F7; /* \350\203\214\346\231\257\351\241\217\350\211\262 */\n"
"    border: 2px solid #ABB2B9; /* \351\202\212\346\241\206\346\250\243\345\274\217 */\n"
"    padding: 10px;         /* \345\205\247\351\202\212\350\267\235 */\n"
"    border-radius: 5px;    /* \351\202\212\345\257\254\345\234\223\350\247\222 */\n"
"}"));
        label_X->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_Left_5->addWidget(label_X);

        label_a1 = new QLabel(centralwidget);
        label_a1->setObjectName("label_a1");
        label_a1->setMaximumSize(QSize(16777215, 40));
        label_a1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_5->addWidget(label_a1);

        label_a0 = new QLabel(centralwidget);
        label_a0->setObjectName("label_a0");
        label_a0->setMaximumSize(QSize(16777215, 40));
        label_a0->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_5->addWidget(label_a0);

        label_s0 = new QLabel(centralwidget);
        label_s0->setObjectName("label_s0");
        label_s0->setMaximumSize(QSize(16777215, 40));
        label_s0->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_5->addWidget(label_s0);

        label_s1 = new QLabel(centralwidget);
        label_s1->setObjectName("label_s1");
        label_s1->setMaximumSize(QSize(16777215, 40));
        label_s1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_5->addWidget(label_s1);

        label_p0 = new QLabel(centralwidget);
        label_p0->setObjectName("label_p0");
        label_p0->setMaximumSize(QSize(16777215, 40));
        label_p0->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_5->addWidget(label_p0);

        label_p1 = new QLabel(centralwidget);
        label_p1->setObjectName("label_p1");
        label_p1->setMaximumSize(QSize(16777215, 40));
        label_p1->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_5->addWidget(label_p1);

        label_p2 = new QLabel(centralwidget);
        label_p2->setObjectName("label_p2");
        label_p2->setMaximumSize(QSize(16777215, 40));
        label_p2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: lightgray; /* \346\240\207\347\255\276\350\203\214\346\231\257\350\211\262 */\n"
"    border: 1px solid black;    /* \351\273\221\350\211\262\350\276\271\346\241\206 */\n"
"    border-radius: 5px;         /* \345\234\206\350\247\222\350\276\271\346\241\206 */\n"
"    color: darkblue;            /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 10px;            /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;          /* \345\255\227\344\275\223\345\212\240\347\262\227 */\n"
"    padding: 5px;               /* \345\206\205\350\276\271\350\267\235 */\n"
"    text-align: center;         /* \346\226\207\346\234\254\345\261\205\344\270\255 */\n"
"    min-width: 50px;            /* \346\234\200\345\260\217\345\256\275\345\272\246 */\n"
"    min-height: 20px;           /* \346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
""));

        verticalLayout_Left_5->addWidget(label_p2);


        gridLayout->addLayout(verticalLayout_Left_5, 3, 4, 1, 1);

        verticalLayout_Left_1 = new QVBoxLayout();
        verticalLayout_Left_1->setObjectName("verticalLayout_Left_1");
        label_Manual = new QLabel(centralwidget);
        label_Manual->setObjectName("label_Manual");
        label_Manual->setMinimumSize(QSize(0, 50));
        label_Manual->setMaximumSize(QSize(16777215, 50));
        label_Manual->setStyleSheet(QString::fromUtf8("QLabel#label_Manual {\n"
"    font-size: 15px;       /* \345\255\227\351\253\224\345\244\247\345\260\217 */\n"
"    font-weight: bold;     /* \347\262\227\351\253\224 */\n"
"    color: #2E86C1;        /* \345\255\227\351\253\224\351\241\217\350\211\262 */\n"
"    text-align: center;    /* \345\261\205\344\270\255\345\260\215\351\275\212 */\n"
"    background-color: #F4F6F7; /* \350\203\214\346\231\257\351\241\217\350\211\262 */\n"
"    border: 2px solid #ABB2B9; /* \351\202\212\346\241\206\346\250\243\345\274\217 */\n"
"    padding: 10px;         /* \345\205\247\351\202\212\350\267\235 */\n"
"    border-radius: 5px;    /* \351\202\212\345\257\254\345\234\223\350\247\222 */\n"
"}"));
        label_Manual->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_Left_1->addWidget(label_Manual);

        pushButton_ManualConveyor = new QPushButton(centralwidget);
        pushButton_ManualConveyor->setObjectName("pushButton_ManualConveyor");
        pushButton_ManualConveyor->setMaximumSize(QSize(16777215, 40));
        pushButton_ManualConveyor->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_1->addWidget(pushButton_ManualConveyor);

        pushButton_ManualACylinder = new QPushButton(centralwidget);
        pushButton_ManualACylinder->setObjectName("pushButton_ManualACylinder");
        pushButton_ManualACylinder->setMaximumSize(QSize(16777215, 40));
        pushButton_ManualACylinder->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_1->addWidget(pushButton_ManualACylinder);

        pushButton_ManualArmLeft = new QPushButton(centralwidget);
        pushButton_ManualArmLeft->setObjectName("pushButton_ManualArmLeft");
        pushButton_ManualArmLeft->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_1->addWidget(pushButton_ManualArmLeft);

        pushButton_ManualArmRight = new QPushButton(centralwidget);
        pushButton_ManualArmRight->setObjectName("pushButton_ManualArmRight");
        pushButton_ManualArmRight->setMinimumSize(QSize(0, 40));
        pushButton_ManualArmRight->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_1->addWidget(pushButton_ManualArmRight);


        gridLayout->addLayout(verticalLayout_Left_1, 3, 0, 1, 1);

        verticalLayout_Left_2 = new QVBoxLayout();
        verticalLayout_Left_2->setObjectName("verticalLayout_Left_2");
        label_Operate = new QLabel(centralwidget);
        label_Operate->setObjectName("label_Operate");
        label_Operate->setMinimumSize(QSize(0, 50));
        label_Operate->setMaximumSize(QSize(16777215, 50));
        label_Operate->setStyleSheet(QString::fromUtf8("QLabel#label_Operate {\n"
"    font-size: 15px;       /* \345\255\227\351\253\224\345\244\247\345\260\217 */\n"
"    font-weight: bold;     /* \347\262\227\351\253\224 */\n"
"    color: #2E86C1;        /* \345\255\227\351\253\224\351\241\217\350\211\262 */\n"
"    text-align: center;    /* \345\261\205\344\270\255\345\260\215\351\275\212 */\n"
"    background-color: #F4F6F7; /* \350\203\214\346\231\257\351\241\217\350\211\262 */\n"
"    border: 2px solid #ABB2B9; /* \351\202\212\346\241\206\346\250\243\345\274\217 */\n"
"    padding: 10px;         /* \345\205\247\351\202\212\350\267\235 */\n"
"    border-radius: 5px;    /* \351\202\212\345\257\254\345\234\223\350\247\222 */\n"
"}"));
        label_Operate->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_Left_2->addWidget(label_Operate);

        checkBox_Rst = new QCheckBox(centralwidget);
        checkBox_Rst->setObjectName("checkBox_Rst");
        checkBox_Rst->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QCheckBox:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"Q"
                        "CheckBox:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}"));

        verticalLayout_Left_2->addWidget(checkBox_Rst);

        radioButton__Work = new QRadioButton(centralwidget);
        radioButton__Work->setObjectName("radioButton__Work");
        radioButton__Work->setStyleSheet(QString::fromUtf8("QRadioButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}"));

        verticalLayout_Left_2->addWidget(radioButton__Work);

        pushButton_St_Rst = new QPushButton(centralwidget);
        pushButton_St_Rst->setObjectName("pushButton_St_Rst");
        pushButton_St_Rst->setMaximumSize(QSize(16777215, 40));
        pushButton_St_Rst->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_2->addWidget(pushButton_St_Rst);

        pushButton_EMS = new QPushButton(centralwidget);
        pushButton_EMS->setObjectName("pushButton_EMS");
        pushButton_EMS->setMaximumSize(QSize(16777215, 40));
        pushButton_EMS->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_2->addWidget(pushButton_EMS);


        gridLayout->addLayout(verticalLayout_Left_2, 3, 1, 1, 1);

        verticalLayout_Left_4 = new QVBoxLayout();
        verticalLayout_Left_4->setObjectName("verticalLayout_Left_4");
        label_material = new QLabel(centralwidget);
        label_material->setObjectName("label_material");
        label_material->setMaximumSize(QSize(16777215, 50));
        label_material->setStyleSheet(QString::fromUtf8("QLabel#label_material {\n"
"    font-size: 15px;       /* \345\255\227\351\253\224\345\244\247\345\260\217 */\n"
"    font-weight: bold;     /* \347\262\227\351\253\224 */\n"
"    color: #2E86C1;        /* \345\255\227\351\253\224\351\241\217\350\211\262 */\n"
"    text-align: center;    /* \345\261\205\344\270\255\345\260\215\351\275\212 */\n"
"    background-color: #F4F6F7; /* \350\203\214\346\231\257\351\241\217\350\211\262 */\n"
"    border: 2px solid #ABB2B9; /* \351\202\212\346\241\206\346\250\243\345\274\217 */\n"
"    padding: 10px;         /* \345\205\247\351\202\212\350\267\235 */\n"
"    border-radius: 5px;    /* \351\202\212\345\257\254\345\234\223\350\247\222 */\n"
"}"));

        verticalLayout_Left_4->addWidget(label_material);

        lcdNumber_Circle = new QLCDNumber(centralwidget);
        lcdNumber_Circle->setObjectName("lcdNumber_Circle");
        lcdNumber_Circle->setMaximumSize(QSize(16777215, 35));
        lcdNumber_Circle->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"    background-color: white;\n"
"    color: blue;\n"
"    border: 2px solid gray;\n"
"    border-radius: 5px;\n"
"}\n"
""));

        verticalLayout_Left_4->addWidget(lcdNumber_Circle);

        pushButton_AddCircle = new QPushButton(centralwidget);
        pushButton_AddCircle->setObjectName("pushButton_AddCircle");
        pushButton_AddCircle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_4->addWidget(pushButton_AddCircle);

        pushButton_SubCircle = new QPushButton(centralwidget);
        pushButton_SubCircle->setObjectName("pushButton_SubCircle");
        pushButton_SubCircle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_4->addWidget(pushButton_SubCircle);

        lcdNumber_Square = new QLCDNumber(centralwidget);
        lcdNumber_Square->setObjectName("lcdNumber_Square");
        lcdNumber_Square->setMaximumSize(QSize(16777215, 35));
        lcdNumber_Square->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"    background-color: white;\n"
"    color: blue;\n"
"    border: 2px solid gray;\n"
"    border-radius: 5px;\n"
"}\n"
""));

        verticalLayout_Left_4->addWidget(lcdNumber_Square);

        pushButton_AddSquare = new QPushButton(centralwidget);
        pushButton_AddSquare->setObjectName("pushButton_AddSquare");
        pushButton_AddSquare->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_4->addWidget(pushButton_AddSquare);

        pushButton_SubSquare = new QPushButton(centralwidget);
        pushButton_SubSquare->setObjectName("pushButton_SubSquare");
        pushButton_SubSquare->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    font-size: 10px;              /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"    font-weight: bold;            /* \347\262\227\344\275\223 */\n"
"    color: white;                 /* \345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"    background-color: #3498DB;    /* \346\214\211\351\222\256\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #2980B9;    /* \346\214\211\351\222\256\350\276\271\346\241\206 */\n"
"    border-radius: 8px;           /* \350\276\271\346\241\206\345\234\206\350\247\222 */\n"
"    padding: 10px 20px;           /* \346\214\211\351\222\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #1F618D;    /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
""
                        "\n"
"QPushButton:pressed {\n"
"    background-color: #1F618D;    /* \346\214\211\344\270\213\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 2px solid #154360;    /* \346\214\211\344\270\213\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #D6EAF8;               /* \346\214\211\344\270\213\346\227\266\345\255\227\344\275\223\351\242\234\350\211\262 */\n"
"}\n"
""));

        verticalLayout_Left_4->addWidget(pushButton_SubSquare);


        gridLayout->addLayout(verticalLayout_Left_4, 3, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_Model->setText(QCoreApplication::translate("MainWindow", "\346\250\241\345\274\217\351\201\270\346\223\207", nullptr));
        radioButton_SingleCycle->setText(QCoreApplication::translate("MainWindow", "\345\226\256\344\270\200\345\276\252\347\222\260", nullptr));
        radioButton_Continuous->setText(QCoreApplication::translate("MainWindow", "\351\200\243\347\272\214\345\276\252\347\222\260", nullptr));
        radioButton_Manual->setText(QCoreApplication::translate("MainWindow", "\346\211\213\345\213\225\346\223\215\344\275\234", nullptr));
        label_Y->setText(QCoreApplication::translate("MainWindow", "Y-\350\274\270\345\205\245\344\277\241\350\231\237", nullptr));
        label_A->setText(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\347\274\270\344\270\213\351\231\215", nullptr));
        label_R1->setText(QCoreApplication::translate("MainWindow", "\350\274\270\351\200\201\345\270\266\351\246\254\351\201\224\350\275\211(M1)", nullptr));
        label_R2->setText(QCoreApplication::translate("MainWindow", "\351\276\215\351\226\200\346\211\213\350\207\202\345\267\246\347\247\273(M2\357\274\213)", nullptr));
        label_R3->setText(QCoreApplication::translate("MainWindow", "\351\276\215\351\226\200\346\211\213\350\207\202\345\217\263\347\247\273(M2\357\274\215)", nullptr));
        label_P_B->setText(QCoreApplication::translate("MainWindow", "\345\244\276\347\210\252\345\244\276\346\214\201", nullptr));
        label_N_B->setText(QCoreApplication::translate("MainWindow", "\345\244\276\347\210\252\346\224\276\351\254\206", nullptr));
        label_RL->setText(QCoreApplication::translate("MainWindow", "\347\264\205\347\207\210", nullptr));
        label_YL->setText(QCoreApplication::translate("MainWindow", "\351\273\203\347\207\210", nullptr));
        label_GL->setText(QCoreApplication::translate("MainWindow", "\347\266\240\347\207\210", nullptr));
        label_Top->setText(QCoreApplication::translate("MainWindow", "\345\275\242\347\213\200\345\210\244\345\210\245\350\210\207\345\202\263\351\200\201", nullptr));
        label_X->setText(QCoreApplication::translate("MainWindow", "X-\350\274\270\345\205\245\344\277\241\350\231\237", nullptr));
        label_a1->setText(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\347\274\270\344\270\213\347\253\257\351\273\236", nullptr));
        label_a0->setText(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\347\274\270\344\270\212\347\253\257\351\273\236", nullptr));
        label_s0->setText(QCoreApplication::translate("MainWindow", "\351\200\262\346\226\231\346\204\237\346\270\254\345\231\250", nullptr));
        label_s1->setText(QCoreApplication::translate("MainWindow", "\346\226\271\346\226\231/\345\234\223\346\226\231\346\204\237\346\270\254\345\231\250 ", nullptr));
        label_p0->setText(QCoreApplication::translate("MainWindow", "\351\276\215\351\226\200\346\211\213\350\207\202\345\210\244\346\226\231\344\275\215", nullptr));
        label_p1->setText(QCoreApplication::translate("MainWindow", "\345\234\223\346\226\231\346\216\222\346\226\231\344\275\215", nullptr));
        label_p2->setText(QCoreApplication::translate("MainWindow", "\346\226\271\346\226\231\346\216\222\346\226\231\344\275\215", nullptr));
        label_Manual->setText(QCoreApplication::translate("MainWindow", "\346\211\213\345\213\225\346\223\215\344\275\234", nullptr));
        pushButton_ManualConveyor->setText(QCoreApplication::translate("MainWindow", "PB1 \346\223\215\346\216\247\350\274\270\351\200\201\345\270\266", nullptr));
        pushButton_ManualACylinder->setText(QCoreApplication::translate("MainWindow", "PB2 \346\223\215\346\216\247\345\236\202\347\233\264\347\274\270\344\270\213\351\231\215", nullptr));
        pushButton_ManualArmLeft->setText(QCoreApplication::translate("MainWindow", "PB3 \346\223\215\346\216\247\351\276\215\351\226\200\346\211\213\350\207\202\345\267\246\347\247\273", nullptr));
        pushButton_ManualArmRight->setText(QCoreApplication::translate("MainWindow", "PB4 \346\223\215\346\216\247\351\276\215\351\226\200\346\211\213\350\207\202\345\217\263\347\247\273", nullptr));
        label_Operate->setText(QCoreApplication::translate("MainWindow", "\346\223\215\344\275\234\346\214\211\351\210\225", nullptr));
        checkBox_Rst->setText(QCoreApplication::translate("MainWindow", "\345\276\251\346\255\270\346\250\241\345\274\217", nullptr));
        radioButton__Work->setText(QCoreApplication::translate("MainWindow", "\345\267\245\344\275\234\346\250\241\345\274\217", nullptr));
        pushButton_St_Rst->setText(QCoreApplication::translate("MainWindow", "\345\225\237\345\213\225\351\210\225/\345\276\251\346\255\270\351\210\225(\347\266\240_\351\273\203)", nullptr));
        pushButton_EMS->setText(QCoreApplication::translate("MainWindow", "\347\267\212\346\200\245\345\201\234\346\255\242\351\226\213\351\227\234(\347\264\205)", nullptr));
        label_material->setText(QCoreApplication::translate("MainWindow", "\345\234\223 / \346\226\271\346\226\231", nullptr));
        pushButton_AddCircle->setText(QCoreApplication::translate("MainWindow", "\345\234\223\346\226\231\345\242\236\345\212\240", nullptr));
        pushButton_SubCircle->setText(QCoreApplication::translate("MainWindow", "\345\234\223\346\226\231\346\270\233\345\260\221", nullptr));
        pushButton_AddSquare->setText(QCoreApplication::translate("MainWindow", "\346\226\271\346\226\231\345\242\236\345\212\240", nullptr));
        pushButton_SubSquare->setText(QCoreApplication::translate("MainWindow", "\346\226\271\346\226\231\346\270\233\345\260\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

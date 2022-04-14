#pragma once


#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include "ui_BattleCity.h"


#include "Configure.h"
#include "MyMap.h"
#include "Start1.h"
#include "Player.h"
#include "EnemyNormal.h"

#define PLAYER2

namespace Ui {
    class BattleCity;
}

class BattleCity : public QWidget
{
    Q_OBJECT

public:
     
    explicit BattleCity(QWidget* parent = 0);
    ~BattleCity();

    //初始化逻辑
    void initLogic();
    //初始化界面
    void initWidget();
    //设置定时器
    void setQTimer(int value);
    //重写绘画
    void paintEvent(QPaintEvent* ev);
    //重写按键按下
    void keyPressEvent(QKeyEvent* ev);
    //重写按键释放
    void keyReleaseEvent(QKeyEvent* ev);

public slots:
    //计时器，更新
    void slotUpdate();  
    //敌人死亡
    void slotEnemyDie();
    //接受游戏开始信号和玩家数量
    void slotGameStart2(int playNum); 

signals:
    void signalGameOver();


private:
    Ui::BattleCity* ui;
    //
    int i_time;   
    //剩余敌方数量
    int m_tankNum;  
    //关卡
    int m_stage; 

    //buff显示状态
    bool m_buffShowFlag;
    bool m_startFlag;
    //玩家数量
    int m_playNum;  

    QTimer* m_timer;


    Player p1;
#ifdef PLAYER2
    Player p2;
#endif

    EnemyNormal EN;
    //EnemySpeed ES;
    ////EnemyForce EF;
    //EnemyBuff EB;


    //图片准备(将图片提前放到内存中，可节省时间)
    QImage imgOtherLife;
    QImage imgOtherLife2;
    QImage imgOtherIP;
    QImage imgOtherIIP;
    QImage imgOtherNumber0;
    QImage imgOtherNumber1;
    QImage imgOtherNumber2;
    QImage imgOtherNumber3;
    QImage imgOtherFlag;
    QImage imgOtherOver;
    QImage imgWallL;
    QImage imgWallR;
    QImage imgBase;
    QImage imgIron;
    QImage imgGrass;
    QImage imgBuffBase;
    QImage imgBuffBump;
    QImage imgBuffForce;
    QImage imgBuffDefence;
    QImage imgBuffLife;
    QImage imgBuffTimer;
};


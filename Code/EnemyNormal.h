#pragma once

#include <QDebug>
#include <QtGlobal>
#include <QTime>
#include "Base.h"
#include "Configure.h"
#include "MyMap.h"
#include "Bullet.h"
#include "Tank.h"
#include "Player.h"




class EnemyNormal :public Tank
{

    Q_OBJECT
public:
    
    //构造析构
    EnemyNormal();
    ~EnemyNormal();

    //普通敌人初始化
    void enemyNormalInit(int xx, int yy, Direction ddirec, char role);

    //设置生命
    void setAlive(int alive);
    int getAlive() const;

    //更新方向和位置
    void updateDirec(); //随机更新方向
    void updateLoca();

public slots:
    void slotAttack(char role);     //受到攻击

signals:
    void signalEnemyDie();          //敌人死亡，给界面发送信号
    void signalAttack(char role);   //击中敌人

private:
    int m_alive;

};


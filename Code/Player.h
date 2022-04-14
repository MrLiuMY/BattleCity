#pragma once

#include <QDebug>
#include "Tank.h"
#include "Configure.h"
#include "EnemyNormal.h"



class Player :public Tank
{

    Q_OBJECT
public:

    Player();
    ~Player();

    //初始化
    void playerInit(int xx, int yy, Direction ddirec, char role);
    //死亡后重新初始化
    void playerReInit();    
    //生命值
    void setAlive(int alive);  
    int getAlive() const;

    //定时Buff的时间
    void setPauseTime(int pauseTime);   
    int getPauseTime() const;

    //获取buff
    void getBuff();
    //接触buff
    void touchBuff();
    //更新数据位置
    void updateLoca();


public slots:
    //受到攻击
    void slotAttack(char role);  

signals:
    //
    void signalAttack(char role);
    //
    void signalTouchBuff();

private:
    //生命值
    int m_alive;
    //buff时间
    int m_pauseTime;
    
   
    //保留初始位置
    int initX;  
    //保留初始位置
    int initY;  
    //保留初始方向
    Direction initDir;

};


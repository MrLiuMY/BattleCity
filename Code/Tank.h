#pragma once


#include <QDebug>
#include "Base.h"
#include "Configure.h"
#include "MyMap.h"
#include "Bullet.h"


class Tank :public Base
{
    Q_OBJECT
public:
    //构造析构
    Tank();
    ~Tank();

    //设置获取运行状态
    void setMoveFlag(bool flag);
    //
    bool getMoveFlag() const;

    //设置坦克类型
    void setRole(char role);
    //
    char getRole() const;

    //设置速度，获取速度
    void setSpeedX(int speedX);
    //
    char getSpeedX() const;
    //
    void setSpeedY(int speedY);
    //
    char getSpeedY() const;


    //获取图片旋转的角度
    int getAngle();        
    //矫正
    //void adjustLoca();   
    //矫正XY
    //void adjustLocaXY(); 
    //   
    //接触到墙壁
    bool isTouchWall(int x, int y);
    //是否检测到一部分障碍物
    bool isTouchObjectPart(int x, int y); 
    //是否检测到障碍物，能否通过
    bool isTouchObject();   
    //是否碰到边界
    bool isTouchBorder();  
    //更新子弹位置
    void updateBullte();    
    //
    void updateTankMap(char value);




    //坦克对象子弹
    Bullet m_bullet;
    //是否可移动
    bool m_moveFlag;    
    //判断是否可矫正
    //Direction m_saveDirec[2]; 
    //
    QPoint m_saveLoca[2];


private:
    //交换方向
    void swapDirec();
    //交换QPoint
    void swapPoint();
    //判断是什么样敌人（普通，速度快，子弹快，带buff）或者玩家
    char m_role;
    //坦克X速度
    int m_speedX;
    //坦克Y速度
    int m_speedY;
};


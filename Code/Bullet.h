#pragma once

#include <QDebug>
#include <QImage>

#include "Base.h"
#include "Configure.h"
#include "MyMap.h"

class Bullet : public Base{
	Q_OBJECT
public:
	//构造和析构
	Bullet();
	virtual ~Bullet();

    //子弹初始化
	void bulletInit(int xx, int yy, Direction ddirec, int grade);
    //设置子弹速度
    void setSpeed(int speed);
    //获取子弹速度
    int getSpeed() const;
    //设置子弹等级
    void setGrade(int grade);
    //获取子弹等级
    int getGrade() const;
    //设置移动标志位
    void setMoveFlag(int flag);
    //获取移动标志位
    bool getMoveFlag() const;


    //更新子弹位置
    bool updateLoca(); 
    //更新子弹等级
    void updateGrade();
    //获取子弹状态，改变运行状态
    void getBulletStatus(QMatrix& matrixBullet, QImage& imgBullet);


    //判断：：如果是墙壁
    bool isWall(int xx, int yy);
    //判断：：打击墙壁
    bool attackWall();
    //判断：：打击铁墙
    bool attackIron();
    //判断：：打击敌人
    bool attackEnemy(char role);
    //判断：：打击基地
    bool attackBase();


private:
	//子弹速度
	int m_speed;
	//子弹等级
	int m_grade;
	//运行标志位
	bool m_moveFlag;
};


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

    //��ʼ��
    void playerInit(int xx, int yy, Direction ddirec, char role);
    //���������³�ʼ��
    void playerReInit();    
    //����ֵ
    void setAlive(int alive);  
    int getAlive() const;

    //��ʱBuff��ʱ��
    void setPauseTime(int pauseTime);   
    int getPauseTime() const;

    //��ȡbuff
    void getBuff();
    //�Ӵ�buff
    void touchBuff();
    //��������λ��
    void updateLoca();


public slots:
    //�ܵ�����
    void slotAttack(char role);  

signals:
    //
    void signalAttack(char role);
    //
    void signalTouchBuff();

private:
    //����ֵ
    int m_alive;
    //buffʱ��
    int m_pauseTime;
    
   
    //������ʼλ��
    int initX;  
    //������ʼλ��
    int initY;  
    //������ʼ����
    Direction initDir;

};


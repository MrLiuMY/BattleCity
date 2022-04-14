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
    
    //��������
    EnemyNormal();
    ~EnemyNormal();

    //��ͨ���˳�ʼ��
    void enemyNormalInit(int xx, int yy, Direction ddirec, char role);

    //��������
    void setAlive(int alive);
    int getAlive() const;

    //���·����λ��
    void updateDirec(); //������·���
    void updateLoca();

public slots:
    void slotAttack(char role);     //�ܵ�����

signals:
    void signalEnemyDie();          //���������������淢���ź�
    void signalAttack(char role);   //���е���

private:
    int m_alive;

};


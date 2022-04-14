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
    //��������
    Tank();
    ~Tank();

    //���û�ȡ����״̬
    void setMoveFlag(bool flag);
    //
    bool getMoveFlag() const;

    //����̹������
    void setRole(char role);
    //
    char getRole() const;

    //�����ٶȣ���ȡ�ٶ�
    void setSpeedX(int speedX);
    //
    char getSpeedX() const;
    //
    void setSpeedY(int speedY);
    //
    char getSpeedY() const;


    //��ȡͼƬ��ת�ĽǶ�
    int getAngle();        
    //����
    //void adjustLoca();   
    //����XY
    //void adjustLocaXY(); 
    //   
    //�Ӵ���ǽ��
    bool isTouchWall(int x, int y);
    //�Ƿ��⵽һ�����ϰ���
    bool isTouchObjectPart(int x, int y); 
    //�Ƿ��⵽�ϰ���ܷ�ͨ��
    bool isTouchObject();   
    //�Ƿ������߽�
    bool isTouchBorder();  
    //�����ӵ�λ��
    void updateBullte();    
    //
    void updateTankMap(char value);




    //̹�˶����ӵ�
    Bullet m_bullet;
    //�Ƿ���ƶ�
    bool m_moveFlag;    
    //�ж��Ƿ�ɽ���
    //Direction m_saveDirec[2]; 
    //
    QPoint m_saveLoca[2];


private:
    //��������
    void swapDirec();
    //����QPoint
    void swapPoint();
    //�ж���ʲô�����ˣ���ͨ���ٶȿ죬�ӵ��죬��buff���������
    char m_role;
    //̹��X�ٶ�
    int m_speedX;
    //̹��Y�ٶ�
    int m_speedY;
};


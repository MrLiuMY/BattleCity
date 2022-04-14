#pragma once

#include <QDebug>
#include <QImage>

#include "Base.h"
#include "Configure.h"
#include "MyMap.h"

class Bullet : public Base{
	Q_OBJECT
public:
	//���������
	Bullet();
	virtual ~Bullet();

    //�ӵ���ʼ��
	void bulletInit(int xx, int yy, Direction ddirec, int grade);
    //�����ӵ��ٶ�
    void setSpeed(int speed);
    //��ȡ�ӵ��ٶ�
    int getSpeed() const;
    //�����ӵ��ȼ�
    void setGrade(int grade);
    //��ȡ�ӵ��ȼ�
    int getGrade() const;
    //�����ƶ���־λ
    void setMoveFlag(int flag);
    //��ȡ�ƶ���־λ
    bool getMoveFlag() const;


    //�����ӵ�λ��
    bool updateLoca(); 
    //�����ӵ��ȼ�
    void updateGrade();
    //��ȡ�ӵ�״̬���ı�����״̬
    void getBulletStatus(QMatrix& matrixBullet, QImage& imgBullet);


    //�жϣ��������ǽ��
    bool isWall(int xx, int yy);
    //�жϣ������ǽ��
    bool attackWall();
    //�жϣ��������ǽ
    bool attackIron();
    //�жϣ����������
    bool attackEnemy(char role);
    //�жϣ����������
    bool attackBase();


private:
	//�ӵ��ٶ�
	int m_speed;
	//�ӵ��ȼ�
	int m_grade;
	//���б�־λ
	bool m_moveFlag;
};


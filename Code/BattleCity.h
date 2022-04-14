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

    //��ʼ���߼�
    void initLogic();
    //��ʼ������
    void initWidget();
    //���ö�ʱ��
    void setQTimer(int value);
    //��д�滭
    void paintEvent(QPaintEvent* ev);
    //��д��������
    void keyPressEvent(QKeyEvent* ev);
    //��д�����ͷ�
    void keyReleaseEvent(QKeyEvent* ev);

public slots:
    //��ʱ��������
    void slotUpdate();  
    //��������
    void slotEnemyDie();
    //������Ϸ��ʼ�źź��������
    void slotGameStart2(int playNum); 

signals:
    void signalGameOver();


private:
    Ui::BattleCity* ui;
    //
    int i_time;   
    //ʣ��з�����
    int m_tankNum;  
    //�ؿ�
    int m_stage; 

    //buff��ʾ״̬
    bool m_buffShowFlag;
    bool m_startFlag;
    //�������
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


    //ͼƬ׼��(��ͼƬ��ǰ�ŵ��ڴ��У��ɽ�ʡʱ��)
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


#include "BattleCity.h"

BattleCity::BattleCity(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::BattleCity)
{
    ui->setupUi(this);
    //��ʼ���߼�
    initLogic();
    //��ʼ������
    initWidget();

}
BattleCity::~BattleCity() {
    delete m_timer;
    delete ui;
}


void BattleCity::initLogic() {

    i_time = 0;
    //ʣ��з�����
    m_tankNum = 1;
    //�ؿ�
    m_stage = 1;

    m_buffShowFlag = true;
    m_startFlag = true;

    //��ͼ��ʼ��
    MyMap::initMap();
    MyMap::setStage(1);

    //��ҳ�ʼ��
    p1.playerInit(32, 96, Base::Direction_Up, 'P');
#ifdef PLAYER2
    p2.playerInit(64, 96, Base::Direction_Up, 'Q');
#endif

    EN.enemyNormalInit(0, 0, Base::Direction_Down, '1');
    //EN.enemyNormalInit(96, 0, Base::Direction_Down, '1');
    //EN.enemyNormalInit(48, 0, Base::Direction_Down, '1');
}

void BattleCity::initWidget() {
    this->resize(1280, 960);
    this->setFixedSize(1280, 960);
    //�̶�λ��
    setGeometry(300, 50, 1280, 960); 

    m_timer = new QTimer(this);

    connect(m_timer, &QTimer::timeout,this, &BattleCity::slotUpdate);

    //p1��EN���ͻ����źţ�����EN���ҵ���
    connect(&p1, SIGNAL(signalAttack(char)), &EN, SLOT(slotAttack(char)));
    connect(&EN, SIGNAL(signalAttack(char)), &p1, SLOT(slotAttack(char)));

#ifdef PLAYER2

    connect(&p2, SIGNAL(signalAttack(char)), &EN, SLOT(slotAttack(char)));
    connect(&EN, SIGNAL(signalAttack(char)), &p2, SLOT(slotAttack(char)));

#endif

    connect(&EN, SIGNAL(signalEnemyDie()), this, SLOT(slotEnemyDie()));



    //ͼƬ׼��
    imgOtherLife = QImage(":/other/image/other/otherLife.png");
    imgOtherLife2 = QImage(":/other/image/other/otherLife2.png");
    imgOtherIP = QImage(":/other/image/other/otherIP.png");
    imgOtherIIP = QImage(":/other/image/other/otherIIP.png");
    imgOtherNumber0 = QImage(":/other/image/other/otherNumber0.jpg");
    imgOtherNumber1 = QImage(":/other/image/other/otherNumber1.png");
    imgOtherNumber2 = QImage(":/other/image/other/otherNumber2.png");
    imgOtherNumber3 = QImage(":/other/image/other/otherNumber3.jpg");
    imgOtherFlag = QImage(":/other/image/other/otherFlag.png");
    imgOtherOver = QImage(":/other/image/other/otherOver.jpg");
    imgWallL = QImage(":/object/image/object/objectWallL.png");
    imgWallR = QImage(":/object/image/object/objectWallR.png");
    imgBase = QImage(":/player/image/player/base.png");
    imgIron = QImage(":/object/image/object/objectIronSmall.png");
    imgGrass = QImage(":/object/image/object/objectGrassSmall.png");
    imgBuffBase = QImage(":/buff/image/buff/buffBase.png");
    imgBuffBump = QImage(":/buff/image/buff/buffBump.png");
    imgBuffForce = QImage(":/buff/image/buff/buffForce.png");
    imgBuffDefence = QImage(":/buff/image/buff/buffDefense.png");
    imgBuffLife = QImage(":/buff/image/buff/buffLife.png");
    imgBuffTimer = QImage(":/buff/image/buff/buffTimer.png");

}

//���ö�ʱ��
void BattleCity::setQTimer(int value) {
    if (value != -1)
        m_timer->start(value);
    else m_timer->stop();
}

//��ʼ���滭
void BattleCity::paintEvent(QPaintEvent* ev) {

    QPen pen;
    QPainter p(this);

    pen.setColor(QColor(99, 97, 99));
    p.setBrush(QColor(99, 97, 99));
    p.setPen(pen);
    p.drawRect(0, 0, SIZE_WIDTH, SIZE_HEIGHT);

    p.setBrush(Qt::black);
    p.drawRect(BORDER_LEFT, BORDER_UP, CELL_WIDTH * CELL_NUMBER, CELL_HEIGHT * CELL_NUMBER);


    int drawTankCount = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (drawTankCount == m_tankNum) break;
            //�����з�̹��������
            p.drawImage(1115 + 40 + 43 * j, 90 + 33 * i, imgOtherLife);
            drawTankCount++;
        }

        if (drawTankCount == m_tankNum) break;
    }

    //�����з�IP
    p.drawImage(1115 + 40, 500, imgOtherIP);
    p.drawImage(1115 + 40, 500 + 36, imgOtherLife2);

    switch (p1.getAlive())  //��ʣ������
    {
    case 0: p.drawImage(75 + 3 * 80 + 40, 45 + 12 * 64, imgOtherOver);
        p.drawImage(1115 + 81, 500 + 36, imgOtherNumber0); break;
    case 1: p.drawImage(1115 + 81, 500 + 36, imgOtherNumber0); break;
    case 2: p.drawImage(1115 + 81, 500 + 36, imgOtherNumber1); break;
    case 3: p.drawImage(1115 + 81, 500 + 36, imgOtherNumber2); break;
    case 4: p.drawImage(1115 + 81, 500 + 36, imgOtherNumber3); break;
    default: break;
    }

    //�����з�IIP
    p.drawImage(1115 + 40, 590, imgOtherIIP);
    p.drawImage(1115 + 40, 590 + 36, imgOtherLife2);

    switch (p2.getAlive())
    {
    case 0: p.drawImage(75 + 7 * 80 + 40, 45 + 12 * 64, imgOtherOver);
        p.drawImage(1115 + 81, 590 + 36, imgOtherNumber0); break;
    case 1: p.drawImage(1115 + 81, 590 + 36, imgOtherNumber0); break;
    case 2: p.drawImage(1115 + 81, 590 + 36, imgOtherNumber1); break;
    case 3: p.drawImage(1115 + 81, 590 + 36, imgOtherNumber2); break;
    case 4: p.drawImage(1115 + 81, 590 + 36, imgOtherNumber3); break;
    default: break;
    }


    p.drawImage(1115 + 40, 690, imgOtherFlag);
    p.drawImage(1115 + 84, 760, imgOtherNumber1);



    //����ͼ
    for (int y = 0; y < CELL_NUMBER; y += 1)
    {
        for (int x = 0; x < CELL_NUMBER; x += 1)
        {
            switch (MyMap::getMap(x, y))
            {
                //��������
                case 'B': p.drawImage(75 + x * 10, 45 + y * 8, imgBase); break;
                //����ǽ��L
                case 'W': p.drawImage(75 + x * 10, 45 + y * 8, imgWallL); break;
                //����ǽ��R
                case 'V': p.drawImage(75 + x * 10, 45 + y * 8, imgWallR); break;
                //��������
                case 'I': p.drawImage(75 + x * 10, 45 + y * 8, imgIron); break;
                //�����ݵ�
                case 'G': p.drawImage(75 + x * 10, 45 + y * 8, imgGrass); break;
                default: break;
            }
        }
    }

    //���1
    QImage imgP1(":/player/image/player/p1tankNormal_U1.png");
    //���2
    QImage imgP2(":/player/image/player/p2tankNormal_U1.png");
    //����ӵ�
    QImage imgBullet(":/object/image/object/bullet.png");
    //�з��ӵ�
    QImage imgBulletTemp = imgBullet;
    //��������
    QImage imgEnEmyN(":/enemy/image/enemy/enemyNormal.png");
    //�ٶȿ����
    QImage imgEnEmyS(":/enemy/image/enemy/enemySpeed.png");
    //�ӵ������
    QImage imgEnEmyF(":/enemy/image/enemy/enemyForce.png");
    //��buff����
    QImage imgEnEmyB(":/enemy/image/enemy/enemyBuff.png");

    ///*
    //�����1
    if (p1.getAlive() != 0)
    {
        QMatrix matrixP1;
        matrixP1.rotate(p1.getAngle());
        imgP1 = imgP1.transformed(matrixP1).scaled(80, 64);
        p.drawImage(p1.x, p1.y, imgP1);
    }
    //*/
//
#ifdef PLAYER2
    //�����2
    if (p2.getAlive() != 0)
    {
        QMatrix matrixP2;
        matrixP2.rotate(p2.getAngle());
        imgP2 = imgP2.transformed(matrixP2).scaled(80, 64);
        p.drawImage(p2.x, p2.y, imgP2);
    }
#endif

    //���з�1
    if (EN.getAlive() != 0)
    {
        QMatrix matrixEnEmyN;
        matrixEnEmyN.rotate(EN.getAngle());
        imgEnEmyN = imgEnEmyN.transformed(matrixEnEmyN).scaled(80, 64);
        p.drawImage(EN.x, EN.y, imgEnEmyN);
    }





    //�����1�ӵ�
    imgBullet = imgBulletTemp;
    pen.setColor(Qt::yellow);
    p.setPen(pen);

    QMatrix matrixBullet1;
    if (p1.m_bullet.getMoveFlag())
    {
        p1.m_bullet.getBulletStatus(matrixBullet1, imgBullet);
        p.drawImage(p1.m_bullet.x, p1.m_bullet.y, imgBullet);
    }


#ifdef PLAYER2
    //�����2�ӵ�
    imgBullet = imgBulletTemp;
    pen.setColor(Qt::green);
    p.setPen(pen);
    QMatrix matrixBullet2;
    if (p2.m_bullet.getMoveFlag())
    {
        p2.m_bullet.getBulletStatus(matrixBullet2, imgBullet);
        p.drawImage(p2.m_bullet.x, p2.m_bullet.y, imgBullet);
    }
#endif

    //���з��ӵ�

    imgBullet = imgBulletTemp;
    pen.setColor(Qt::white);
    p.setPen(pen);
    QMatrix matrixBulletEN;
    if (EN.m_bullet.getMoveFlag())
    {
        EN.m_bullet.getBulletStatus(matrixBulletEN, imgBullet);
        p.drawImage(EN.m_bullet.x, EN.m_bullet.y, imgBullet);
    }


}


void BattleCity::keyPressEvent(QKeyEvent* ev) {
    //qDebug() << ev->key();
    switch (ev->key())
    {
    case 87: p1.setMoveFlag(true); p1.direc = Player::Direction_Up; qDebug() << "tank1 up run"; break;  //'w'
    case 65: p1.setMoveFlag(true); p1.direc = Player::Direction_Left; qDebug() << "tank1 left run"; break;  //'a'
    case 83: p1.setMoveFlag(true); p1.direc = Player::Direction_Down; qDebug() << "tank1 down run"; break;  //'s'
    case 68: p1.setMoveFlag(true); p1.direc = Player::Direction_Right; qDebug() << "tank1 right run"; break;  //'d'
    case 70: if (!p1.m_bullet.getMoveFlag())    //'f'
    {
        qDebug() << "The tank1 fired bullets";
        p1.updateBullte();
    }
             p1.m_bullet.setMoveFlag(true); break; //�ӵ���������ʱ
#ifdef PLAYER2
    case 73: p2.setMoveFlag(true); p2.direc = Player::Direction_Up; qDebug() << "tank2 up run"; break;  //'i'
    case 74: p2.setMoveFlag(true); p2.direc = Player::Direction_Left; qDebug() << "tank2 left run"; break;  //'j'
    case 75: p2.setMoveFlag(true); p2.direc = Player::Direction_Down; qDebug() << "tank2 down run"; break;  //'k'
    case 76: p2.setMoveFlag(true); p2.direc = Player::Direction_Right; qDebug() << "tank2 right run"; break;  //'l'
    case 72: if (!p2.m_bullet.getMoveFlag())    //'h'
    {
        qDebug() << "The tank2 fired bullets";
        p2.updateBullte();

    }
             p2.m_bullet.setMoveFlag(true); break; //�ӵ���������ʱ
#endif
    default: p1.setMoveFlag(false);
#ifdef PLAYER2
        p2.setMoveFlag(false);
#endif
        break;
    }
}


void BattleCity::keyReleaseEvent(QKeyEvent* ev) {
    switch (ev->key())
    {
    case 87: p1.setMoveFlag(false); break;  //'w'
    case 65: p1.setMoveFlag(false); break;  //'a'
    case 83: p1.setMoveFlag(false); break;  //'s'
    case 68: p1.setMoveFlag(false); break;  //'d'
#ifdef PLAYER2
    case 73: p2.setMoveFlag(false); break;  //'i'
    case 74: p2.setMoveFlag(false); break;  //'j'
    case 75: p2.setMoveFlag(false); break;  //'k'
    case 76: p2.setMoveFlag(false); break;  //'l'
#endif
    default: break;
    }
}


void BattleCity::slotUpdate() {
    //��Ϸ����
    if ((p1.getAlive() == 0 && p2.getAlive() == 0)||
        p1.m_bullet.attackBase() ||
        p2.m_bullet.attackBase() ||
        EN.m_bullet.attackBase())

    {
        qDebug() << "Game Over";
        m_timer->stop();

        emit signalGameOver();
        this->hide();
    }


    i_time++;
    i_time = i_time % 20;

    p1.updateLoca();    //���1����
#ifdef PLAYER2
    p2.updateLoca();    //���2����
#endif

    //��ʱBuff
    if (p1.getPauseTime() == 0 && p2.getPauseTime() == 0)
    {
        EN.updateLoca();    //���˸���

    }
    else
    {
        //�ӵ�ֹͣ����
        EN.m_bullet.setMoveFlag(false);

    }

    //buff��˸
    if (i_time % 4 == 0)
    {
        if (m_buffShowFlag == true)
            m_buffShowFlag = false;
        else
            m_buffShowFlag = true;
    }

    if (i_time == 0)
    {
        //��ʱBuff���£�buff��˸
        if (p1.getPauseTime() != 0)
            p1.setPauseTime(p1.getPauseTime() - 1);
        if (p2.getPauseTime() != 0)
            p2.setPauseTime(p2.getPauseTime() - 1);


        //��ʱBuff
        if (p1.getPauseTime() == 0 && p2.getPauseTime() == 0)
        {
            EN.updateDirec();   //���˷������
 
        }



        //�����ӵ�����
        if (EN.getAlive() != 0 && EN.m_bullet.getMoveFlag() == false)
        {
            EN.m_bullet.setMoveFlag(true);
            EN.updateBullte();
        }

  
  
    }

    update();
}


void BattleCity::slotEnemyDie() {
    m_tankNum--;
    qDebug() << "tankNum: " << m_tankNum;
}


void BattleCity::slotGameStart2(int playNum) {
    qDebug() << "playNum = " << playNum;
    m_playNum = playNum;
    if (m_playNum == 2)
    {

    }
    this->show();
    setQTimer(40);
}
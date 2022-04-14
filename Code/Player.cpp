#include "Player.h"


Player::Player() {

    m_alive = 10;
    m_pauseTime = 0;

    initX = 0;
    initY = 0;
    initDir = Direction_Up;
}

Player::~Player() {

}

//初始化
void Player::playerInit(int xx, int yy, Direction ddirec, char role) {
    //位置
    x = BORDER_LEFT + xx * CELL_WIDTH;
    y = BORDER_UP + yy * CELL_HEIGHT;
    direc = ddirec;

    //记录初始位置和方向
    initX = x;
    initY = y;
    initDir = direc;

    //用于更新地图
    m_saveLoca[0] = QPoint(xx, yy);
    m_saveLoca[1] = QPoint(xx, yy);

    setSpeedX(CELL_WIDTH);
    setSpeedY(CELL_HEIGHT);

    //确定角色
    MyMap::setBigCell(xx, yy, role);
    setRole(role);

    //子弹初始化
    m_bullet.bulletInit(x + 40, y, ddirec, 1);

    //m_alive = 3;

}

//死亡后重新初始化
void Player::playerReInit() {
    int xx = (x - BORDER_LEFT) / CELL_WIDTH;
    int yy = (y - BORDER_UP) / CELL_HEIGHT;

    x = initX;
    y = initY;
    direc = initDir;



        //用于更新地图
    MyMap::setBigCell(m_saveLoca[1].x(), m_saveLoca[1].y(), 0);     //旧位置
    MyMap::setBigCell(m_saveLoca[0].x(), m_saveLoca[0].y(), 0);     //新位置

    setSpeedX(CELL_WIDTH);
    setSpeedY(CELL_HEIGHT);

    m_saveLoca[0] = QPoint(xx, yy);
    m_saveLoca[1] = QPoint(xx, yy);

    //确定角色
    MyMap::setBigCell(xx, yy, getRole());

    //子弹初始化
    m_bullet.bulletInit(x + 40, y, direc, 1);

}


//生命值
void Player::setAlive(int alive) {

    m_alive = alive;
}


int Player::getAlive() const {
    return m_alive;

}

//定时Buff的时间
void Player::setPauseTime(int pauseTime) {

    m_pauseTime = pauseTime;
}


int Player::getPauseTime() const {
    return m_pauseTime;

}

//
void Player::getBuff() {
    //switch (EnemyBuff::getSBuffType())
    //{
    //case EnemyBuff::BuffType_Base: break;
    //case EnemyBuff::BuffType_Bump:
    //    emit signalAttack('1');
    //    emit signalAttack('2');
    //    emit signalAttack('3');
    //    emit signalAttack('4');
    //    break;
    //case EnemyBuff::BuffType_Defense: break;
    //case EnemyBuff::BuffType_Force: m_bullet.setGrade(2); break;
    //case EnemyBuff::BuffType_Life: if (m_alive < 5) m_alive++; break;
    //case EnemyBuff::BuffType_Timer: m_pauseTime = 10; break;
    //default: break;
    //}

}


//
void Player::touchBuff() {
  /*  QPoint buffPoint = EnemyBuff::getSBuffPoint();

    if (buffPoint.x() != -1 && buffPoint.y() != -1)
    {
        if (direc == Base::Direction_Up)
        {
            if (x > buffPoint.x() - 45 && x < buffPoint.x() + 45
                && y > buffPoint.y() && y < buffPoint.y() + 64)
            {
                getBuff();
                emit signalTouchBuff();
            }
        }
        else if (direc == Base::Direction_Left)
        {
            if (y > buffPoint.y() - 37 && y < buffPoint.y() + 37
                && x > buffPoint.x() && x < buffPoint.x() + 80)
            {
                getBuff();
                emit signalTouchBuff();
            }
        }
        else if (direc == Base::Direction_Down)
        {
            if (x > buffPoint.x() - 45 && x < buffPoint.x() + 45
                && y > buffPoint.y() - 64 && y < buffPoint.y())
            {
                getBuff();
                emit signalTouchBuff();
            }
        }
        else if (direc == Base::Direction_Right)
        {
            if (y > buffPoint.y() - 37 && y < buffPoint.y() + 37
                && x > buffPoint.x() - 80 && x < buffPoint.x())
            {
                getBuff();
                emit signalTouchBuff();
            }
        }
    }*/

}


//
void Player::updateLoca() {

    //如果生命值为0
    if (m_alive == 0)
    {
        x = 0;
        y = 0;
        MyMap::setBigCell(m_saveLoca[1].x(), m_saveLoca[1].y(), 0); //旧位置
        MyMap::setBigCell(m_saveLoca[0].x(), m_saveLoca[0].y(), 0); //新位置
        m_bullet.setMoveFlag(false);
        m_moveFlag = false;

        return;
    }

    //更新子弹
    if (m_bullet.attackWall() || m_bullet.attackIron() || !m_bullet.updateLoca())
    {
        m_bullet.setMoveFlag(false);
    }


    if (m_bullet.attackEnemy('1'))
    {
        m_bullet.setMoveFlag(false);
        emit signalAttack('1');
        qDebug() << getRole() << "attack alayer 1";
    }



 /*   if (m_bullet.attackEnemy('2'))
    {
        m_bullet.setMoveFlag(false);
        emit signalAttack('2');
        qDebug() << getRole() << "attack alayer 2";
    }
    if (m_bullet.attackEnemy('3'))
    {
        m_bullet.setMoveFlag(false);
        emit signalAttack('3');
        qDebug() << getRole() << "attack alayer 3";
    }
    if (m_bullet.attackEnemy('4'))
    {
        m_bullet.setMoveFlag(false);
        emit signalAttack('4');
        qDebug() << getRole() << "attack alayer 4";
    }*/





    if (m_moveFlag == false)
        return;

    if (isTouchObject())
        return;

    //是否吃到buff和碰到边界
    touchBuff();
    isTouchBorder();

    //更新地图上坦克的位置
    updateTankMap(getRole());
}



//受到攻击
void Player::slotAttack(char role) {

    if (role == getRole())
    {
        m_alive--;

        playerReInit();
        updateTankMap(getRole());

        qDebug() << getRole() << "received attick";
    }

}
#include "EnemyNormal.h"

EnemyNormal::EnemyNormal() {
    m_moveFlag = true;  //敌方一直可动
    m_bullet.setMoveFlag(false);

    m_alive = 1;
}


EnemyNormal::~EnemyNormal() {


}



void EnemyNormal::enemyNormalInit(int xx, int yy, Direction ddirec, char role) {
    
    //位置
    x = BORDER_LEFT + xx * CELL_WIDTH;
    y = BORDER_UP + yy * CELL_HEIGHT;
    direc = ddirec;

    //用于更新地图
    m_saveLoca[0] = QPoint(xx, yy);
    m_saveLoca[1] = QPoint(xx, yy);

    setSpeedX(CELL_WIDTH);
    setSpeedY(CELL_HEIGHT);

    //确定角色
    MyMap::setBigCell(xx, yy, role);
    setRole(role);

    //子弹初始化
    m_bullet.bulletInit(x + 40, y + 64, ddirec, 1);

}

void EnemyNormal::setAlive(int alive) {

    m_alive = alive;
}


int EnemyNormal::getAlive() const {

    return m_alive;

}

//随机更新方向
void EnemyNormal::updateDirec(){
    
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    int sDirec = qrand() % 4;
    direc = (Direction)(sDirec + 1);

}


void EnemyNormal::updateLoca() {

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
    if (m_bullet.attackEnemy('P'))
    {
        m_bullet.setMoveFlag(false);
        emit signalAttack('P');
        qDebug() << getRole() << "attack alayer P";
    }
    if (m_bullet.attackEnemy('Q'))
    {
        m_bullet.setMoveFlag(false);
        emit signalAttack('Q');
        qDebug() << getRole() << "attack alayer Q";
    }


    if (m_moveFlag == false)
        return;

    if (isTouchObject())
        return;

    isTouchBorder();

    //更新地图上坦克的位置
    updateTankMap(getRole());

}

//受到攻击
void EnemyNormal::slotAttack(char role) {

    if (role == getRole())
    {
        if (m_alive > 0)
        {
            m_alive--;
            if (m_alive == 0)
            {
                MyMap::setBigCell(m_saveLoca[1].x(), m_saveLoca[1].y(), 0);
                MyMap::setBigCell(m_saveLoca[0].x(), m_saveLoca[0].y(), 0);

                emit signalEnemyDie();
            }
            qDebug() << getRole() << ":Received Attick, Life: " << m_alive;

        }
    }

}
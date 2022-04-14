#include "EnemyNormal.h"

EnemyNormal::EnemyNormal() {
    m_moveFlag = true;  //�з�һֱ�ɶ�
    m_bullet.setMoveFlag(false);

    m_alive = 1;
}


EnemyNormal::~EnemyNormal() {


}



void EnemyNormal::enemyNormalInit(int xx, int yy, Direction ddirec, char role) {
    
    //λ��
    x = BORDER_LEFT + xx * CELL_WIDTH;
    y = BORDER_UP + yy * CELL_HEIGHT;
    direc = ddirec;

    //���ڸ��µ�ͼ
    m_saveLoca[0] = QPoint(xx, yy);
    m_saveLoca[1] = QPoint(xx, yy);

    setSpeedX(CELL_WIDTH);
    setSpeedY(CELL_HEIGHT);

    //ȷ����ɫ
    MyMap::setBigCell(xx, yy, role);
    setRole(role);

    //�ӵ���ʼ��
    m_bullet.bulletInit(x + 40, y + 64, ddirec, 1);

}

void EnemyNormal::setAlive(int alive) {

    m_alive = alive;
}


int EnemyNormal::getAlive() const {

    return m_alive;

}

//������·���
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
        MyMap::setBigCell(m_saveLoca[1].x(), m_saveLoca[1].y(), 0); //��λ��
        MyMap::setBigCell(m_saveLoca[0].x(), m_saveLoca[0].y(), 0); //��λ��
        m_bullet.setMoveFlag(false);
        m_moveFlag = false;

        return;
    }

    //�����ӵ�
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

    //���µ�ͼ��̹�˵�λ��
    updateTankMap(getRole());

}

//�ܵ�����
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
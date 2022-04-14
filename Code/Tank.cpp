#include "Tank.h"


Tank::Tank() {
	m_role = 0;
	m_moveFlag = false;
}


Tank::~Tank() {

}



//
void Tank::setMoveFlag(bool flag) {
	this->m_moveFlag = flag;

}



//
bool Tank::getMoveFlag() const {
	return this->m_moveFlag;

}

//
void Tank::setRole(char role) {
	this->m_role = role;
}


//
char Tank::getRole() const {
	return this->m_role;
}


//X速度
void Tank::setSpeedX(int speedX) {
	this->m_speedX = speedX;

}


//
char Tank::getSpeedX() const {
	return this->m_speedX;
}


//Y速度
void Tank::setSpeedY(int speedY) {
	this->m_speedY = speedY;
}


//
char Tank::getSpeedY() const {
	return this->m_speedY;

}


//获取图片旋转的角度
int Tank::getAngle() {
	switch (direc)
	{
	case Base::Direction_Up:    return 0;   break;
	case Base::Direction_Left:  return 270; break;
	case Base::Direction_Down:  return 180; break;
	case Base::Direction_Right: return 90;  break;
	default: break;
	}

}




//矫正
//void adjustLoca();   
//矫正XY
//void adjustLocaXY();  



//？？？是否碰到墙壁？
bool Tank::isTouchWall(int x, int y) {
    if (MyMap::getMap(x, y) == '1' || MyMap::getMap(x, y) == '2')
        return true;
    else return false;
}


//是否检测到一部分障碍物
bool Tank::isTouchObjectPart(int x, int y) {

    //计算出像素点
    int smallX = CELL_WIDTH * 2;    //20
    int smallY = CELL_HEIGHT * 2;   //16

    int bigX = CELL_WIDTH * 4;    //40
    int bigY = CELL_HEIGHT * 4;   //32

    int biggerX = CELL_WIDTH * 8;    //80
    int biggerY = CELL_HEIGHT * 8;   //64

    //不可通过的
    if (MyMap::getMap(x / smallX * 2, y / smallY * 2) == 'W' ||
        MyMap::getMap(x / smallX * 2, y / smallY * 2) == 'V' ||
        MyMap::getMap(x / bigX * 4, y / bigY * 4) == 'I' ||
        MyMap::getMap(x / biggerX * 8, y / biggerY * 8) == 'B' ||
        MyMap::getMap(x / biggerX * 8, y / biggerY * 8) == 'R' ||
        (
            ((MyMap::getMap(x / smallX * 2, y / smallY * 2) >= '0' && MyMap::getMap(x / smallX * 2, y / smallY * 2) <= '9') ||
                (MyMap::getMap(x / smallX * 2, y / smallY * 2) == 'P' || MyMap::getMap(x / smallX * 2, y / smallY * 2) == 'Q')) &&
            MyMap::getMap(x / smallX * 2, y / smallY * 2) != getRole()
            )
        )

        return true;
    else return false;
}


//是否检测到障碍物
bool Tank::isTouchObject() {

    int x1 = x - BORDER_LEFT;//  -75
    int y1 = y - BORDER_UP;  //  -45
    int x2 = x - BORDER_LEFT + 80 - 2;
    int y2 = y - BORDER_UP + 64 - 2;

    //
    if (direc == Base::Direction_Up)
    {
        if (isTouchObjectPart(x1, (y1 - m_speedY)) || isTouchObjectPart(x2, (y1 - m_speedY))
            || isTouchObjectPart((x1 + 40), (y1 - m_speedY))
            || isTouchObjectPart((x1 + 20), (y1 - m_speedY))
            || isTouchObjectPart((x1 + 60), (y1 - m_speedY)))
            return true;
    }
    else if (direc == Base::Direction_Left)
    {
        if (isTouchObjectPart((x1 - m_speedX), y1) || isTouchObjectPart((x1 - m_speedX), y2)
            || isTouchObjectPart((x1 - m_speedX), (y1 + 32))
            || isTouchObjectPart((x1 - m_speedX), (y1 + 16))
            || isTouchObjectPart((x1 - m_speedX), (y1 + 48)))
            return true;
    }
    else if (direc == Base::Direction_Down)
    {
        if (isTouchObjectPart(x1, (y2 + m_speedY)) || isTouchObjectPart(x2, (y2 + m_speedY))
            || isTouchObjectPart((x1 + 20), (y2 + m_speedY))
            || isTouchObjectPart((x1 + 40), (y2 + m_speedY))
            || isTouchObjectPart((x1 + 60), (y2 + m_speedY)))
            return true;
    }
    else if (direc == Base::Direction_Right)
    {
        if (isTouchObjectPart((x2 + m_speedX), y1) || isTouchObjectPart((x2 + m_speedX), y2)
            || isTouchObjectPart((x2 + m_speedX), (y1 + 32))
            || isTouchObjectPart((x2 + m_speedX), (y1 + 16))
            || isTouchObjectPart((x2 + m_speedX), (y1 + 48)))
            return true;
    }
    else return false;
}


//是否碰到边界,
bool Tank::isTouchBorder() {

    //运动范围
    int speedValueRD = CELL_NUMBER - 8;

    //移动速度普通，加快
    if (m_speedX == CELL_WIDTH * 2 && m_speedY == CELL_HEIGHT * 2)
    {
        speedValueRD = CELL_NUMBER / 2 - 4;
    }

    //如果没碰到墙壁，继续运动
    if (((y - BORDER_UP) / (m_speedY) > 0) && (direc == Direction_Up))
    {
        y -= m_speedY;
        return false;
    }
    else if (((x - BORDER_LEFT) / (m_speedX) > 0) && (direc == Direction_Left))
    {
        x -= m_speedX;
        return false;
    }
    else if ((y - BORDER_UP) / (m_speedY) < (speedValueRD) && (direc == Direction_Down))
    {
        y += m_speedY;
        return false;
    }
    else if ((x - BORDER_LEFT) / (m_speedX) < (speedValueRD) && (direc == Direction_Right))
    {
        x += m_speedX;
        return false;
    }
    else return true;
}


//更新子弹位置
void Tank::updateBullte() {

    m_bullet.direc = direc;

    switch (direc)
    {
    case Base::Direction_Up:

        m_bullet.x = x + 40 - 5;
        m_bullet.y = y; 
        qDebug() << " bullet up run "; 
        break;

    case Base::Direction_Left:

        m_bullet.x = x;
        m_bullet.y = y + 32 - 5;
        qDebug() << " bullet left run ";
        break;

    case Base::Direction_Down:

        m_bullet.x = x + 40 - 5;
        m_bullet.y = y + 64 - 16; 
        qDebug() << " bullet down run ";
        break;

    case Base::Direction_Right:

        m_bullet.x = x + 80 - 16;
        m_bullet.y = y + 32 - 5; 
        qDebug() << " bullet right run ";
        break;

    default: 
        break;
    }
}


//
void Tank::updateTankMap(char value) {
    //更新地图上坦克的位置
    m_saveLoca[1] = (QPoint((x - BORDER_LEFT) / (CELL_WIDTH / 2 * 2), (y - BORDER_UP) / (CELL_HEIGHT / 2 * 2)));
    swapPoint();
    if (m_saveLoca[0] != m_saveLoca[1])
    {
        //        if (MyMap::getMap(m_saveLoca[1].x(), m_saveLoca[1].y()) == 'G')
        //            MyMap::setMap(m_saveLoca[1].x(), m_saveLoca[1].y(), 'G');     //旧位置
        //        else
        //            MyMap::setBigCell(m_saveLoca[1].x(), m_saveLoca[1].y(), 0);

        MyMap::setBigCell(m_saveLoca[1].x(), m_saveLoca[1].y(), 0);
        MyMap::setBigCell(m_saveLoca[0].x(), m_saveLoca[0].y(), value); //新位置
    }
}



void Tank::swapDirec() {

}

void Tank::swapPoint() {
	QPoint temp = m_saveLoca[0];
	m_saveLoca[0] = m_saveLoca[1];
	m_saveLoca[1] = temp;
}
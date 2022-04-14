#include "Bullet.h"

//构造和析构
Bullet::Bullet() {
	this->m_moveFlag = false;
    this->m_speed = 0;
    this->m_grade = 0;
}
Bullet::~Bullet() {

}


//子弹初始化
void Bullet::bulletInit(int xx, int yy, Direction ddirec, int grade) {
    this->x = xx;
    this->y = yy;
    this->direc = ddirec;
    this->m_grade = grade;
    
    updateGrade();//根据子弹等级影响子弹速度,和能够打击类型
}


//设置子弹速度
void Bullet::setSpeed(int speed) {
    this->m_speed = speed;
}


//获取子弹速度
int Bullet::getSpeed() const {
    return this->m_speed;
}


//设置子弹等级
void Bullet::setGrade(int grade) {
    this->m_grade = grade;
}


//获取子弹等级
int Bullet::getGrade() const {
    return this->m_grade;
}


//设置移动标志位
void Bullet::setMoveFlag(int flag) {
    this->m_moveFlag = flag;
}


//获取移动标志位
bool Bullet::getMoveFlag() const {
    return m_moveFlag;
}


//更新子弹位置（还能运行返回真，不能运行返回假）
bool Bullet::updateLoca() {

    updateGrade();//根据子弹等级影响子弹速度

    if (m_moveFlag == true){
        
        //相对游戏界面位置根据当前x，y减去边界宽度与高度
        int xx = this->x - BORDER_LEFT;
        int yy = this->y - BORDER_UP;
        
        //如果y大于最小单位并且方向向上，则让其y坐标减去速度，向上移动
        if ((yy / (CELL_HEIGHT) > 1) && (direc == Direction_Up)){
            qDebug() << "bullet->x ::" << this->x << "  " << "bullet->y ::" << this->y;
            y -= m_speed;
            return true;
        }
        //如果x大于最小单位并且方向向左，则让其x坐标减去速度，向左移动
        else if ((xx / (CELL_WIDTH) > 0) && (direc == Direction_Left)){
            qDebug() << "bullet->x ::" << this->x << "  " << "bullet->y ::" << this->y;
            x -= m_speed;
            return true;
        }
        //如果y除以最小单位小于列数量并且方向向下，则让其y坐标加上速度，向下移动
        else if ((yy / (CELL_HEIGHT) < CELL_NUMBER - 2) && (direc == Direction_Down)){
            qDebug() << "bullet->x ::" << this->x<< "  " << "bullet->y ::" << this->y;
            y += m_speed;
            return true;
        }
        //如果x除以最小单位小于行数量并且方向向右，则让其x坐标加上速度，向右移动
        else if ((xx / (CELL_WIDTH) < CELL_NUMBER - 2) && (direc == Direction_Right)){
            qDebug() << "bullet->x ::" << this->x << "  " << "bullet->y ::" << this->y;
            x += m_speed;
            return true;
        }
        //否则返回假
        else{
            return false;
        }
    }
    else 
        return false;
}


//更新子弹等级，影响子弹速度，默认为16（一个子弹身位）
void Bullet::updateGrade() {
    switch (this->m_grade) {
    case 1:
        this->m_speed = 16;
        break;
    case 2:
        this->m_speed = 32;
        break;
    default:
        this->m_speed = 16;
        break;
    }
}


//获取子弹状态更改运行方向图
void Bullet::getBulletStatus(QMatrix& matrixBullet, QImage& imgBullet) {
    switch (direc){
    case Bullet::Direction_Up:
        imgBullet = imgBullet.transformed(matrixBullet).scaled(10, 16); break;
    case Bullet::Direction_Left:
        matrixBullet.rotate(270);
        imgBullet = imgBullet.transformed(matrixBullet).scaled(16, 10); break;
    case Bullet::Direction_Down:
        matrixBullet.rotate(180);
        imgBullet = imgBullet.transformed(matrixBullet).scaled(10, 16); break;
    case Bullet::Direction_Right:
        matrixBullet.rotate(90);
        imgBullet = imgBullet.transformed(matrixBullet).scaled(16, 10); break;
    default: break;
    }
}


//判断：：是否为墙壁
bool Bullet::isWall(int xx, int yy) {
    if (MyMap::getMap(xx, yy) == 'W' || MyMap::getMap(xx, yy) == 'V')
        return true;
    else 
        return false;
}


//判断：：打击墙壁
bool Bullet::attackWall() {

    updateGrade();

    if (m_moveFlag == true)
    {
        // -75和-45为了 去除 边界影响
        int cenX = x - 75;
        int cenY = y - 45;

        if (this->direc == Base::Direction_Up)
        {
            if (m_grade == 2)
            {
                //将像素点换算成坐标
                int xx = (cenX + 5) / CELL_WIDTH / 2 * 2;
                int yy = (cenY - 16) / CELL_HEIGHT / 2 * 2;

                //右侧为空(子弹中心偏右)
                if (isWall(xx - 2, yy) && MyMap::getMap(xx, yy) == 0)
                {
                    MyMap::setMap(xx - 2, yy, 0);
                    MyMap::setMap(xx - 4, yy, 0);
                    return true;
                }
                //左侧为空
                if (isWall(xx, yy) && MyMap::getMap(xx - 2, yy) == 0)
                {
                    MyMap::setMap(xx, yy, 0);
                    MyMap::setMap(xx + 2, yy, 0);
                    return true;
                }
                //左右都不为空
                if ((isWall(xx, yy) && isWall(xx - 2, yy)) ||
                    (isWall(xx, yy) && isWall(xx + 2, yy)))
                {
                    MyMap::setMap(xx, yy, 0);
                    MyMap::setMap(xx + 2, yy, 0);
                    MyMap::setMap(xx - 2, yy, 0);
                    MyMap::setMap(xx - 4, yy, 0);
                    return true;
                }
            }
            
            int xx = (cenX + 5) / CELL_WIDTH / 2 * 2;
            int yy = (cenY - m_speed) / CELL_HEIGHT / 2 * 2;
            //右侧为空(子弹中心偏右)
            if (isWall(xx - 2, yy) && MyMap::getMap(xx, yy) == 0)
            {
                MyMap::setMap(xx - 2, yy, 0);
                MyMap::setMap(xx - 4, yy, 0);
                return true;
            }
            //左侧为空
            if (isWall(xx, yy) && MyMap::getMap(xx - 2, yy) == 0)
            {
                MyMap::setMap(xx, yy, 0);
                MyMap::setMap(xx + 2, yy, 0);
                return true;
            }
            //左右都不为空
            if ((isWall(xx, yy) && isWall(xx - 2, yy)) ||
                (isWall(xx, yy) && isWall(xx + 2, yy)))
            {
                MyMap::setMap(xx, yy, 0);
                MyMap::setMap(xx + 2, yy, 0);
                MyMap::setMap(xx - 2, yy, 0);
                MyMap::setMap(xx - 4, yy, 0);
                return true;
            }

        }
        else if (direc == Base::Direction_Left)
        {
            if (m_grade == 2)
            {
                int xx = (cenX - 16) / CELL_WIDTH / 2 * 2;
                int yy = (cenY + 5) / CELL_HEIGHT / 2 * 2;
                //上部为空(子弹中心偏下)
                if (isWall(xx, yy) && MyMap::getMap(xx, yy - 2) != 'W')
                {
                    MyMap::setMap(xx, yy + 0, 0);
                    MyMap::setMap(xx, yy + 2, 0);
                    return true;
                }
                //下部为空(子弹中心偏下)
                if (isWall(xx, yy - 2) && MyMap::getMap(xx, yy) == 0)
                {
                    MyMap::setMap(xx, yy - 2, 0);
                    MyMap::setMap(xx, yy - 4, 0);
                    return true;
                }
                //上下都不为空(子弹中心偏下)
                if ((isWall(xx, yy) && isWall(xx, yy - 2)) ||
                    (isWall(xx, yy) && isWall(xx, yy + 2)))
                {
                    MyMap::setMap(xx, yy + 0, 0);
                    MyMap::setMap(xx, yy + 2, 0);
                    MyMap::setMap(xx, yy - 2, 0);
                    MyMap::setMap(xx, yy - 4, 0);
                    return true;
                }
            }
           
            int xx = (cenX - m_speed) / CELL_WIDTH / 2 * 2;
            int yy = (cenY + 5) / CELL_HEIGHT / 2 * 2;
            //上部为空(子弹中心偏下)
            if (isWall(xx, yy) && MyMap::getMap(xx, yy - 2) == 0)
            {
                MyMap::setMap(xx, yy + 0, 0);
                MyMap::setMap(xx, yy + 2, 0);
                return true;
            }
            //下部为空(子弹中心偏下)
            if (isWall(xx, yy - 2) && MyMap::getMap(xx, yy) == 0)
            {
                MyMap::setMap(xx, yy - 2, 0);
                MyMap::setMap(xx, yy - 4, 0);
                return true;
            }
            //上下都不为空(子弹中心偏下)
            if ((isWall(xx, yy) && isWall(xx, yy - 2)) ||
                (isWall(xx, yy) && isWall(xx, yy + 2)))
            {
                MyMap::setMap(xx, yy + 0, 0);
                MyMap::setMap(xx, yy + 2, 0);
                MyMap::setMap(xx, yy - 2, 0);
                MyMap::setMap(xx, yy - 4, 0);
                return true;
            }
        }
        else if (direc == Base::Direction_Down)
        {
            if (m_grade == 2)
            {
                int xx = (cenX + 5) / CELL_WIDTH / 2 * 2;
                int yy = (cenY + 16) / CELL_HEIGHT / 2 * 2;
                //右侧为空(子弹中心偏右)
                if (isWall(xx - 2, yy) && !isWall(xx, yy))
                {
                    MyMap::setMap(xx - 2, yy, 0);
                    MyMap::setMap(xx - 4, yy, 0);
                    return true;
                }
                //右侧为空
                if (isWall(xx, yy) && !isWall(xx - 2, yy))
                {
                    MyMap::setMap(xx + 0, yy, 0);
                    MyMap::setMap(xx + 2, yy, 0);
                    return true;
                }
                //左右都不为空
                if ((isWall(xx, yy) && isWall(xx - 2, yy)) ||
                    (isWall(xx, yy) && isWall(xx + 2, yy)))
                {
                    MyMap::setMap(xx, yy, 0);
                    MyMap::setMap(xx + 2, yy, 0);
                    MyMap::setMap(xx - 2, yy, 0);
                    MyMap::setMap(xx - 4, yy, 0);
                    return true;
                }
            }
            
            int xx = (cenX + 5) / CELL_WIDTH / 2 * 2;
            int yy = (cenY + m_speed) / CELL_HEIGHT / 2 * 2;
            //右侧为空(子弹中心偏右)
            if (isWall(xx - 2, yy) && !isWall(xx, yy))
            {
                MyMap::setMap(xx - 2, yy, 0);
                MyMap::setMap(xx - 4, yy, 0);
                return true;
            }
            //右侧为空
            if (isWall(xx, yy) && !isWall(xx - 2, yy))
            {
                MyMap::setMap(xx + 0, yy, 0);
                MyMap::setMap(xx + 2, yy, 0);
                return true;
            }
            //左右都不为空
            if ((isWall(xx, yy) && isWall(xx - 2, yy)) ||
                (isWall(xx, yy) && isWall(xx + 2, yy)))
            {
                MyMap::setMap(xx, yy, 0);
                MyMap::setMap(xx + 2, yy, 0);
                MyMap::setMap(xx - 2, yy, 0);
                MyMap::setMap(xx - 4, yy, 0);
                return true;
            }
        }
        else if (direc == Base::Direction_Right)
        {
            if (m_grade == 2)
            {
                int xx = (cenX + 16) / CELL_WIDTH / 2 * 2;
                int yy = (cenY + 5) / CELL_HEIGHT / 2 * 2;
                //上部为空(子弹中心偏下)
                if (isWall(xx, yy) && MyMap::getMap(xx, yy - 2) == 0)
                {
                    MyMap::setMap(xx, yy + 0, 0);
                    MyMap::setMap(xx, yy + 2, 0);
                    return true;
                }
                //下部为空(子弹中心偏下)
                if (isWall(xx, yy - 2) && MyMap::getMap(xx, yy) == 0)
                {
                    MyMap::setMap(xx, yy - 2, 0);
                    MyMap::setMap(xx, yy - 4, 0);
                    return true;
                }
                //上下都不为空(子弹中心偏下)
                if ((isWall(xx, yy) && isWall(xx, yy - 2)) ||
                    (isWall(xx, yy) && isWall(xx, yy + 2)))
                {
                    MyMap::setMap(xx, yy + 0, 0);
                    MyMap::setMap(xx, yy + 2, 0);
                    MyMap::setMap(xx, yy - 2, 0);
                    MyMap::setMap(xx, yy - 4, 0);
                    return true;
                }
            }
            
            int xx = (cenX + m_speed) / CELL_WIDTH / 2 * 2;
            int yy = (cenY + 5) / CELL_HEIGHT / 2 * 2;
            //上部为空(子弹中心偏下)
            if (isWall(xx, yy) && MyMap::getMap(xx, yy - 2) == 0)
            {
                MyMap::setMap(xx, yy + 0, 0);
                MyMap::setMap(xx, yy + 2, 0);
                return true;
            }
            //下部为空(子弹中心偏下)
            if (isWall(xx, yy - 2) && MyMap::getMap(xx, yy) == 0)
            {
                MyMap::setMap(xx, yy - 2, 0);
                MyMap::setMap(xx, yy - 4, 0);
                return true;
            }
            //上下都不为空(子弹中心偏下)
            if ((isWall(xx, yy) && isWall(xx, yy - 2)) ||
                (isWall(xx, yy) && isWall(xx, yy + 2)))
            {
                MyMap::setMap(xx, yy + 0, 0);
                MyMap::setMap(xx, yy + 2, 0);
                MyMap::setMap(xx, yy - 2, 0);
                MyMap::setMap(xx, yy - 4, 0);
                return true;
            }
        }
        else 
            return false;
    }
    else 
        return false;
}


//判断：：打击铁墙（判断钢铁消失坐标还有问题）
bool Bullet::attackIron() {

    updateGrade();

    if (m_moveFlag == true)
    {
        //相对游戏界面位置
        int cenX = x - 75;
        int cenY = y - 45;

        if (direc == Base::Direction_Up)
        {
            int xx = (cenX + 5) / CELL_WIDTH / 4 * 4;
            int yy = (cenY - m_speed) / CELL_HEIGHT / 4 * 4;
            //下一个目标点为钢铁
            if (MyMap::getMap(xx, yy) == 'I')
            {
                if (m_grade == 3)
                {
                    MyMap::setMap(xx, yy, 0);
                    MyMap::setMap(xx-4, yy, 0);
                    return true;
                }
                else return true;
            }
            else return false;

        }
        else if (direc == Base::Direction_Left)
        {
            int xx = (cenX - m_speed) / CELL_WIDTH / 4 * 4;
            int yy = (cenY + 5) / CELL_HEIGHT / 4 * 4;
            //下一个目标点为钢铁
            if (MyMap::getMap(xx, yy) == 'I')
            {
                if (m_grade == 3)
                {
                    MyMap::setMap(xx, yy, 0);
                    MyMap::setMap(xx, yy+4, 0);
                    return true;
                }
                else return true;
            }
            else return false;
        }
        else if (direc == Base::Direction_Down)
        {
            int xx = (cenX + 5) / CELL_WIDTH / 4 * 4;
            int yy = (cenY + m_speed) / CELL_HEIGHT / 4 * 4;
            //下一个目标点为钢铁
            if (MyMap::getMap(xx, yy) == 'I')
            {
                if (m_grade == 3)
                {
                    MyMap::setMap(xx, yy, 0);
                    MyMap::setMap(xx+4, yy, 0);
                    return true;
                }
                else return true;
            }
            else return false;
        }
        else if (direc == Base::Direction_Right)
        {
            int xx = (cenX + m_speed) / CELL_WIDTH / 4 * 4;
            int yy = (cenY + 5) / CELL_HEIGHT / 4 * 4;
            //下一个目标点为钢铁
            if (MyMap::getMap(xx, yy) == 'I')
            {
                if (m_grade == 3)
                {
                    MyMap::setMap(xx, yy, 0);
                    MyMap::setMap(xx, yy-4, 0);
                    return true;
                }
                else 
                    return true;
            }
            else return false;
        }
        else 
            return false;
    }
    else 
        return false;

}


//判断：：子弹前方是否有敌人
bool Bullet::attackEnemy(char role) {

    updateGrade();

    if (m_moveFlag == true)
    {
        //相对游戏界面的位置
        int cenX = x - 75;
        int cenY = y - 45;

        if (direc == Bullet::Direction_Up)
        {
            int xx = (cenX + 5) / CELL_WIDTH / 2 * 2;
            int yy = (cenY - 16) / CELL_HEIGHT / 2 * 2;

            //上方有敌人
            if (MyMap::getMap(xx, yy) == role)
            {
                qDebug() << "xxyy:" << xx << yy << "xy:" << x << y;
                qDebug() << "up";

                return true;
            }
        }
        else if (direc == Base::Direction_Left)
        {
            int xx = (cenX - 16) / CELL_WIDTH / 2 * 2;
            int yy = (cenY + 5) / CELL_HEIGHT / 2 * 2;

            //左方有敌人
            if (MyMap::getMap(xx, yy) == role)
            {
                qDebug() << "left";

                return true;
            }
        }
        else if (direc == Base::Direction_Down)
        {
            int xx = (cenX + 5) / CELL_WIDTH / 2 * 2;
            int yy = (cenY + 16) / CELL_HEIGHT / 2 * 2;

            //下方有敌人
            if (MyMap::getMap(xx, yy) == role)
            {
                qDebug() << "down";

                return true;
            }
        }
        else if (direc == Base::Direction_Right)
        {
            int xx = (cenX + 16) / CELL_WIDTH / 2 * 2;
            int yy = (cenY + 5) / CELL_HEIGHT / 2 * 2;
            //右方有敌人
            if (MyMap::getMap(xx, yy) == role)
            {
                qDebug() << "right";

                return true;
            }
        }
        else return false;
    }
    else 
        return false;
}


//判断：：打击基地
bool Bullet::attackBase() {

    //qDebug() << "Start judging if the base has been hit";

    updateGrade();  //更新子弹等级

    if (m_moveFlag == true)
    {
        int cenX = x - 75;
        int cenY = y - 45;

        if (direc == Base::Direction_Left)
        {
            int xx = (cenX - 16) / CELL_WIDTH / 8 * 8;
            int yy = (cenY + 5) / CELL_HEIGHT / 8 * 8;

            //左方击中基地
            if (MyMap::getMap(xx, yy) == 'B')
            {

                qDebug() << "left attack base";
                m_moveFlag = false;
                return true;
            }
            else
                return false;
        }
        else if (direc == Base::Direction_Down)
        {
            int xx = (cenX + 5) / CELL_WIDTH / 8 * 8;
            int yy = (cenY + 16) / CELL_HEIGHT / 8 * 8;

            //下方击中基地
            if (MyMap::getMap(xx, yy) == 'B')
            {
                qDebug() << "down attack base";
                m_moveFlag = false;
                return true;
            }
            else
                return false;
        }
        else if (direc == Base::Direction_Right)
        {
            int xx = (cenX + 16) / CELL_WIDTH / 8 * 8;
            int yy = (cenY + 5) / CELL_HEIGHT / 8 * 8;
            //右方击中基地
            if (MyMap::getMap(xx, yy) == 'B')
            {
                qDebug() << "right attack base";
                m_moveFlag = false;
                return true;
            }
            else
                return false;
        }
        else 
            return false;
    }
    else 
        return false;
}





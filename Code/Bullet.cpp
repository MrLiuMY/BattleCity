#include "Bullet.h"

//���������
Bullet::Bullet() {
	this->m_moveFlag = false;
    this->m_speed = 0;
    this->m_grade = 0;
}
Bullet::~Bullet() {

}


//�ӵ���ʼ��
void Bullet::bulletInit(int xx, int yy, Direction ddirec, int grade) {
    this->x = xx;
    this->y = yy;
    this->direc = ddirec;
    this->m_grade = grade;
    
    updateGrade();//�����ӵ��ȼ�Ӱ���ӵ��ٶ�,���ܹ��������
}


//�����ӵ��ٶ�
void Bullet::setSpeed(int speed) {
    this->m_speed = speed;
}


//��ȡ�ӵ��ٶ�
int Bullet::getSpeed() const {
    return this->m_speed;
}


//�����ӵ��ȼ�
void Bullet::setGrade(int grade) {
    this->m_grade = grade;
}


//��ȡ�ӵ��ȼ�
int Bullet::getGrade() const {
    return this->m_grade;
}


//�����ƶ���־λ
void Bullet::setMoveFlag(int flag) {
    this->m_moveFlag = flag;
}


//��ȡ�ƶ���־λ
bool Bullet::getMoveFlag() const {
    return m_moveFlag;
}


//�����ӵ�λ�ã��������з����棬�������з��ؼ٣�
bool Bullet::updateLoca() {

    updateGrade();//�����ӵ��ȼ�Ӱ���ӵ��ٶ�

    if (m_moveFlag == true){
        
        //�����Ϸ����λ�ø��ݵ�ǰx��y��ȥ�߽�����߶�
        int xx = this->x - BORDER_LEFT;
        int yy = this->y - BORDER_UP;
        
        //���y������С��λ���ҷ������ϣ�������y�����ȥ�ٶȣ������ƶ�
        if ((yy / (CELL_HEIGHT) > 1) && (direc == Direction_Up)){
            qDebug() << "bullet->x ::" << this->x << "  " << "bullet->y ::" << this->y;
            y -= m_speed;
            return true;
        }
        //���x������С��λ���ҷ�������������x�����ȥ�ٶȣ������ƶ�
        else if ((xx / (CELL_WIDTH) > 0) && (direc == Direction_Left)){
            qDebug() << "bullet->x ::" << this->x << "  " << "bullet->y ::" << this->y;
            x -= m_speed;
            return true;
        }
        //���y������С��λС�����������ҷ������£�������y��������ٶȣ������ƶ�
        else if ((yy / (CELL_HEIGHT) < CELL_NUMBER - 2) && (direc == Direction_Down)){
            qDebug() << "bullet->x ::" << this->x<< "  " << "bullet->y ::" << this->y;
            y += m_speed;
            return true;
        }
        //���x������С��λС�����������ҷ������ң�������x��������ٶȣ������ƶ�
        else if ((xx / (CELL_WIDTH) < CELL_NUMBER - 2) && (direc == Direction_Right)){
            qDebug() << "bullet->x ::" << this->x << "  " << "bullet->y ::" << this->y;
            x += m_speed;
            return true;
        }
        //���򷵻ؼ�
        else{
            return false;
        }
    }
    else 
        return false;
}


//�����ӵ��ȼ���Ӱ���ӵ��ٶȣ�Ĭ��Ϊ16��һ���ӵ���λ��
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


//��ȡ�ӵ�״̬�������з���ͼ
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


//�жϣ����Ƿ�Ϊǽ��
bool Bullet::isWall(int xx, int yy) {
    if (MyMap::getMap(xx, yy) == 'W' || MyMap::getMap(xx, yy) == 'V')
        return true;
    else 
        return false;
}


//�жϣ������ǽ��
bool Bullet::attackWall() {

    updateGrade();

    if (m_moveFlag == true)
    {
        // -75��-45Ϊ�� ȥ�� �߽�Ӱ��
        int cenX = x - 75;
        int cenY = y - 45;

        if (this->direc == Base::Direction_Up)
        {
            if (m_grade == 2)
            {
                //�����ص㻻�������
                int xx = (cenX + 5) / CELL_WIDTH / 2 * 2;
                int yy = (cenY - 16) / CELL_HEIGHT / 2 * 2;

                //�Ҳ�Ϊ��(�ӵ�����ƫ��)
                if (isWall(xx - 2, yy) && MyMap::getMap(xx, yy) == 0)
                {
                    MyMap::setMap(xx - 2, yy, 0);
                    MyMap::setMap(xx - 4, yy, 0);
                    return true;
                }
                //���Ϊ��
                if (isWall(xx, yy) && MyMap::getMap(xx - 2, yy) == 0)
                {
                    MyMap::setMap(xx, yy, 0);
                    MyMap::setMap(xx + 2, yy, 0);
                    return true;
                }
                //���Ҷ���Ϊ��
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
            //�Ҳ�Ϊ��(�ӵ�����ƫ��)
            if (isWall(xx - 2, yy) && MyMap::getMap(xx, yy) == 0)
            {
                MyMap::setMap(xx - 2, yy, 0);
                MyMap::setMap(xx - 4, yy, 0);
                return true;
            }
            //���Ϊ��
            if (isWall(xx, yy) && MyMap::getMap(xx - 2, yy) == 0)
            {
                MyMap::setMap(xx, yy, 0);
                MyMap::setMap(xx + 2, yy, 0);
                return true;
            }
            //���Ҷ���Ϊ��
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
                //�ϲ�Ϊ��(�ӵ�����ƫ��)
                if (isWall(xx, yy) && MyMap::getMap(xx, yy - 2) != 'W')
                {
                    MyMap::setMap(xx, yy + 0, 0);
                    MyMap::setMap(xx, yy + 2, 0);
                    return true;
                }
                //�²�Ϊ��(�ӵ�����ƫ��)
                if (isWall(xx, yy - 2) && MyMap::getMap(xx, yy) == 0)
                {
                    MyMap::setMap(xx, yy - 2, 0);
                    MyMap::setMap(xx, yy - 4, 0);
                    return true;
                }
                //���¶���Ϊ��(�ӵ�����ƫ��)
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
            //�ϲ�Ϊ��(�ӵ�����ƫ��)
            if (isWall(xx, yy) && MyMap::getMap(xx, yy - 2) == 0)
            {
                MyMap::setMap(xx, yy + 0, 0);
                MyMap::setMap(xx, yy + 2, 0);
                return true;
            }
            //�²�Ϊ��(�ӵ�����ƫ��)
            if (isWall(xx, yy - 2) && MyMap::getMap(xx, yy) == 0)
            {
                MyMap::setMap(xx, yy - 2, 0);
                MyMap::setMap(xx, yy - 4, 0);
                return true;
            }
            //���¶���Ϊ��(�ӵ�����ƫ��)
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
                //�Ҳ�Ϊ��(�ӵ�����ƫ��)
                if (isWall(xx - 2, yy) && !isWall(xx, yy))
                {
                    MyMap::setMap(xx - 2, yy, 0);
                    MyMap::setMap(xx - 4, yy, 0);
                    return true;
                }
                //�Ҳ�Ϊ��
                if (isWall(xx, yy) && !isWall(xx - 2, yy))
                {
                    MyMap::setMap(xx + 0, yy, 0);
                    MyMap::setMap(xx + 2, yy, 0);
                    return true;
                }
                //���Ҷ���Ϊ��
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
            //�Ҳ�Ϊ��(�ӵ�����ƫ��)
            if (isWall(xx - 2, yy) && !isWall(xx, yy))
            {
                MyMap::setMap(xx - 2, yy, 0);
                MyMap::setMap(xx - 4, yy, 0);
                return true;
            }
            //�Ҳ�Ϊ��
            if (isWall(xx, yy) && !isWall(xx - 2, yy))
            {
                MyMap::setMap(xx + 0, yy, 0);
                MyMap::setMap(xx + 2, yy, 0);
                return true;
            }
            //���Ҷ���Ϊ��
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
                //�ϲ�Ϊ��(�ӵ�����ƫ��)
                if (isWall(xx, yy) && MyMap::getMap(xx, yy - 2) == 0)
                {
                    MyMap::setMap(xx, yy + 0, 0);
                    MyMap::setMap(xx, yy + 2, 0);
                    return true;
                }
                //�²�Ϊ��(�ӵ�����ƫ��)
                if (isWall(xx, yy - 2) && MyMap::getMap(xx, yy) == 0)
                {
                    MyMap::setMap(xx, yy - 2, 0);
                    MyMap::setMap(xx, yy - 4, 0);
                    return true;
                }
                //���¶���Ϊ��(�ӵ�����ƫ��)
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
            //�ϲ�Ϊ��(�ӵ�����ƫ��)
            if (isWall(xx, yy) && MyMap::getMap(xx, yy - 2) == 0)
            {
                MyMap::setMap(xx, yy + 0, 0);
                MyMap::setMap(xx, yy + 2, 0);
                return true;
            }
            //�²�Ϊ��(�ӵ�����ƫ��)
            if (isWall(xx, yy - 2) && MyMap::getMap(xx, yy) == 0)
            {
                MyMap::setMap(xx, yy - 2, 0);
                MyMap::setMap(xx, yy - 4, 0);
                return true;
            }
            //���¶���Ϊ��(�ӵ�����ƫ��)
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


//�жϣ��������ǽ���жϸ�����ʧ���껹�����⣩
bool Bullet::attackIron() {

    updateGrade();

    if (m_moveFlag == true)
    {
        //�����Ϸ����λ��
        int cenX = x - 75;
        int cenY = y - 45;

        if (direc == Base::Direction_Up)
        {
            int xx = (cenX + 5) / CELL_WIDTH / 4 * 4;
            int yy = (cenY - m_speed) / CELL_HEIGHT / 4 * 4;
            //��һ��Ŀ���Ϊ����
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
            //��һ��Ŀ���Ϊ����
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
            //��һ��Ŀ���Ϊ����
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
            //��һ��Ŀ���Ϊ����
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


//�жϣ����ӵ�ǰ���Ƿ��е���
bool Bullet::attackEnemy(char role) {

    updateGrade();

    if (m_moveFlag == true)
    {
        //�����Ϸ�����λ��
        int cenX = x - 75;
        int cenY = y - 45;

        if (direc == Bullet::Direction_Up)
        {
            int xx = (cenX + 5) / CELL_WIDTH / 2 * 2;
            int yy = (cenY - 16) / CELL_HEIGHT / 2 * 2;

            //�Ϸ��е���
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

            //���е���
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

            //�·��е���
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
            //�ҷ��е���
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


//�жϣ����������
bool Bullet::attackBase() {

    //qDebug() << "Start judging if the base has been hit";

    updateGrade();  //�����ӵ��ȼ�

    if (m_moveFlag == true)
    {
        int cenX = x - 75;
        int cenY = y - 45;

        if (direc == Base::Direction_Left)
        {
            int xx = (cenX - 16) / CELL_WIDTH / 8 * 8;
            int yy = (cenY + 5) / CELL_HEIGHT / 8 * 8;

            //�󷽻��л���
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

            //�·����л���
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
            //�ҷ����л���
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





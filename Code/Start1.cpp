#include "Start1.h"

Start1::Start1(QWidget *parent)
	: QWidget(parent),ui(new Ui::Start1)
{
	ui->setupUi(this);
	this->m_count = 150;
    //图片加载是否完成
	this->m_isLoadFinish = false;
    //初始化选择坦克位置
	this->m_selectPo = QPoint(322, 510);//固定位置

	this->m_selectValue = 1;
	//this->m_countDownTime = 200;

	this->imgStart= QImage(":/image/start1.jpg");
	this->imgSelect = QImage(":/player/image/player/p1tankNormal_U1.png");
	this->imgStart2 = QImage(":/image/start2.jpg");

	QMatrix matrixBulletIS;
	matrixBulletIS.rotate(90);

	this->imgSelect = this->imgSelect.transformed(matrixBulletIS).scaled(80, 64);
    //设置界面大小
	this->resize(1280, 960);
    this->setFixedSize(1280, 960);
	setGeometry(300, 50, 1280, 960);

	this->m_timer = new QTimer(this);
	connect(this->m_timer, &QTimer::timeout,this, &Start1::slotUpdate);
	this->m_timer->start(19);
}

Start1::~Start1()
{
    delete ui;
    delete m_timer;
}



void Start1::paintEvent(QPaintEvent* ev)
{
	//QPen pen;
	QPainter p(this);
	p.setBrush(Qt::black);
	p.drawRect(0, 0, 1280, 960);
    //制造从下往上的动态效果
    if (m_isLoadFinish == false) {
        p.drawImage(0, 960 / 150 * m_count, imgStart);
    }
    //最后开始界面
	else{
        //画开始界面
		p.drawImage(0, 0, imgStart);
		//画选择框，屏蔽开始界面的坦克
		p.drawRect(322, 510, 80, 64);
        //将选择关卡坦克画上去
		p.drawImage(m_selectPo.x(), m_selectPo.y(), imgSelect);
	}

}


void Start1::keyPressEvent(QKeyEvent* ev)
{
    qDebug() << ev->key();
    switch (ev->key()){
    case 87:
        if (m_selectPo.y() > 510){
            m_selectValue--;
            m_selectPo.ry() -= 64; 
            update();
        }
        break;
    case 83:
        if (m_selectPo.y() < 510 + 64){
            m_selectValue++;
            m_selectPo.ry() += 64; 
            update();
        }
        break;
    case 16777220:
        if (m_count != 0){
            m_count = 0;
        }
        else{
            emit signalGameStart1(m_selectValue);
            this->hide();
        }
        break;
    default: break;
    }
}


void Start1::slotUpdate()
{

    if (m_count){
        this->m_count--;
    }
    else{
        this->m_isLoadFinish = true;
        this->m_timer->stop();
    }
    update();
}
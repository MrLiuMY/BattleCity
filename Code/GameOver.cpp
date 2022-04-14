#include "GameOver.h"

GameOver::GameOver(QWidget *parent)
	: QWidget(parent),ui(new Ui::GameOver)
{
	ui->setupUi(this);

    m_count = 150; //定时器倒计时
    imgGameOver = QImage(":/image/gameOver1.png");

    //设置界面大小
    this->resize(1280, 960);
    this->setFixedSize(1280, 960);
    setGeometry(300, 50, 1280, 960);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout,this, &GameOver::slotUpdate);

    //m_timer->start(19);
}

GameOver::~GameOver(){
    delete ui;
    delete m_timer;
}


void GameOver::paintEvent(QPaintEvent* ev){
    QPen pen;
    QPainter p(this);
    p.setBrush(Qt::black);
    p.drawRect(0, 0, 1280, 960);

    p.drawImage(0, 960 / 150 * m_count, imgGameOver);

}


//重写控制键盘
void GameOver::keyPressEvent(QKeyEvent* ev){
    qDebug() << ev->key();
    switch (ev->key()){
    case 16777220: 
        qDebug() << "enter"; 
        break;
    default: break;
    }
}


//控制界面逐步往上走
void GameOver::slotUpdate(){
    if (m_count){
        m_count--;
    }
    else{
        m_timer->stop();
    }

    update();
}


//gameover界面槽函数
void GameOver::slotGameOver(){
    //显示界面
    this->show();
    //开启定时器
    m_timer->start(19);
}

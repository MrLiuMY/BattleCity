#include "GameOver.h"

GameOver::GameOver(QWidget *parent)
	: QWidget(parent),ui(new Ui::GameOver)
{
	ui->setupUi(this);

    m_count = 150; //��ʱ������ʱ
    imgGameOver = QImage(":/image/gameOver1.png");

    //���ý����С
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


//��д���Ƽ���
void GameOver::keyPressEvent(QKeyEvent* ev){
    qDebug() << ev->key();
    switch (ev->key()){
    case 16777220: 
        qDebug() << "enter"; 
        break;
    default: break;
    }
}


//���ƽ�����������
void GameOver::slotUpdate(){
    if (m_count){
        m_count--;
    }
    else{
        m_timer->stop();
    }

    update();
}


//gameover����ۺ���
void GameOver::slotGameOver(){
    //��ʾ����
    this->show();
    //������ʱ��
    m_timer->start(19);
}

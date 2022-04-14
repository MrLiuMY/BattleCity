#include "Start2.h"

Start2::Start2(QWidget *parent)
	: QWidget(parent),ui(new Ui::Start2)
{
	ui->setupUi(this);

	this->resize(1280, 960);
	this->setFixedSize(1280, 960);
	setGeometry(300, 50, 1280, 960);

	this->m_playNum = 1;

}

Start2::~Start2()
{
	delete ui;
}

void Start2::paintEvent(QPaintEvent* ev) {
	QPainter p(this);
	p.setBrush(Qt::black);
	p.drawRect(0, 0, 1280, 960);

	QImage imgStart2(":/image/start2.jpg");
	p.drawImage(0, 0, imgStart2);

}

void Start2::keyPressEvent(QKeyEvent* ev) {
	qDebug() << ev->key();
	switch (ev->key())
	{
	case 16777220: 
		qDebug() << "enter"; 
		this->hide();
		emit signalGameStart2(m_playNum); 
		break;
	default: break;
	}
}

void Start2::slotGameStart1(int playNum)
{
	this->show();

	m_playNum = playNum;
}
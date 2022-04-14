#pragma once

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <QPaintEvent>
#include <QKeyEvent>

#include "ui_Start1.h"

namespace Ui {
	class Start1;
}

class Start1 : public QWidget
{
	Q_OBJECT

public:
	explicit Start1(QWidget *parent = 0);
	~Start1();


	//void setStartFlag(bool flag);
	//bool getStartFlag() const;

	//��ͼ�¼�
	void paintEvent(QPaintEvent* ev);
	//�����¼�
	void keyPressEvent(QKeyEvent* ev);

public slots:
	void slotUpdate();

signals:
	void signalGameStart1(int playNum);  //������Ϸ��ʼ�ź�

private:
	Ui::Start1 *ui;

	QTimer* m_timer;
	int m_count;   
	bool m_isLoadFinish;
	QPoint m_selectPo;
	int m_selectValue;
	//int m_countDownTime;//��ʱ����ʱʱ��
	QImage imgStart;
	QImage imgSelect;
	QImage imgStart2;
};

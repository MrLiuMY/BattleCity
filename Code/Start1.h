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

	//绘图事件
	void paintEvent(QPaintEvent* ev);
	//键盘事件
	void keyPressEvent(QKeyEvent* ev);

public slots:
	void slotUpdate();

signals:
	void signalGameStart1(int playNum);  //发送游戏开始信号

private:
	Ui::Start1 *ui;

	QTimer* m_timer;
	int m_count;   
	bool m_isLoadFinish;
	QPoint m_selectPo;
	int m_selectValue;
	//int m_countDownTime;//计时器计时时间
	QImage imgStart;
	QImage imgSelect;
	QImage imgStart2;
};

#pragma once

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <QPaintEvent>
#include <QKeyEvent>
#include "ui_Start2.h"

namespace Ui {
	class Start2;
}

class Start2 : public QWidget
{
	Q_OBJECT

public:
	explicit Start2(QWidget *parent = 0);
	~Start2();
	//重写绘画
	void paintEvent(QPaintEvent* ev);
	//重写键盘按键
	void keyPressEvent(QKeyEvent* ev);

public slots:
	void slotGameStart1(int playNum); //接受游戏开始信号

signals:
	void signalGameStart2(int playNum); //发送游戏开始，进入画面信号

private:
	Ui::Start2 *ui;
	int m_playNum;
};

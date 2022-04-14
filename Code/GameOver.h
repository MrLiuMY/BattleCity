#pragma once

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <QPaintEvent>
#include <QKeyEvent>

#include "ui_GameOver.h"


namespace Ui {
	class GameOver;
}


class GameOver : public QWidget
{
	Q_OBJECT

public:
	explicit GameOver(QWidget *parent = 0);
	~GameOver();

	//重写绘画
	void paintEvent(QPaintEvent* ev);
	//重写按键
	void keyPressEvent(QKeyEvent* ev);


public slots:
	//
	void slotUpdate();
	//
	void slotGameOver();


private:
	Ui::GameOver *ui;

	//定时器
	QTimer* m_timer;
	//游戏图片出来的动作时间
	int m_count;
	//游戏结束的图片
	QImage imgGameOver;
};

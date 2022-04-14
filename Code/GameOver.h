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

	//��д�滭
	void paintEvent(QPaintEvent* ev);
	//��д����
	void keyPressEvent(QKeyEvent* ev);


public slots:
	//
	void slotUpdate();
	//
	void slotGameOver();


private:
	Ui::GameOver *ui;

	//��ʱ��
	QTimer* m_timer;
	//��ϷͼƬ�����Ķ���ʱ��
	int m_count;
	//��Ϸ������ͼƬ
	QImage imgGameOver;
};

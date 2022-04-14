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
	//��д�滭
	void paintEvent(QPaintEvent* ev);
	//��д���̰���
	void keyPressEvent(QKeyEvent* ev);

public slots:
	void slotGameStart1(int playNum); //������Ϸ��ʼ�ź�

signals:
	void signalGameStart2(int playNum); //������Ϸ��ʼ�����뻭���ź�

private:
	Ui::Start2 *ui;
	int m_playNum;
};

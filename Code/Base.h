#pragma once

#include <QWidget>
#include <QObject>

class Base : public QObject
{
	Q_OBJECT

public:

	//枚举类型，控制方向
	enum  Direction {
		Direction_None = 0,
		Direction_Up,
		Direction_Left,
		Direction_Down,
		Direction_Right
	};

	Base(int xx = 0, int yy = 0, Direction ddirec = Direction_Up);
	virtual ~Base();

	//x，y坐标
	int x;
	int y;
	Direction direc;

};

#pragma once

#include <iostream>
#include "Configure.h"



using namespace std;
/*
0 空白   1 普通敌人
B 基地   2 速度快敌人
I 钢铁   3 子弹快敌人
W 墙壁L  4 BUFF敌人
V 墙壁R  5 护甲敌人
G 草地   6
R 河流   7
P 玩家1  8
Q 玩家2  9
*/

class MyMap {
public:
	MyMap();
	~MyMap();

    static char* m_map;
    //地图初始化
    static void initMap();

    //设置和获取地图
    static void setMap(int x, int y, char value);
    static char getMap(int x, int y);


    static void setWall26(int x, int y);
    static void setWall13(int x, int y);
    static void setBigCell(int x, int y, char value);
    static void setBase();  //设置基地

    static void stageTest();    //Test关卡
    static void stage1();   //第一关
    static void stage2();   //第二关
    static void setStage(int stage);    //设置关卡
};

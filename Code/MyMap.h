#pragma once

#include <iostream>
#include "Configure.h"



using namespace std;
/*
0 �հ�   1 ��ͨ����
B ����   2 �ٶȿ����
I ����   3 �ӵ������
W ǽ��L  4 BUFF����
V ǽ��R  5 ���׵���
G �ݵ�   6
R ����   7
P ���1  8
Q ���2  9
*/

class MyMap {
public:
	MyMap();
	~MyMap();

    static char* m_map;
    //��ͼ��ʼ��
    static void initMap();

    //���úͻ�ȡ��ͼ
    static void setMap(int x, int y, char value);
    static char getMap(int x, int y);


    static void setWall26(int x, int y);
    static void setWall13(int x, int y);
    static void setBigCell(int x, int y, char value);
    static void setBase();  //���û���

    static void stageTest();    //Test�ؿ�
    static void stage1();   //��һ��
    static void stage2();   //�ڶ���
    static void setStage(int stage);    //���ùؿ�
};

#include "MyMap.h"

char* MyMap::m_map = new char[CELL_NUMBER * CELL_NUMBER];//104x104

MyMap::MyMap()
{

}

MyMap::~MyMap()
{
    if (m_map != NULL)
        delete[] m_map;
}


//初始化地图
void MyMap::initMap()
{
    for (int i = 0; i < CELL_NUMBER * CELL_NUMBER; i++)
    {
        m_map[i] = 0;
    }
}

//设置地图，并保存值
void MyMap::setMap(int x, int y, char value)
{
    m_map[y * CELL_NUMBER + x] = value;
}
//得到地图里的值
char MyMap::getMap(int x, int y)
{
    return m_map[y * CELL_NUMBER + x];
}


//设置墙  4*4
void MyMap::setWall26(int x, int y)
{
    setMap(x, y, 'W');
    setMap(x + 2, y, 'V');
    setMap(x, y + 2, 'V');
    setMap(x + 2, y + 2, 'W');
}
//设置墙  8*8
void MyMap::setWall13(int x, int y)
{
    setWall26(x, y);
    setWall26(x + 4, y);
    setWall26(x, y + 4);
    setWall26(x + 4, y + 4);
}

//设置8*8区域
void MyMap::setBigCell(int x, int y, char value)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            setMap(x + j, y + i, value);
        }
    }
}

//设置基地
void MyMap::setBase()
{
    setWall26(22 * 2, 46 * 2);
    setWall26(2 * 22, 48 * 2);
    setWall26(22 * 2, 50 * 2);

    setWall26(28 * 2, 46 * 2);
    setWall26(28 * 2, 48 * 2);
    setWall26(28 * 2, 50 * 2);

    setWall26(24 * 2, 46 * 2);
    setWall26(26 * 2, 46 * 2);

    setMap(24 * 2, 48 * 2, 'B');
}


//设置关卡
void MyMap::setStage(int stage)
{
    if (stage == 0)
        stageTest();
    if (stage == 1)
        stage1();
    if (stage == 2)
        stage2();
}


//测试关卡
void MyMap::stageTest()
{
    setBase();

    //setWall13(0, 8);
    //setWall13(32, 8);

    //for (int y = 40; y < 48; y += 8)
    //{
    //    for (int x = 16; x < 48; x += 8)
    //    {
    //        setWall13(x, y);
    //    }
    //}

    //for (int y = 56; y < 64; y += 8)
    //{
    //    for (int x = 0; x < 96; x += 8)
    //    {
    //        setWall13(x, y);
    //    }
    //}

    //for (int y = 24; y < 32; y += 8)
    //{
    //    for (int x = 16; x < 48; x += 8)
    //    {
    //        setWall13(x, y);
    //    }
    //}
}


//设置第一关
void MyMap::stage1()
{
    setBase();

    setWall26(8, 8);
    setWall26(12, 8);
    setWall26(24, 8);
    setWall26(28, 8);
    setWall26(40, 8);
    setWall26(44, 8);
    setWall26(56, 8);
    setWall26(60, 8);
    setWall26(72, 8);
    setWall26(76, 8);
    setWall26(88, 8);
    setWall26(92, 8);
    setWall26(8, 12);
    setWall26(12, 12);
    setWall26(24, 12);
    setWall26(28, 12);
    setWall26(40, 12);
    setWall26(44, 12);
    setWall26(56, 12);
    setWall26(60, 12);
    setWall26(72, 12);
    setWall26(76, 12);
    setWall26(88, 12);
    setWall26(92, 12);
    setWall26(8, 16);
    setWall26(12, 16);
    setWall26(24, 16);
    setWall26(28, 16);
    setWall26(40, 16);
    setWall26(44, 16);
    setWall26(56, 16);
    setWall26(60, 16);
    setWall26(72, 16);
    setWall26(76, 16);
    setWall26(88, 16);
    setWall26(92, 16);
    setWall26(8, 20);
    setWall26(12, 20);
    setWall26(24, 20);
    setWall26(28, 20);
    setWall26(40, 20);
    setWall26(44, 20);
    setWall26(56, 20);
    setWall26(60, 20);
    setWall26(72, 20);
    setWall26(76, 20);
    setWall26(88, 20);
    setWall26(92, 20);
    setWall26(8, 24);
    setWall26(12, 24);
    setWall26(24, 24);
    setWall26(28, 24);
    setWall26(40, 24);
    setWall26(44, 24);
    setMap(48, 24, 'I');
    setMap(52, 24, 'I');
    setWall26(56, 24);
    setWall26(60, 24);
    setWall26(72, 24);
    setWall26(76, 24);
    setWall26(88, 24);
    setWall26(92, 24);
    setWall26(8, 28);
    setWall26(12, 28);
    setWall26(24, 28);
    setWall26(28, 28);
    setWall26(40, 28);
    setWall26(44, 28);
    setMap(48, 28, 'I');
    setMap(52, 28, 'I');
    setWall26(56, 28);
    setWall26(60, 28);
    setWall26(72, 28);
    setWall26(76, 28);
    setWall26(88, 28);
    setWall26(92, 28);
    setWall26(8, 32);
    setWall26(12, 32);
    setWall26(24, 32);
    setWall26(28, 32);
    setWall26(40, 32);
    setWall26(44, 32);
    setWall26(56, 32);
    setWall26(60, 32);
    setWall26(72, 32);
    setWall26(76, 32);
    setWall26(88, 32);
    setWall26(92, 32);
    setWall26(8, 36);
    setWall26(12, 36);
    setWall26(24, 36);
    setWall26(28, 36);
    setWall26(72, 36);
    setWall26(76, 36);
    setWall26(88, 36);
    setWall26(92, 36);
    setWall26(8, 40);
    setWall26(12, 40);
    setWall26(24, 40);
    setWall26(28, 40);
    setWall26(72, 40);
    setWall26(76, 40);
    setWall26(88, 40);
    setWall26(92, 40);
    setWall26(40, 44);
    setWall26(44, 44);
    setWall26(56, 44);
    setWall26(60, 44);
    setWall26(40, 48);
    setWall26(44, 48);
    setWall26(56, 48);
    setWall26(60, 48);
    setWall26(0, 52);
    setWall26(4, 52);
    setWall26(16, 52);
    setWall26(20, 52);
    setWall26(24, 52);
    setWall26(28, 52);
    setWall26(72, 52);
    setWall26(76, 52);
    setWall26(80, 52);
    setWall26(84, 52);
    setWall26(96, 52);
    setWall26(100, 52);
    setMap(0, 56, 'I');
    setMap(4, 56, 'I');
    setWall26(16, 56);
    setWall26(20, 56);
    setWall26(24, 56);
    setWall26(28, 56);
    setWall26(72, 56);
    setWall26(76, 56);
    setWall26(80, 56);
    setWall26(84, 56);
    setMap(96, 56, 'I');
    setMap(100, 56, 'I');
    setWall26(40, 60);
    setWall26(44, 60);
    setWall26(56, 60);
    setWall26(60, 60);
    setWall26(40, 64);
    setWall26(44, 64);
    setWall26(48, 64);
    setWall26(52, 64);
    setWall26(56, 64);
    setWall26(60, 64);
    setWall26(8, 68);
    setWall26(12, 68);
    setWall26(24, 68);
    setWall26(28, 68);
    setWall26(40, 68);
    setWall26(44, 68);
    setWall26(48, 68);
    setWall26(52, 68);
    setWall26(56, 68);
    setWall26(60, 68);
    setWall26(72, 68);
    setWall26(76, 68);
    setWall26(88, 68);
    setWall26(92, 68);
    setWall26(8, 72);
    setWall26(12, 72);
    setWall26(24, 72);
    setWall26(28, 72);
    setWall26(40, 72);
    setWall26(44, 72);
    setWall26(56, 72);
    setWall26(60, 72);
    setWall26(72, 72);
    setWall26(76, 72);
    setWall26(88, 72);
    setWall26(92, 72);
    setWall26(8, 76);
    setWall26(12, 76);
    setWall26(24, 76);
    setWall26(28, 76);
    setWall26(40, 76);
    setWall26(44, 76);
    setWall26(56, 76);
    setWall26(60, 76);
    setWall26(72, 76);
    setWall26(76, 76);
    setWall26(88, 76);
    setWall26(92, 76);
    setWall26(8, 80);
    setWall26(12, 80);
    setWall26(24, 80);
    setWall26(28, 80);
    setWall26(40, 80);
    setWall26(44, 80);
    setWall26(56, 80);
    setWall26(60, 80);
    setWall26(72, 80);
    setWall26(76, 80);
    setWall26(88, 80);
    setWall26(92, 80);
    setWall26(8, 84);
    setWall26(12, 84);
    setWall26(24, 84);
    setWall26(28, 84);
    setWall26(72, 84);
    setWall26(76, 84);
    setWall26(88, 84);
    setWall26(92, 84);
    setWall26(8, 88);
    setWall26(12, 88);
    setWall26(24, 88);
    setWall26(28, 88);
    setWall26(72, 88);
    setWall26(76, 88);
    setWall26(88, 88);
    setWall26(92, 88);
    setWall26(8, 92);
    setWall26(12, 92);
    setWall26(24, 92);
    setWall26(28, 92);
    setWall26(72, 92);
    setWall26(76, 92);
    setWall26(88, 92);
    setWall26(92, 92);
}


//设置第二关
void MyMap::stage2()
{
    setBase();

    setMap(24, 0, 'I');
    setMap(28, 0, 'I');
    setMap(56, 0, 'I');
    setMap(60, 0, 'I');
    setMap(24, 4, 'I');
    setMap(28, 4, 'I');
    setMap(56, 4, 'I');
    setMap(60, 4, 'I');
    setWall26(8, 8);
    setWall26(12, 8);
    setMap(24, 8, 'I');
    setMap(28, 8, 'I');
    setWall26(56, 8);
    setWall26(60, 8);
    setWall26(72, 8);
    setWall26(76, 8);
    setWall26(88, 8);
    setWall26(92, 8);
    setWall26(8, 12);
    setWall26(12, 12);
    setMap(24, 12, 'I');
    setMap(28, 12, 'I');
    setWall26(56, 12);
    setWall26(60, 12);
    setWall26(72, 12);
    setWall26(76, 12);
    setWall26(88, 12);
    setWall26(92, 12);
    setWall26(8, 16);
    setWall26(12, 16);
    setWall26(48, 16);
    setWall26(52, 16);
    setWall26(56, 16);
    setWall26(60, 16);
    setWall26(72, 16);
    setWall26(76, 16);
    setMap(80, 16, 'I');
    setMap(84, 16, 'I');
    setWall26(88, 16);
    setWall26(92, 16);
    setWall26(8, 20);
    setWall26(12, 20);
    setWall26(48, 20);
    setWall26(52, 20);
    setWall26(56, 20);
    setWall26(60, 20);
    setWall26(72, 20);
    setWall26(76, 20);
    setMap(80, 20, 'I');
    setMap(84, 20, 'I');
    setWall26(88, 20);
    setWall26(92, 20);
    setWall26(24, 24);
    setWall26(28, 24);
    setMap(72, 24, 'I');
    setMap(76, 24, 'I');
    setWall26(24, 28);
    setWall26(28, 28);
    setMap(72, 28, 'I');
    setMap(76, 28, 'I');
    setMap(0, 32, 'G');
    setMap(4, 32, 'G');
    setWall26(24, 32);
    setWall26(28, 32);
    setMap(48, 32, 'I');
    setMap(52, 32, 'I');
    setWall26(72, 32);
    setWall26(76, 32);
    setMap(80, 32, 'G');
    setMap(84, 32, 'G');
    setWall26(88, 32);
    setWall26(92, 32);
    setMap(96, 32, 'I');
    setMap(100, 32, 'I');
    setMap(0, 36, 'G');
    setMap(4, 36, 'G');
    setWall26(24, 36);
    setWall26(28, 36);
    setMap(48, 36, 'I');
    setMap(52, 36, 'I');
    setWall26(72, 36);
    setWall26(76, 36);
    setMap(80, 36, 'G');
    setMap(84, 36, 'G');
    setWall26(88, 36);
    setWall26(92, 36);
    setMap(96, 36, 'I');
    setMap(100, 36, 'I');
    setMap(0, 40, 'G');
    setMap(4, 40, 'G');
    setMap(8, 40, 'G');
    setMap(12, 40, 'G');
    setWall26(40, 40);
    setWall26(44, 40);
    setMap(64, 40, 'I');
    setMap(68, 40, 'I');
    setMap(80, 40, 'G');
    setMap(84, 40, 'G');
    setMap(0, 44, 'G');
    setMap(4, 44, 'G');
    setMap(8, 44, 'G');
    setMap(12, 44, 'G');
    setWall26(40, 44);
    setWall26(44, 44);
    setMap(64, 44, 'I');
    setMap(68, 44, 'I');
    setMap(80, 44, 'G');
    setMap(84, 44, 'G');
    setWall26(8, 48);
    setWall26(12, 48);
    setWall26(16, 48);
    setWall26(20, 48);
    setWall26(24, 48);
    setWall26(28, 48);
    setMap(32, 48, 'G');
    setMap(36, 48, 'G');
    setMap(40, 48, 'G');
    setMap(44, 48, 'G');
    setMap(48, 48, 'G');
    setMap(52, 48, 'G');
    setMap(56, 48, 'I');
    setMap(60, 48, 'I');
    setMap(80, 48, 'G');
    setMap(84, 48, 'G');
    setWall26(88, 48);
    setWall26(92, 48);
    setWall26(8, 52);
    setWall26(12, 52);
    setWall26(16, 52);
    setWall26(20, 52);
    setWall26(24, 52);
    setWall26(28, 52);
    setMap(32, 52, 'G');
    setMap(36, 52, 'G');
    setMap(40, 52, 'G');
    setMap(44, 52, 'G');
    setMap(48, 52, 'G');
    setMap(52, 52, 'G');
    setMap(56, 52, 'I');
    setMap(60, 52, 'I');
    setMap(80, 52, 'G');
    setMap(84, 52, 'G');
    setWall26(88, 52);
    setWall26(92, 52);
    setMap(24, 56, 'I');
    setMap(28, 56, 'I');
    setMap(32, 56, 'G');
    setMap(36, 56, 'G');
    setWall26(40, 56);
    setWall26(44, 56);
    setWall26(56, 56);
    setWall26(60, 56);
    setWall26(72, 56);
    setWall26(76, 56);
    setWall26(88, 56);
    setWall26(92, 56);
    setMap(24, 60, 'I');
    setMap(28, 60, 'I');
    setMap(32, 60, 'G');
    setMap(36, 60, 'G');
    setWall26(40, 60);
    setWall26(44, 60);
    setWall26(56, 60);
    setWall26(60, 60);
    setWall26(72, 60);
    setWall26(76, 60);
    setWall26(88, 60);
    setWall26(92, 60);
    setMap(0, 64, 'I');
    setMap(4, 64, 'I');
    setWall26(8, 64);
    setWall26(12, 64);
    setMap(24, 64, 'I');
    setMap(28, 64, 'I');
    setWall26(40, 64);
    setWall26(44, 64);
    setWall26(56, 64);
    setWall26(60, 64);
    setWall26(88, 64);
    setWall26(92, 64);
    setMap(0, 68, 'I');
    setMap(4, 68, 'I');
    setWall26(8, 68);
    setWall26(12, 68);
    setMap(24, 68, 'I');
    setMap(28, 68, 'I');
    setWall26(40, 68);
    setWall26(44, 68);
    setWall26(56, 68);
    setWall26(60, 68);
    setWall26(88, 68);
    setWall26(92, 68);
    setWall26(8, 72);
    setWall26(12, 72);
    setWall26(24, 72);
    setWall26(28, 72);
    setWall26(40, 72);
    setWall26(44, 72);
    setWall26(48, 72);
    setWall26(52, 72);
    setWall26(56, 72);
    setWall26(60, 72);
    setWall26(72, 72);
    setWall26(76, 72);
    setMap(80, 72, 'I');
    setMap(84, 72, 'I');
    setWall26(88, 72);
    setWall26(92, 72);
    setWall26(8, 76);
    setWall26(12, 76);
    setWall26(24, 76);
    setWall26(28, 76);
    setWall26(40, 76);
    setWall26(44, 76);
    setWall26(48, 76);
    setWall26(52, 76);
    setWall26(56, 76);
    setWall26(60, 76);
    setWall26(72, 76);
    setWall26(76, 76);
    setMap(80, 76, 'I');
    setMap(84, 76, 'I');
    setWall26(88, 76);
    setWall26(92, 76);
    setWall26(8, 80);
    setWall26(12, 80);
    setWall26(24, 80);
    setWall26(28, 80);
    setWall26(40, 80);
    setWall26(44, 80);
    setWall26(48, 80);
    setWall26(52, 80);
    setWall26(56, 80);
    setWall26(60, 80);
    setWall26(8, 84);
    setWall26(12, 84);
    setWall26(24, 84);
    setWall26(28, 84);
    setWall26(40, 84);
    setWall26(44, 84);
    setWall26(48, 84);
    setWall26(52, 84);
    setWall26(56, 84);
    setWall26(60, 84);
    setWall26(8, 88);
    setWall26(12, 88);
    setWall26(72, 88);
    setWall26(76, 88);
    setWall26(88, 88);
    setWall26(92, 88);
    setWall26(8, 92);
    setWall26(12, 92);
    setWall26(72, 92);
    setWall26(76, 92);
    setWall26(88, 92);
    setWall26(92, 92);
    setWall26(8, 96);
    setWall26(12, 96);
    setWall26(24, 96);
    setWall26(28, 96);
    setWall26(72, 96);
    setWall26(76, 96);
    setWall26(80, 96);
    setWall26(84, 96);
    setWall26(88, 96);
    setWall26(92, 96);
    setWall26(8, 100);
    setWall26(12, 100);
    setWall26(24, 100);
    setWall26(28, 100);
    setWall26(72, 100);
    setWall26(76, 100);
    setWall26(80, 100);
    setWall26(84, 100);
    setWall26(88, 100);
    setWall26(92, 100);
}



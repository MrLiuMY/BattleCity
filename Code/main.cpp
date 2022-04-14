#include "BattleCity.h"
#include "Start1.h"
#include "Start2.h"
#include "GameOver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start1 st1; //��ʼ����1
    st1.show();
    Start2 st2;
    st2.hide();
    BattleCity w;   //��Ϸ����
    w.hide();
    GameOver over;  //��������
    over.hide();

    QObject::connect(&st1, &Start1::signalGameStart1 ,&st2, &Start2::slotGameStart1);
    QObject::connect(&st2, &Start2::signalGameStart2, &w, &BattleCity::slotGameStart2);
    QObject::connect(&w, &BattleCity::signalGameOver, &over, &GameOver::slotGameOver);


    return a.exec();
}

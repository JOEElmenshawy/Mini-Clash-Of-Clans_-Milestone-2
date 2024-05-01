#ifndef GAME_H
#define GAME_H
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QMouseEvent>
#include "castle.h"
#include "fence.h"
#include "defense.h"
#include"bullet.h"
#include "enemy.h"
#include <QObject>
#include <QTimer>
#include<QMouseEvent>
class  Game: public QGraphicsView
{

public:
    Game();
     void mousePressEvent(QMouseEvent* event) override ;
    bool eventFilter(QObject *obj, QEvent *event) override;
     void gameOver();
    void showview();
     Castle* getCastle();
    std::vector<std::vector<ObjectStruct*>> objects;
public slots:
private:
    QGraphicsView * view;
QGraphicsScene * scene;
    Castle* castle;
    Fence** fence;
    Defense* defense;
    int NumberOfFences;
    QTimer* wintimer;
};

#endif // GAME_H

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
class  Game:public QGraphicsView
{
Q_OBJECT
public:
    Game(int h);
    bool powerup;
     void mousePressEvent(QMouseEvent* event) override ;
    bool eventFilter(QObject *obj, QEvent *event) override;
     void gameOver();
    void showview();
     Castle* getCastle();
    int cannonx,cannony;
     int enemydestroyed;
    std::vector<std::vector<ObjectStruct*>> objects;
public slots:
    void createEnemy();
    void createCitizens();
private:
    QGraphicsView * view;
    int hardness;
QGraphicsScene * scene;
    Castle* castle;
    Fence** fence;
    Defense* defense;
    int NumberOfFences;
    QTimer* wintimer;
    QTimer* Enemytimer;
    QTimer*CitizenTimer;
    int Iterator;
};

#endif // GAME_H

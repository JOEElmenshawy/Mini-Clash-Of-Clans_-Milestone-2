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
#include <QMediaPlayer>
#include<QAudioOutput>
class  Game:public QGraphicsView
{
Q_OBJECT
public:
    Game(int h);
    bool powerup;
    bool powermarker;
     void mousePressEvent(QMouseEvent* event) override ;
    bool eventFilter(QObject *obj, QEvent *event) override;
     void gameOver();
    void showview();
     void boostshootpower();
     Castle* getCastle();
    int cannonx,cannony;
     int enemydestroyed;
    std::vector<std::vector<ObjectStruct*>> objects;
     ~Game();
public slots:
    void createEnemy();
    void createCitizens();
    void createMarkers();
private:
    QGraphicsView * view;
    int hardness;
    int extradamage;
    QMediaPlayer*Q;
QGraphicsScene * scene;
    Castle* castle;
    Fence** fence;
    Defense* defense;
    QTimer* wintimer;
    QTimer* Enemytimer;
    QTimer*CitizenTimer;
    QTimer* MarkerTimer;
    QTimer* boostdamagetimer;
    int Iterator;
};

#endif // GAME_H

#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsRectItem>
#include <QObject>
#include "castle.h"
#include "fence.h"
#include<QTimer>
class Enemy:public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(Castle*,Fence **, int);
    void Die();
    void DecreaseHealth();
private:
    Castle * castleEnemy;
    Fence ** fenceEnemy;
    int fencecount;
    bool continuemove;
    int health;

public slots:
    void move();

};

#endif // ENEMY_H

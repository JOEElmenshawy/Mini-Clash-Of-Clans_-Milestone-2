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
    Enemy();
    void Die();
    void DecreaseHealth();
private:
    bool continuemove;
    int health;
    bool enemydied;
    QTimer* MoveTimer;
public slots:
    void move();

};

#endif // ENEMY_H

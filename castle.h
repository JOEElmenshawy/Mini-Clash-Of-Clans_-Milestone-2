#ifndef CASTLE_H
#define CASTLE_H
#include <QGraphicsRectItem>
#include <QObject>
#include "fence.h"

class Castle: public QObject , public QGraphicsPixmapItem
{ Q_OBJECT
public:
    Castle(Fence **,int);
    void Die();
    void DecreaseHealth();

public slots:
void createEnemy();
    void createCitizens();

private:
Fence** fencePassEnemy;
    int fenceCount;
    int health;
    int Iterator;
    bool shown;

};

#endif

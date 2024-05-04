#ifndef FENCE_H
#define FENCE_H
#include <QGraphicsRectItem>
#include <QObject>
#include<QGraphicsScene>
#include"objectstruct.h"
class Fence:public QObject , public ObjectStruct
{
public:
    Fence();
    void DecreaseHealth(int d);
    void Die();

private:
    int health;
    QGraphicsItem * border;
};

#endif // FENCE_H

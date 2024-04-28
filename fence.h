#ifndef FENCE_H
#define FENCE_H
#include <QGraphicsRectItem>
#include <QObject>
#include<QGraphicsScene>
class Fence:public QObject , public QGraphicsPixmapItem
{
public:
    Fence();
    void DecreaseHealth();
    void Die();

private:
    int health;
    QGraphicsItem * border;
};

#endif // FENCE_H

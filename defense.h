#ifndef DEFENSE_H
#define DEFENSE_H
#include <QGraphicsRectItem>
#include <QObject>
#include<QMouseEvent>
#include<QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include<QKeyEvent>
class Defense:public QObject , public QGraphicsPixmapItem
{
public:
    Defense();



private:
    int health;
};

#endif // DEFENSE_H

#ifndef DEFENSE_H
#define DEFENSE_H
#include <QGraphicsRectItem>
#include <QObject>
#include<QMouseEvent>
#include<QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include<QKeyEvent>
#include"objectstruct.h"
class Defense:public QObject , public ObjectStruct
{
public:
    Defense();



private:
    int health;
};

#endif // DEFENSE_H

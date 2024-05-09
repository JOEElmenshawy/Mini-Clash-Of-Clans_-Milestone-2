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
    int health;
    std::vector <QPixmap> rotatingPictures;
    int frame;
    QPoint CurserPoint;
    void Animate();
    float getRatio();
    float Ratio;
};

#endif // DEFENSE_H

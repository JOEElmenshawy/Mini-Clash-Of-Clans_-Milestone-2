#ifndef BULLET_H
#define BULLET_H
#include<QGraphicsPixmapItem>
#include<QObject>
#include<QGraphicsItem>
class bullet:public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT
public slots:
    void move();
public:
    bullet(int x, int y);
    double CalculatePos();
private:
    int targetX;
    int targetY;

};

#endif // BULLET_H

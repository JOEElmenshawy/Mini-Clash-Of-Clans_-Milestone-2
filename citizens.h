#ifndef CITIZENS_H
#define CITIZENS_H
#include<QGraphicsPixmapItem>
#include<QObject>

class Citizens:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Citizens();
public slots:

    void move();
private:
    int sign;
};

#endif // CITIZENS_H

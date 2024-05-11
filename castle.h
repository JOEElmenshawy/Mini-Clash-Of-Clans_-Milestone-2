#ifndef CASTLE_H
#define CASTLE_H
#include <QGraphicsRectItem>
#include <QObject>
#include "fence.h"
#include <Qtime>
#include"UniqueNode.h"
class Castle: public QObject , public UniqueNode
{ Q_OBJECT
public:
    Castle();
    void Die();
    void DecreaseHealth(int d);
    int castleRow;
    int castleColumn;
public slots:


private:
    int health;

    bool shown;

};

#endif

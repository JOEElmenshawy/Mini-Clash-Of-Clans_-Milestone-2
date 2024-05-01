#ifndef CASTLE_H
#define CASTLE_H
#include <QGraphicsRectItem>
#include <QObject>
#include "fence.h"
#include <Qtime>
#include"objectstruct.h"
class Castle: public QObject , public ObjectStruct
{ Q_OBJECT
public:
    Castle();
    void Die();
    void DecreaseHealth();

public slots:
void createEnemy();
    void createCitizens();

private:
    int health;
    int Iterator;
    bool shown;
    QTimer* Enemytimer;
    QTimer*CitizenTimer;
};

#endif

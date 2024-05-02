#include "citizens.h"
#include"fence.h"
#include"QTimer"
Citizens::Citizens() {

    sign=1;


    setPixmap(QPixmap(":/new/images/images/citizenWorker.png").scaled(40, 40));

    this->setPos(400+rand()%250 ,330 + rand()%250 );
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100);
}

void Citizens::move()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Fence)) {
            Fence *fence = dynamic_cast<Fence*>(colliding_items[i]);
            if (fence) {
                // Call member functions specific to Fence
                sign=-sign;
            }
        }
    }
    setPos(x()+5*sign, y()+5* sign);
}

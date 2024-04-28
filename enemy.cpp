#include "enemy.h"
#include <cmath>
#include <QGraphicsScene>
#include"game.h"
extern Game *g;
Enemy::Enemy(Castle* c,Fence ** f, int co)
{

    castleEnemy=c;
    fenceEnemy=f;
    fencecount=co;
    continuemove =true;
    health = 3;
    setPixmap(QPixmap(":/new/images/images/enemy.png").scaled(75, 75));

    int random_number = rand() %(1080);
    while(random_number>100&&random_number<980)
    {random_number=rand()%1080;}
    int random_number2= rand()%750;
    while(random_number2>70 &&random_number2<680)
    {
        random_number2= rand()%750;
    }
    setPos(random_number,random_number2);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT (move()));
   timer->start(200);

}
void Enemy::DecreaseHealth(){
    health--;
    Die();
}

void Enemy::Die(){
    if(health<=0){
        scene()->removeItem(this);
        delete this;
    }

}
void Enemy::move()
{
    continuemove=true;
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Fence)) {
            Fence *fence = dynamic_cast<Fence*>(colliding_items[i]);
            if (fence) {
                // Call member functions specific to Fence
                fence->DecreaseHealth();
                continuemove = false;

            }
        }
    }
    QList<QGraphicsItem*> colliding_items2 = collidingItems();
    for (int i = 0, n = colliding_items2.size(); i < n; ++i) {
        if (typeid(*(colliding_items2[i])) == typeid(Castle)) {
            Castle *C = dynamic_cast<Castle*>(colliding_items2[i]);
            if (C) {
                // Call member functions specific to Fence
                C->DecreaseHealth();
                continuemove = false;

            }
        }
    }
    if(continuemove){
        if(x()> castleEnemy->x())
        {
            setPos(x()-5,y());
        }
        if(x() < castleEnemy->x()){
            setPos(x()+5,y());
        }
        if(y() > castleEnemy->y()){
            setPos(x(),y()-5);
        }
        if(y() < castleEnemy->y()){
            setPos(x(),y()+5);
        }
    }



}

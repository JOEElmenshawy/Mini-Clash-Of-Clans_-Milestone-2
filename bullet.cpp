#include "bullet.h"
#include<QPixmap>
#include<QTimer>
#include<qmath.h> //to use sin , cos ... etc
#include<QGraphicsScene>
#include"enemy.h"
#include "healthmarker.h"
#include"game.h"
#include "mainwindow.h"
extern Game *g;
bullet::bullet(int x, int y,int d):targetX(x),targetY(y),damage(d) {
    this->setPixmap(QPixmap (":/new/images/images/cannonball_PNG10.png").scaled(15,15));

    QTimer * timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

double bullet::CalculatePos()
{
    double dx2 = targetX - 75*5;
    double dy2 = targetY - 75*4;
    double theta2 = qAtan2(dy2, dx2) * 180 / M_PI;
    return theta2;
}
void bullet::move()
{
    if(g->enemydestroyed==2&&!g->powerup)
    {
        g->powerup=true;
        damage+=damage*0.10;
        qDebug()<<"damage increased";
    }
    QList<QGraphicsItem*> colliding_items1 = collidingItems();
    for (int i = 0, n = colliding_items1.size(); i < n; ++i) {
        if (typeid(*(colliding_items1[i])) == typeid(HealthMarker)) {
            HealthMarker* h  = dynamic_cast<HealthMarker*>(colliding_items1[i]);
            if (h) {
                scene()->removeItem(h);
                delete h;
                g->boostshootpower();
            }
        }
    }
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            Enemy *e = dynamic_cast<Enemy*>(colliding_items[i]);
            if (e) {

                // Call member functions specific to Fence
                e->DecreaseHealth(damage);
                scene()->removeItem(this);
                delete this;

            }
        }
    }
    if(x()<0|| x()>1125||y()<0||y()>750)
    {
        scene()->removeItem(this);
            delete this;
    }
    int STEP =10;

     // Angle in degrees

    // Set the rotation of the bullet to face the target
    setRotation(CalculatePos());
    double theta=rotation();//in degrees

    double dy= STEP*qSin(qDegreesToRadians(theta));
    double dx= STEP*qCos(qDegreesToRadians(theta));
    setPos(x()+dx,y()+dy);

}

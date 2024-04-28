#include "castle.h"
#include "enemy.h"
#include"game.h"
#include <QGraphicsScene>
#include"game.h"
#include"citizens.h"


extern Game *g;
Castle::Castle(Fence ** f, int c) {
    Iterator=0;
    health=40;
    fencePassEnemy=f;
    fenceCount=c;

    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(createEnemy()));
    timer->start(3000);
    QTimer * timer2 = new QTimer();
    QObject::connect(timer2,SIGNAL(timeout()),this,SLOT(createCitizens()));
    timer2->start(50);


 }

void Castle::createEnemy()
{

    Enemy* e= new Enemy(this,fencePassEnemy,fenceCount);
    scene()->addItem(e);




}
void Castle::createCitizens()
{
    if(Iterator<5)
    {Citizens* c = new Citizens;
        scene()->addItem(c);}
    Iterator++;
}
void Castle::DecreaseHealth(){
    health--;
    if(health==0){
        Die();
    }
}

void Castle::Die(){

    g->gameOver();



}

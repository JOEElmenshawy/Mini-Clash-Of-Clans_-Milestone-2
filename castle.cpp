#include "castle.h"
#include "enemy.h"
#include"game.h"
#include <QGraphicsScene>
#include"game.h"
#include"citizens.h"


extern Game *g;
Castle::Castle() {
    Iterator=0;
    health=40;

    Enemytimer = new QTimer();
    QObject::connect(Enemytimer,SIGNAL(timeout()),this,SLOT(createEnemy()));
    Enemytimer->start(2000);
    CitizenTimer = new QTimer();
    QObject::connect(  CitizenTimer,SIGNAL(timeout()),this,SLOT(createCitizens()));
    CitizenTimer->start(50);
    name = "Castle";
    ID = 2;
    healthBar = 3000;

 }

void Castle::createEnemy()
{

    Enemy* e= new Enemy();
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
    qDebug()<<"castle health decreased";
    if(health==0){
        Die();
    }
}

void Castle::Die(){

    g->gameOver();



}

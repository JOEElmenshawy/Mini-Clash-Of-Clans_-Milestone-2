#include "castle.h"
#include "enemy.h"
#include"game.h"
#include <QGraphicsScene>
#include"game.h"
#include"citizens.h"


extern Game *g;
Castle::Castle() {

    health=40;


    name = "Castle";
    healthBar = 3000;

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

#include "fence.h"
#include"game.h"
extern Game *g;
Fence::Fence() {

    health = 10;
    costToPass=60;
    QPixmap fencephoto (":/new/images/images/fence.png");
    fencephoto=fencephoto.scaledToWidth(75);
    fencephoto=fencephoto.scaledToHeight(75);
    setPixmap(fencephoto);
    name = "fence";
}

void Fence::DecreaseHealth(int d){
    health-=d;
    costToPass-=5*d;
    if(health<0)
        health=0;
    if(costToPass<10)
        costToPass=10;
    Die();
}

void Fence::Die(){
    if(health<=0){
        scene()->removeItem(this);

    }

}

void Fence::increaseHealth()
{
    health+=1;
    costToPass+=5*1;
    if(health>10)
        health=10;
    if(costToPass>60)
        costToPass=60;
}

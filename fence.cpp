#include "fence.h"
#include"game.h"
extern Game *g;
Fence::Fence() {
    health = 10;
    QPixmap fencephoto (":/new/images/images/fence.png");
    fencephoto=fencephoto.scaledToWidth(75);
    fencephoto=fencephoto.scaledToHeight(75);
    setPixmap(fencephoto);
}

void Fence::DecreaseHealth(){
    health--;
    Die();
}

void Fence::Die(){
    if(health<=0){
        scene()->removeItem(this);
        delete this;
    }

}

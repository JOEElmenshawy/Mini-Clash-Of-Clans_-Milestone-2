#include "fence.h"
#include"game.h"
extern Game *g;
Fence::Fence() {
    health = 10;

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

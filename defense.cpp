#include "defense.h"
#include<QGraphicsSceneMouseEvent>
#include"game.h"
extern Game *g;
Defense::Defense() {
    costToPass=2000;
    name="cannon";
    QPixmap defencephoto (":/new/images/images/cannon.png");
    defencephoto=defencephoto.scaledToWidth(75);
    defencephoto=defencephoto.scaledToHeight(75);
    setPixmap(defencephoto);
}




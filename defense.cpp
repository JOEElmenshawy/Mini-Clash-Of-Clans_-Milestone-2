#include "defense.h"
#include<QGraphicsSceneMouseEvent>
#include"game.h"
extern Game *g;
Defense::Defense() {
    QPixmap defencephoto (":/new/images/images/cannon.png");
    defencephoto=defencephoto.scaledToWidth(75);
    defencephoto=defencephoto.scaledToHeight(75);
    setPixmap(defencephoto);
}




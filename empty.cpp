#include "empty.h"

empty::empty()
{
    QPixmap grassphoto (":/new/images/images/grass.png");
    grassphoto=grassphoto.scaledToWidth(75);
    grassphoto=grassphoto.scaledToHeight(75);
    setPixmap(grassphoto);
    name = "";
    ID = 0;
    healthBar = 600;

}

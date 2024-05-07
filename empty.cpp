#include "empty.h"

empty::empty()
{
    costToPass=10;
    QPixmap grassphoto (":/new/images/images/grass.png");
    grassphoto=grassphoto.scaledToWidth(75);
    grassphoto=grassphoto.scaledToHeight(75);
    setPixmap(grassphoto);
    name = "emptyland";

}

#include "empty.h"
extern QString land;
empty::empty()
{
    costToPass=new int();
    *costToPass=10;
    QPixmap landphoto (land);
    landphoto=landphoto.scaledToWidth(75);
    landphoto=landphoto.scaledToHeight(75);
    setPixmap(landphoto);
    name = "emptyland";

}

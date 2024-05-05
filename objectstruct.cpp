#include "objectstruct.h"

ObjectStruct::ObjectStruct()
{

}

ObjectStruct::~ObjectStruct(){
}



ObjectStruct::ObjectStruct(const ObjectStruct& other) {
    setPos(other.pos());
    id = other.id;
    name = other.name;
    setPixmap(other.pixmap());
}

#include "UniqueNode.h"

UniqueNode::UniqueNode()
{
}


UniqueNode::~UniqueNode(){
}



UniqueNode::UniqueNode(const UniqueNode& other) {
    setPos(other.pos());
    id = other.id;
    costToPass=other.costToPass;
    name = other.name;
    setPixmap(other.pixmap());
}

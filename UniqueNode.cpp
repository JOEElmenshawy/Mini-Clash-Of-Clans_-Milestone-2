#include "UniqueNode.h"

UniqueNode::UniqueNode()
{

}


UniqueNode::~UniqueNode(){
}



UniqueNode::UniqueNode(const UniqueNode& other) {
    setPos(other.pos());
    id = other.id;
    name = other.name;
    setPixmap(other.pixmap());
}

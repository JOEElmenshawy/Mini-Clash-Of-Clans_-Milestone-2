#include "node.h"

node::node(QGraphicsPixmapItem *_object): object(_object), parent(nullptr) {
}

//node::node(ObjectStruct* _object) : object(*_object), gCost(0.0f), hCost(0.0f), parent(nullptr)
//{}

/* float node::fCost() const
{
    return gCost + hCost;
} */

void node::addConnection(node* otherNode){
    connections[otherNode->id] = std::make_pair(otherNode, otherNode->health);
}

std::pair<node *, int> node::getNeighbor(std::string id)
{
    return connections[id];
}



#include "node.h"

node::node(ObjectStruct* _object) : object(*_object), gCost(0.0f), hCost(0.0f), parent(nullptr),id(_object->id)
{
}


float node::fCost() const
{
    return gCost + hCost;
}

void node::addConnection(node* otherNode){
    connections[otherNode->id] = std::make_pair(otherNode, otherNode->health);
  //  qDebug()<<otherNode->id;
}

std::pair<node *, int> node::getNeighbor(std::string id)
{
    return connections[id];
}



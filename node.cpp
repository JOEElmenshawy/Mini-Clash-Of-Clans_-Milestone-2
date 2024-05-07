#include "node.h"

node::node(ObjectStruct* _object) : object(_object), parent(nullptr),id(_object->id)
{
}




void node::addConnection(node* otherNode){
    connections[otherNode->id] = std::make_pair(otherNode, otherNode->object->costToPass);
   // qDebug()<<otherNode->id<<otherNode->object->name<<"cost to pass:"<< otherNode->object->costToPass;
}

std::pair<node *, int> node::getNeighbor(std::string id)
{
    return connections[id];
}



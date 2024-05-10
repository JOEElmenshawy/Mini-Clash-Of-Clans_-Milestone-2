#include "node.h"
#include "game.h"
extern Game* g;
node::node(ObjectStruct* _object) : object(_object), parent(nullptr),id(_object->id)
{
}




void node::addConnection(node* otherNode,int xofcastle,int yofcastle){qDebug()<<"reached the first";
     if((object->name=="fence"&&otherNode->object->name=="emptyland")) {
         if(sqrt(pow(object->x() - xofcastle, 2) + pow(object->y() - yofcastle, 2))>sqrt(pow(otherNode->object->x() - xofcastle, 2) + pow(otherNode->object->y() - yofcastle, 2)))
             connections[otherNode->id] = std::make_pair(otherNode, otherNode->object->costToPass);
         else
                 connections[otherNode->id] = std::make_pair(otherNode, object->costToPass);
     }
    else
    connections[otherNode->id] = std::make_pair(otherNode, otherNode->object->costToPass);

   // qDebug()<<otherNode->id<<otherNode->object->name<<"cost to pass:"<< otherNode->object->costToPass;
}

std::pair<node *, int> node::getNeighbor(std::string id)
{
    return connections[id];
}



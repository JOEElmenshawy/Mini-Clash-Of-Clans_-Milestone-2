#include "node.h"
#include "game.h"
extern Game* g;
node::node(UniqueNode* _object) : object(_object), parent(nullptr),id(_object->id)
{
}




void node::addConnection(node* otherNode){
     if((object->name=="fence"&&otherNode->object->name=="emptyland")) {
        if(otherNode->object->inner==true)
             Neighbours[otherNode->id] = std::make_pair(otherNode, otherNode->object->costToPass);
         else
                 Neighbours[otherNode->id] = std::make_pair(otherNode, object->costToPass);
     }
    else
    Neighbours[otherNode->id] = std::make_pair(otherNode, otherNode->object->costToPass);

   // qDebug()<<otherNode->id<<otherNode->object->name<<"cost to pass:"<< otherNode->object->costToPass;
}

std::pair<node *, int> node::getNeighbor(std::string id)
{
    return Neighbours[id];
}



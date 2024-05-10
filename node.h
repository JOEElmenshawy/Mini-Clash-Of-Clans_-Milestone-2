#ifndef NODE_H
#define NODE_H
#include<QGraphicsPixmapItem>
#include"objectstruct.h"
class node
{
public:
    node(ObjectStruct* _object);
    ObjectStruct* object;
    node* parent;
    int health;
    int x;
    int y;
    std::string id;
    std::map<std::string, std::pair<node*, int>> connections; // Store both the node and the weight
    void addConnection(node* node1,int xofcastle,int yofcastle);
    std::pair<node*, int> getNeighbor(std::string);


};

#endif // NODE_H

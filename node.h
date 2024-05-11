#ifndef NODE_H
#define NODE_H
#include<QGraphicsPixmapItem>
#include"UniqueNode.h"
class node
{
public:
    node(UniqueNode* _object);
    UniqueNode* object;
    node* parent;
    int health;
    std::string id;
    std::map<std::string, std::pair<node*, int>> Neighbours; // Store both the node and the weight
    void addConnection(node* node1);
    std::pair<node*, int> getNeighbor(std::string);


};

#endif // NODE_H

#ifndef CITIZENS_H
#define CITIZENS_H
#include<QGraphicsPixmapItem>
#include<QObject>
#include "castle.h"
#include "fence.h"
#include<QTimer>
#include "node.h"
class Citizens:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Citizens();
      std::vector<node*> dijkstra(node* start, node* end);
      std::vector<std::vector<node*>> creatNodes(std::vector<std::vector< ObjectStruct*>>& objects);
public slots:

    void move();
private:
    bool continuemove;
    bool shouldlookForFence;
    bool citizendied;
    int citizenRow;
    int citizenCol;
    int targetFenceRow;
    int targetFenceCol;
    void lookFence();
    std::vector<node*> path;
    QTimer* MoveTimer;
    int itr;
    std::vector<std::vector<node*>> nodes;
    node* currNode;
    float dX, dY;
    float distance;
};

#endif // CITIZENS_H

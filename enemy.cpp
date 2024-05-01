#include "enemy.h"
#include <cmath>
#include <QGraphicsScene>
#include"game.h"
#include <QTimer>
#include<iostream>

extern Game *g;
Enemy::Enemy()
{
    qDebug()<<"enemy constructed";
    enemydied=false;
    continuemove =true;
    health = 3;
    setPixmap(QPixmap(":/new/images/images/enemy.png").scaled(75, 75));

    int random_number = rand() %(1080);
    while((random_number>100&&random_number<980)||random_number>1080)
    {random_number=rand()%1080;}
    int random_number2= rand()%750;
    while((random_number2>70 &&random_number2<680)||random_number2>750)
    {
        random_number2= rand()%750;
    }
    setPos(random_number,random_number2);

   MoveTimer = new QTimer();
    connect(MoveTimer,&QTimer::timeout, this, [=](){
            move();
    });
    MoveTimer->start(200);

}
void Enemy::DecreaseHealth(){
    health--;
    if(health<=0)
    {
        Die();
    }
}

void Enemy::Die(){
    MoveTimer->stop();
        scene()->removeItem(this);
        qDebug()<<"enemy died";
        enemydied=true;
      //  delete this;
}
void Enemy::move()
{

        qDebug()<<"enemy is still moving";
    continuemove=true;
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Fence)) {
            Fence *fence = dynamic_cast<Fence*>(colliding_items[i]);
            if (fence) {
                // Call member functions specific to Fence
                fence->DecreaseHealth();
                continuemove = false;

            }
        }
    }
    QList<QGraphicsItem*> colliding_items2 = collidingItems();
    for (int i = 0, n = colliding_items2.size(); i < n; ++i) {
        if (typeid(*(colliding_items2[i])) == typeid(Castle)) {
            Castle *C = dynamic_cast<Castle*>(colliding_items2[i]);
            if (C) {
                // Call member functions specific to Fence
                C->DecreaseHealth();
                continuemove = false;
                qDebug()<<"castle touched";
            }
        }
    }
    if(continuemove){
        if(x()> g->getCastle()->x())
        {
            setPos(x()-5,y());
        }
        if(x() < g->getCastle()->x()){
            setPos(x()+5,y());
        }
        if(y() > g->getCastle()->y()){
            setPos(x(),y()-5);
        }
        if(y() < g->getCastle()->y()){
            setPos(x(),y()+5);
        }
    }
}
std::vector<std::vector<node *> > Enemy::creatNodes(std::vector<std::vector<ObjectStruct *> > &objects)
{
    int rows = objects.size();
    int cols = objects[0].size();

    std::vector<std::vector<node*>> nodes(rows, std::vector<node*>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            nodes[i][j] = new node(objects[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i > 0) nodes[i][j]->addConnection(nodes[i-1][j]); // Up
            if (i < rows - 1) nodes[i][j]->addConnection(nodes[i+1][j]); // Down
            if (j > 0) nodes[i][j]->addConnection(nodes[i][j-1]); // Left
            if (j < cols - 1) nodes[i][j]->addConnection(nodes[i][j+1]); // Right

            // Diagonal connections
            if (i > 0 && j > 0) nodes[i][j]->addConnection(nodes[i-1][j-1]); // Top-left
            if (i > 0 && j < cols - 1) nodes[i][j]->addConnection(nodes[i-1][j+1]); // Top-right
            if (i < rows - 1 && j > 0) nodes[i][j]->addConnection(nodes[i+1][j-1]); // Bottom-left
            if (i < rows - 1 && j < cols - 1) nodes[i][j]->addConnection(nodes[i+1][j+1]); // Bottom-right
        }
    }

    return nodes;
}

std::vector<node *> Enemy::dijkstra(node *start, node *end)
{
    if (start == nullptr || end == nullptr) {
        std::cout << "Error: start and end nodes must not be null" << std::endl;
        return std::vector<node*>();
    }

    std::vector<node*> openSet, closedSet;
    openSet.push_back(start);
    while (!openSet.empty()) {
        node* currentNode = *min_element(openSet.begin(), openSet.end(), [](node* lhs, node* rhs) {
            return lhs->gCost < rhs->gCost;
        });

        if (currentNode->object.id == end->object.id) {
            std::vector<node*> path;
            while (currentNode != nullptr) {
                path.push_back(currentNode);
                currentNode = currentNode->parent;
            }
            return path;
        }

        openSet.erase(remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
        closedSet.push_back(currentNode);

        for (auto& connection : currentNode->connections) {
            node* neighbor = connection.second.first;
            if (neighbor == nullptr) {
                std::cout << "Error: Connection contains null node" << std::endl;
                continue;
            }
            if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) continue;

            auto neighborPair = currentNode->getNeighbor(neighbor->object.id);
            if (neighborPair.first == nullptr) {
                std::cout << "Error: Neighbor not found in getNeighbor" << std::endl;
                continue;
            }
            float newMovementCostToNeighbor = currentNode->gCost + neighborPair.second;
            if (newMovementCostToNeighbor < neighbor->gCost || std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
                neighbor->gCost = newMovementCostToNeighbor;
                neighbor->parent = currentNode;

                if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) {
                    openSet.push_back(neighbor);
                }
            }
        }
    }

    std::cout << "No path to end node found" << std::endl;
    return std::vector<node*>();  // return an empty path if there's no path to the end
}

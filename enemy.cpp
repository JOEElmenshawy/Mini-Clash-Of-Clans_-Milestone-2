#include "enemy.h"
#include <cmath>
#include <QGraphicsScene>
#include"game.h"
#include <QTimer>
#include<iostream>

extern Game *g;
Enemy::Enemy(int d)
{
    damage=d;
    qDebug()<<"enemy constructed";
    enemydied=false;
    continuemove =true;
    health = 200;
    setPixmap(QPixmap(":/new/images/images/enemy.png").scaled(75, 75));

    int random_number = rand() %1125;

    int random_number2= rand()%750;

    if (rand()%2)
    {
        while (random_number2>20 &&random_number2<730)
            {
                random_number2= rand()%750;
            }
    }
    else
    {
        while(random_number>20&&random_number<1105)
        {
            random_number=rand()%1125;
        }
    }
    setPos(random_number,random_number2);
    enemyRow=y()/75;
    enemyCol=x()/75;
    qDebug()<<enemyRow<<" "<<enemyCol<<"\n";
   MoveTimer = new QTimer();
    connect(MoveTimer,&QTimer::timeout, this, [=](){
            move();
    });
  //  MoveTimer->start(200);
     nodes = creatNodes(g->objects);
    //printNodes();
   //  printConnections();
    node* start = nodes[enemyRow][enemyCol];
     node* end = nodes[g->getCastle()->castleRow][g->getCastle()->castleColumn];
      std::vector<node*> path = dijkstra(start, end);

    // for (auto it = path.rbegin(); it != path.rend(); it++) {
    //       qDebug() << (*it)->object.id << ": ";
    //   qDebug()  << "(" << (*it)->object.x() << ", " << (*it)->object.y() << ")" << "\n";
    // }
        qDebug()  << "\n";
    itr = path.size()-2;
    currNode = path[itr];

    distance = sqrt(pow(this->x() - currNode->object.x(), 2) + pow(this->y() - currNode->object.y(), 2));

    dX = 0;
     dY = 0;
    MoveTimer = new QTimer(this);
    connect( MoveTimer,&QTimer::timeout, this, [=](){

        distance = sqrt(pow(this->x() - currNode->object.x(), 2) + pow(this->y() - currNode->object.y(), 2));
        if(distance < 30)
        {
            if(itr != 0){
                itr--;
                currNode = path[itr];
            }
        }
        if(enemydied != true){
            move();
        }});
    MoveTimer->start(75);

}
void Enemy::printNodes() const {
    // Iterate over each row of nodes
    for (const auto& row : nodes) {
        // Iterate over each node in the row
        for (const auto& node_ptr : row) {
            // Print the coordinates of the node
            qDebug() << "Node: (" << node_ptr->object.x() << ", " << node_ptr->object.y() << ")";
        }
    }
}
void Enemy::printConnections() const {
    // Iterate over each row of nodes
    for (const auto& row : nodes) {
        // Iterate over each node in the row
        for (const auto& node_ptr : row) {
            // Print connections of the current node
            qDebug() << "Connections of Node (" << node_ptr->object.x() << ", " << node_ptr->object.y() << "):";

            // Iterate over each connection of the current node
            for (const auto& connection : node_ptr->connections) {
                // Print the coordinates of the connected node
                qDebug() << "  Connected Node: (" << connection.second.first->object.x() << ", " << connection.second.first->object.y() << ")";
            }
        }
    }
}
void Enemy::DecreaseHealth(int d){
    health-=d;
    if(health<=0)
    {
        Die();
    }
}

void Enemy::Die(){
    g->enemydestroyed++;
    MoveTimer->stop();
        scene()->removeItem(this);
        qDebug()<<"enemy died";
        enemydied=true;
      //  delete this;
}
void Enemy::move()
{    dX = (currNode->object.x() - this->x()) / distance;
    dY = (currNode->object.y() - this->y()) / distance;

    float newX = this->x() + 2*dX;
    float newY = this->y() + 2*dY;


    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (Fence* fenceItem = dynamic_cast<Fence*>(colliding_items[i])) {
            stepBack();
            fenceItem->DecreaseHealth(damage);
            return;
        }
        else if(Castle* castleItem = dynamic_cast<Castle*>(colliding_items[i])){

            stepBack();
            castleItem->DecreaseHealth(damage);
            return;
        }
    }

        setPos(newX, newY);

}

void Enemy::stepBack(){

    dX = (currNode->object.x() - this->x()) / distance;
    dY = (currNode->object.y() - this->y()) / distance;

    float newX = this->x() - 5*dX;
    float newY = this->y() - 5*dY;

    setPos(newX, newY);

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

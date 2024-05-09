#include "enemy.h"
#include <cmath>
#include <QGraphicsScene>
#include"game.h"
#include <QTimer>
#include <set>
#include<iostream>
#include <stack>
#include<QMediaPlayer>
#include<QAudioOutput>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include<queue>
extern Game *g;
extern int Volume;
Enemy::Enemy(int d)
{
    damage=d;
    qDebug()<<"enemy constructed";
    enemydied=false;
    continuemove =true;
    health = 200;
    setPixmap(QPixmap(":/new/images/images/enemy.png").scaled(45, 45));

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
   //   setPos(0,0);
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
  //   printConnections();
    node* start = nodes[enemyRow][enemyCol];
     node* end = nodes[g->getCastle()->castleRow][g->getCastle()->castleColumn];
     path = dijkstra(start, end);

    // for (auto it = path.rbegin(); it != path.rend(); it++) {
    //      qDebug() << (*it)->object->id << ": ";
    //     qDebug()  << "(" << (*it)->object->x() << ", " << (*it)->object->y() << ")" << "\n";
    // }
        qDebug()  << "\n";
    itr = path.size()-2;
    currNode = path[itr];

    distance = sqrt(pow(this->x() - currNode->object->x(), 2) + pow(this->y() - currNode->object->y(), 2));

    dX = 0;
     dY = 0;
    MoveTimer = new QTimer(this);
    connect( MoveTimer,&QTimer::timeout, this, [=](){

        distance = sqrt(pow(this->x() - currNode->object->x(), 2) + pow(this->y() - currNode->object->y(), 2));
        if(distance<50)
        {
            if(itr != 0){
                itr--;
                currNode = path[itr];
            }
        }
        if(enemydied != true){
           // qDebug()<<"current node:"<<currNode->object->name<<"id:"<<currNode->object->id;
            move();
        }});
    MoveTimer->start(100);

}
void Enemy::printNodes() const {
    // Iterate over each row of nodes
    for (const auto& row : nodes) {
        // Iterate over each node in the row
        for (const auto& node_ptr : row) {
            // Print the coordinates of the node
            qDebug() << "Node: (" << node_ptr->object->x() << ", " << node_ptr->object->y() << ")";
        }
    }
}
void Enemy::printConnections() const {
    // Iterate over each row of nodes
    for (const auto& row : nodes) {
        // Iterate over each node in the row
        for (const auto& node_ptr : row) {
            // Print connections of the current node
            qDebug() << "Connections of Node (" << node_ptr->object->x() << ", " << node_ptr->object->y() << "):";

            // Iterate over each connection of the current node
            for (const auto& connection : node_ptr->connections) {
                // Print the coordinates of the connected node
                qDebug() << "  Connected Node: (" << connection.second.first->object->x()/75 << ", " << connection.second.first->object->y()/75 << ")"<<"cost:"<<connection.second.second;
            }
        }
    }
}
void Enemy::DecreaseHealth(int d){
    health-=d;
    QMediaPlayer *Q = new QMediaPlayer;
    Q ->setSource(QUrl("qrc:/new/Sound/Sound/dead.mp3"));

    QAudioOutput *audio = new QAudioOutput;
    Q->setAudioOutput(audio);
    audio->setVolume(Volume);
    Q->play();
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
        delete this;
}
void Enemy::move()
{    dX = (currNode->object->x() - this->x()) / distance;
    dY = (currNode->object->y() - this->y()) / distance;

    float newX = this->x() + 2*dX;
    float newY = this->y() + 2*dY;

    bool passFence;
    if(currNode->object->name=="emptyland"&&path[itr+1]->object->name=="emptyland")
        passFence=true;

    continuemove=true;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (Fence* fenceItem = dynamic_cast<Fence*>(colliding_items[i])) {
            if(!passFence){
            fenceItem->DecreaseHealth(damage);
                continuemove=false;
         //   Die();
            }
        }
        else if(Castle* castleItem = dynamic_cast<Castle*>(colliding_items[i])){
            castleItem->DecreaseHealth(damage);
            continuemove=false;
        }
    }
    if(continuemove)
        setPos(newX, newY);
  //  setPos(currNode->object->x(),currNode->object->y());

}


Enemy::~Enemy()
{
    qDebug()<<"enemy destructed";
    delete MoveTimer;
    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes[i].size(); j++) {
            delete nodes[i][j];
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
            if (i > 0) nodes[i][j]->addConnection(nodes[i-1][j]); // upper neighbour
            if (i < rows - 1) nodes[i][j]->addConnection(nodes[i+1][j]); // Down neighbour
            if (j > 0) nodes[i][j]->addConnection(nodes[i][j-1]); // left neighbour
            if (j < cols - 1) nodes[i][j]->addConnection(nodes[i][j+1]); // right neighbour

            // Diagonal connections
            if (i > 0 && j > 0)
                nodes[i][j]->addConnection(nodes[i-1][j-1]); // top left neighbour
            if (i > 0 && j < cols - 1)
                nodes[i][j]->addConnection(nodes[i-1][j+1]); // top right neighbour
            if (i < rows - 1 && j > 0)
                nodes[i][j]->addConnection(nodes[i+1][j-1]); // bottom left neighbour
            if (i < rows - 1 && j < cols - 1)
                nodes[i][j]->addConnection(nodes[i+1][j+1]); // bottom right neighbour
        }
    }

    return nodes;
}
using namespace std;
std::vector<node*> Enemy::dijkstra(node* start, node* end) {
    std::vector<node*> path;
    std::unordered_map<node*, double> dist;
    std::unordered_map<node*, node*> prev;
    std::priority_queue<std::pair<double, node*>, std::vector<std::pair<double, node*>>, std::greater<std::pair<double, node*>>> pq;

    for (const auto& row : nodes) {
        for (const auto& node_ptr : row) {
            dist[node_ptr] = std::numeric_limits<double>::infinity();
            prev[node_ptr] = nullptr;
        }
    }

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        node* u = pq.top().second;
        pq.pop();

        if (u == end) {
            break;
        }

        for (const auto& connection : u->connections) {
            node* v = connection.second.first;
            double weight = connection.second.second;

            double alt = dist[u] + weight;

            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }

    node* current = end;
    while (current != nullptr) {
        path.push_back(current);
        current = prev[current];
    }
    for(auto iterator: dist)
    {
        if(iterator.second == std::numeric_limits<double>::infinity())
        {
          //  qDebug() << iterator.first->id << " has infinite distance";
        }
        else
        {
          //  qDebug() << iterator.first->id << " total dist=" << iterator.second;
        }
    }

    return path;
}

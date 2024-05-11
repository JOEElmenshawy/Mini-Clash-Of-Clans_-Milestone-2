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
    animationiterator=0;
    damage=d;
    qDebug()<<"enemy constructed";
    enemydied=false;
    continuemove =true;
    health = 200;
    setPixmap(QPixmap(":/dragon/images/dragon1.png").scaled(75, 75));

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
    //printNodes();
  //   printConnections();
    node* start = g->nodes[enemyRow][enemyCol];
    node* end = g->nodes[g->getCastle()->castleRow][g->getCastle()->castleColumn];
     path = DikestraAlgorithm(start, end);

    for (auto it = path.rbegin(); it != path.rend(); it++) {
         qDebug()<<(*it)->object->name << (*it)->object->id << ": ";
        qDebug()  << "(" << (*it)->object->x() << ", " << (*it)->object->y() << ")" << "\n";
    }
       qDebug()  << "\n";
    itr = path.size()-2;
    currNode = path[itr];

    distance = sqrt(pow(this->x() - currNode->object->x(), 2) + pow(this->y() - currNode->object->y(), 2));

    dX = 0;
     dY = 0;
    MoveTimer = new QTimer(this);
    connect( MoveTimer,&QTimer::timeout, this, [=](){

        distance = sqrt(pow(this->x() - currNode->object->x(), 2) + pow(this->y() - currNode->object->y(), 2));
        if(distance<30)
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
    MoveTimer->start((6-g->hardness)*10+50);

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
{
    if(animationiterator%4>1)
        setPixmap(QPixmap(":/dragon/images/dragon1.png").scaled(75, 75));

    else {
        setPixmap(QPixmap(":/dragon/images/dragon2.png").scaled(75, 75));
    }
    animationiterator++;    dX = (currNode->object->x() - this->x()) / distance;
    dY = (currNode->object->y() - this->y()) / distance;

    float newX = this->x() + 2*dX;
    float newY = this->y() + 2*dY;

    bool passFence=false;
    qDebug()<<currNode->object->name<<path[itr+1]->object->name;
    if((currNode->object->name=="emptyland"||currNode->object->name=="Castle")&&path[itr+1]->object->name=="emptyland")
    {
        passFence=true;

    }
      //  if(passFence)
      //      qDebug()<<"ill pass the fence";
      //  else
      //  qDebug()<<"ill not pass the fence";
    continuemove=true;
    bool fenceispartofpath=false;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (Fence* fenceItem = dynamic_cast<Fence*>(colliding_items[i])) {
            if(!passFence&&fenceItem->name=="fence"){
                for(auto ptr:path)
                {
                    if (ptr->object->x()==fenceItem->x()&&ptr->object->y()==fenceItem->y())
                        fenceispartofpath=true;
                }
                if(fenceispartofpath)
                {
                    fenceItem->DecreaseHealth(damage);
                    continuemove=false;
                }

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
}

using namespace std;
std::vector<node*> Enemy::DikestraAlgorithm(node* start, node* end) {
    std::vector<node*> path;
    std::unordered_map<node*, double> dist;
    std::unordered_map<node*, node*> prev;
    std::priority_queue<std::pair<double, node*>, std::vector<std::pair<double, node*>>, std::greater<std::pair<double, node*>>> pq;

    for (const auto& row :g-> nodes) {
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

        for (const auto& connection : u->Neighbours) {
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

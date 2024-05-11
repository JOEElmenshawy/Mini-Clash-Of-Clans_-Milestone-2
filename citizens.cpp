#include "citizens.h"
#include"fence.h"
#include"QTimer"
#include "enemy.h"
#include <queue>
#include "game.h"
extern Game* g;
Citizens::Citizens() {
    citizendied=false;
    shouldlookForFence=true;
    animationiterator=0;
    setPixmap(QPixmap(":/new/images/images/citizenWorker.png").scaled(80, 80));


    dX = 0;
    dY = 0;

    MoveTimer = new QTimer(this);
    connect( MoveTimer,&QTimer::timeout, this, [=](){
        if(!g->gameover){

        if (shouldlookForFence)
            {
                lookFence();
            }
        else{
 distance = sqrt(pow(this->x() - currNode->object->x(), 2) + pow(this->y() - currNode->object->y(), 2));
        if(distance<20)
        {
            if(itr != 0){
                itr--;
                currNode = path[itr];
            }
        }
        if(!citizendied){
            move();
        }}}});
    MoveTimer->start(50);
}

void Citizens::move()
{
    if(!g->gameover){
    if(animationiterator%4>1)
        setPixmap(QPixmap(":/citizen/images/citizen 1.png").scaled(80, 80));

            else {
              setPixmap(QPixmap(":/citizen/images/citizen2.png").scaled(80, 80));
        }
            animationiterator++;
    continuemove=true;
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
         Enemy *enemy = dynamic_cast<Enemy*>(colliding_items[i]);
            if (enemy) {
             MoveTimer->stop();
             citizendied=true;
             scene()->removeItem(this);
                delete this;
            }
        }
    }

    QList<QGraphicsItem *> colliding_items2 = collidingItems();
    for (int i = 0; i < colliding_items2.size(); ++i) {
        if (Fence* fenceItem = dynamic_cast<Fence*>(colliding_items[i])) {
            if(fenceItem->x()==targetFenceCol*75&&fenceItem->y()==targetFenceRow*75){
            fenceItem->increaseHealth();
                continuemove=false;// qDebug()<<"currentcostduringhealing"<<g->nodes[targetFenceRow][targetFenceCol]->object->costToPass;
 setPixmap(QPixmap(":/new/images/images/citizenWorker.png").scaled(80,80));
            }
            }
        }
    if(*g->nodes[targetFenceRow][targetFenceCol]->object->costToPass==60||*g->nodes[targetFenceRow][targetFenceCol]->object->costToPass==10){
        shouldlookForFence=true;  setPixmap(QPixmap(":/new/images/images/citizenWorker.png").scaled(80, 80));
        return;}
  //  qDebug()<<"cuurent node"<<currNode->id;
 //   if(!continuemove) qDebug()<<"i CANNOT MOVE";
    dX = (currNode->object->x() - this->x()) / distance;
    dY = (currNode->object->y() - this->y()) / distance;

    float newX = this->x() + 2*dX;
    float newY = this->y() + 2*dY;


    if(continuemove)
    {
        setPos(newX, newY);
    }
    }
}

void Citizens::lookFence()
{
    if(!g->gameover){    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            Enemy *enemy = dynamic_cast<Enemy*>(colliding_items[i]);
            if (enemy) {
                 MoveTimer->stop();
                citizendied=true;
                scene()->removeItem(this);
                delete this;
            }
        }
    }

    int min=6000;
    for (const auto& row : g->nodes) {
        for (const auto& node_ptr : row) {
            if(node_ptr->object->name=="fence")
            {
             //   qDebug()<<"wer are in a fence that has health:"<<node_ptr->object->costToPass;
                if (*node_ptr->object->costToPass<60&&*node_ptr->object->costToPass>10&&(sqrt(pow(this->x() -node_ptr->object->x(), 2) + pow(this->y() - node_ptr->object->y(), 2))<min))
                {
                  //  qDebug()<<"fence health:"<<node_ptr->object->costToPass;
                    min=sqrt(pow(this->x() -node_ptr->object->x(), 2) + pow(this->y() - node_ptr->object->y(), 2));
                    targetFenceRow= node_ptr->object->y()/75;
                     targetFenceCol= node_ptr->object->x()/75;
                    shouldlookForFence=false;

                }
            }
        }
    }
    if(!shouldlookForFence)
    {
        node* start = g->nodes[y()/75][x()/75];
        //  qDebug()<<"targetrow:"<<targetFenceRow<<"targetcol"<<targetFenceCol;
        node* end = g->nodes[targetFenceRow][targetFenceCol];
        path = dijkstra(start, end);
         // for (auto it = path.rbegin(); it != path.rend(); it++) {
         //      qDebug() << (*it)->object->id << ": ";
         //     qDebug()  << "(" << (*it)->object->x() << ", " << (*it)->object->y() << ")" << "\n";
         // }
        itr = path.size()-2;
        currNode = path[itr];
        distance = sqrt(pow(this->x() - currNode->object->x(), 2) + pow(this->y() - currNode->object->y(), 2));
      //  qDebug()<<"rached here without crash";
    }
    }
}

using namespace std;
std::vector<node*> Citizens::dijkstra(node* start, node* end) {
    std::vector<node*> path;
    std::unordered_map<node*, double> dist;
    std::unordered_map<node*, node*> prev;
    std::priority_queue<std::pair<double, node*>, std::vector<std::pair<double, node*>>, std::greater<std::pair<double, node*>>> pq;

    for (const auto& row : g->nodes) {
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
            double weight = *connection.second.second;

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

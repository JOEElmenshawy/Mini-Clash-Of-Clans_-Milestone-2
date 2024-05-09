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
    setPixmap(QPixmap(":/new/images/images/citizenWorker.png").scaled(40, 40));
     nodes = creatNodes(g->objects);


     qDebug()<<"reached here";
    dX = 0;
    dY = 0;

    MoveTimer = new QTimer(this);
    connect( MoveTimer,&QTimer::timeout, this, [=](){

        if (shouldlookForFence)
            {
                lookFence();
            }
        else{

        if(distance<50)
        {
            if(itr != 0){
                itr--;
                currNode = path[itr];
            }
        }
        if(!citizendied){
            move();
        }}});
    MoveTimer->start(100);
}

void Citizens::move()
{
    continuemove=true;
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
         Enemy *enemy = dynamic_cast<Enemy*>(colliding_items[i]);
            if (enemy) {
             citizendied=true;
             scene()->removeItem(this);
                delete this;
            }
        }
    }
    if(nodes[targetFenceRow][targetFenceCol]->object->costToPass==60||nodes[targetFenceRow][targetFenceCol]->object->costToPass==10){
        shouldlookForFence=true;
          continuemove=false;}
    QList<QGraphicsItem *> colliding_items2 = collidingItems();
    for (int i = 0; i < colliding_items2.size(); ++i) {
        if (Fence* fenceItem = dynamic_cast<Fence*>(colliding_items[i])) {
            if(fenceItem->x()==targetFenceCol*75&&fenceItem->y()==targetFenceRow*75){
            fenceItem->increaseHealth();
            continuemove=false; qDebug()<<"currentcostduringhealing"<<nodes[targetFenceRow][targetFenceCol]->object->costToPass;
            }
            }
        }

    dX = (currNode->object->x() - this->x()) / distance;
    dY = (currNode->object->y() - this->y()) / distance;

    float newX = this->x() + 2*dX;
    float newY = this->y() + 2*dY;


    if(continuemove)
    {
        setPos(newX, newY);
    }
}

void Citizens::lookFence()
{
    int min=60;
    for (const auto& row : nodes) {
        for (const auto& node_ptr : row) {
            if(node_ptr->object->name=="fence")
            {
             //   qDebug()<<"wer are in a fence that has health:"<<node_ptr->object->costToPass;
                if (node_ptr->object->costToPass<min&&node_ptr->object->costToPass>10)
                {
                    qDebug()<<"fence health:"<<node_ptr->object->costToPass;
                    min=node_ptr->object->costToPass;
                    targetFenceRow= node_ptr->object->y()/75;
                     targetFenceCol= node_ptr->object->x()/75;
                    shouldlookForFence=false;

                }
            }
        }
    }
    if(!shouldlookForFence)
    {
        node* start = nodes[y()/75][x()/75];
          qDebug()<<"targetrow:"<<targetFenceRow<<"targetcol"<<targetFenceCol;
        node* end = nodes[targetFenceRow][targetFenceCol];
        path = dijkstra(start, end);
         for (auto it = path.rbegin(); it != path.rend(); it++) {
              qDebug() << (*it)->object->id << ": ";
             qDebug()  << "(" << (*it)->object->x() << ", " << (*it)->object->y() << ")" << "\n";
         }
        itr = path.size()-2;
        currNode = path[itr];
        distance = sqrt(pow(this->x() - currNode->object->x(), 2) + pow(this->y() - currNode->object->y(), 2));
        qDebug()<<"rached here without crash";
    }
}
std::vector<std::vector<node *> > Citizens::creatNodes(std::vector<std::vector<ObjectStruct *> > &objects)
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
std::vector<node*> Citizens::dijkstra(node* start, node* end) {
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

#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsRectItem>
#include <QObject>
#include "castle.h"
#include "fence.h"
#include<QTimer>
#include "node.h"
class Enemy:public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy();
    void Die();
    void DecreaseHealth();
    std::vector<std::vector<node*>> creatNodes(std::vector<std::vector< ObjectStruct*>>& objects);
    void printNodes() const;
    void printConnections() const ;
    std::vector<node*> dijkstra(node* start, node* end);
    void stepBack();
private:
    int enemyRow;
    int enemyCol;
    bool continuemove;
    int health;
    bool enemydied;
    QTimer* MoveTimer;
    int itr;
    std::vector<std::vector<node*>> nodes;
     node* currNode;
    float dX, dY, Delta;
    float distance;
public slots:
    void move();

};

#endif // ENEMY_H

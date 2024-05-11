#ifndef UNIQUENODE_H
#define UNIQUENODE_H
#include <QPixmap>
#include <QString>
#include <QGraphicsPixmapItem>

class UniqueNode : public QGraphicsPixmapItem
{
public:
    std::string id;
    bool inner;
    QString name;
    int costToPass;
    UniqueNode();
    UniqueNode(const UniqueNode& other); // copy constructor
    ~UniqueNode();
};

#endif // UNIQUENODE_H

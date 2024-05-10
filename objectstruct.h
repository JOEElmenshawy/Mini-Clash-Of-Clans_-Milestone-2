#ifndef OBJECTSTRUCT_H
#define OBJECTSTRUCT_H
#include <QPixmap>
#include <QString>
#include <QGraphicsPixmapItem>

class ObjectStruct : public QGraphicsPixmapItem
{
public:
    std::string id;
    bool inner;
    QString name;
    int costToPass;
    ObjectStruct();
    ObjectStruct(const ObjectStruct& other); // copy constructor
    ~ObjectStruct();
};

#endif // OBJECTSTRUCT_H

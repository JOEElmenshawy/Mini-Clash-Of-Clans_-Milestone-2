#ifndef OBJECTSTRUCT_H
#define OBJECTSTRUCT_H
#include <QPixmap>
#include <QString>
#include <QGraphicsPixmapItem>

class ObjectStruct : public QGraphicsPixmapItem
{
public:
    float healthBar;
    int ID;
    std::string id;
    QString name;
public:
    ObjectStruct();
    ObjectStruct(const ObjectStruct& other); // copy constructor
    ~ObjectStruct();
    int getID();
};

#endif // OBJECTSTRUCT_H

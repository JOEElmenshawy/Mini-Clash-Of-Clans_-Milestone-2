#include "mainwindow.h"
#include"game.h"
#include <QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QBrush>
#include<QLabel>
#include<QFile>
#include<QTextStream>
#include<QGraphicsPixmapItem>//>
Game *g;
MainWindow *w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w= new MainWindow;
    QGraphicsView view;

    g= new Game;



    view.setWindowTitle("Game Project");
    QGraphicsScene scene;
    scene.setSceneRect(0,0,1200,1000);

    view.setFixedSize(1200,1000);
    view.setBackgroundBrush(QBrush(Qt::black));


    QGraphicsRectItem* rect = new QGraphicsRectItem();
    rect->setRect(0,0,1000,1200);
    scene.addItem(rect);
    view.setScene(&scene);



    w->show();
    return a.exec();
}

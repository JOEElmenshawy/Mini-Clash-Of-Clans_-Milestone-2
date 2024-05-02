#include <QApplication>
#include <iostream>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QBrush>
#include<QFile>
#include<QTextStream>
#include<QGraphicsPixmapItem>
#include "enemy.h"
#include <QTimer>
#include "game.h"
#include <QFont>
#include"bullet.h"
#include"mainwindow.h"
#include<QMessageBox>
#include "empty.h"
#include "wonlevel.h"
#include "lostwindow.h"
#include "citizens.h"
extern MainWindow *w;
Game::Game()
{   Iterator=0;
    NumberOfFences=0;
    view= new QGraphicsView;
    view->setWindowTitle("Game Project");
    scene=new QGraphicsScene;
    scene->setSceneRect(0,0,1125,750);
    objects.resize(10);
    for(int i = 0; i < 10; i++){
        objects[i].resize(15);
    }
    view->setFixedSize(1125,750);
    view->setBackgroundBrush(QBrush(QImage(":/new/images/images/background.png")));
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    QFile file(":/new/board/clandesign.txt");
    file.open(QIODevice::ReadOnly);
    int boarddata[10][15];
    QTextStream stream(&file);
    QString temp;
    for(int i=0;i<10;i++){
        for(int j=0;j<15;j++){
            stream>> temp;
            boarddata[i][j] = temp.toInt();
            if (temp.toInt()==3)
                NumberOfFences++;
        }
    }
    fence=new Fence*[NumberOfFences];
    QPixmap castlephoto (":/new/images/images/caslte.png");
    castlephoto=castlephoto.scaledToWidth(75);
    castlephoto=castlephoto.scaledToHeight(75);
    castle = new Castle();
    castle->setPixmap(castlephoto);

    QGraphicsPixmapItem boardimages[10][15];
    for(int i=0;i<10;i++){
        for(int j=0;j<15;j++){
            if(boarddata[i][j] == 0)
            {
                objects[i][j]=new empty();
                objects[i][j]->setPos(75*j,75*i);
               scene->addItem(objects[i][j]);
            }else if(boarddata[i][j] == 1)
            {
                objects[i][j]=castle;
                objects[i][j]->setPos(75*j,75*i);
                scene->addItem(objects[i][j]);
                castle->castleRow=i;
                castle->castleColumn=j;
            }
            else if (boarddata[i][j] == 2)
            {
                objects[i][j]= new Defense();
                objects[i][j]->setPos(75*j,75*i);
                scene->addItem(objects[i][j]);
            }
            else
            {
                objects[i][j]= new Fence();
                objects[i][j]->setPos(75*j,75*i);
                scene->addItem(objects[i][j]);
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            objects[i][j]->id =  "(" + std::to_string(i) + ", " + std::to_string(j) + ")";
        }
    }

    view->viewport()->installEventFilter(this);

Enemytimer = new QTimer();
QObject::connect(Enemytimer,SIGNAL(timeout()),this,SLOT(createEnemy()));
Enemytimer->start(2000);
CitizenTimer = new QTimer();
QObject::connect(  CitizenTimer,SIGNAL(timeout()),this,SLOT(createCitizens()));
CitizenTimer->start(50);

wintimer = new QTimer(this);

// Set a single-shot timer for 5 minutes
wintimer->setSingleShot(true);
wintimer->start(1 * 80* 1000); // 60 seconds in milliseconds

// Connect a slot to the timeout() signal of the timer
connect(wintimer, &QTimer::timeout, this, [=]()
        {
            scene->clear();
            view->hide();
            WonLevel* newlevel= new WonLevel;
            newlevel->show();
        });
}

void Game::createEnemy()
{
    Enemy* e= new Enemy();
    scene->addItem(e);
    qDebug()<<"create enemy called";
}
void Game::createCitizens()
{
    if(Iterator<5)
    {Citizens* c = new Citizens;
    scene->addItem(c);}
    Iterator++;
}
void Game::mousePressEvent(QMouseEvent *event)
{
    bullet* B = new bullet(event->pos().x(), event->pos().y());
    B->setPos(75*5,75*5);
    scene->addItem(B);
    qDebug() << event->pos().x();

}

bool Game::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            mousePressEvent(mouseEvent);
            return true; // Event handled
        }
    }
    return QObject::eventFilter(obj, event);
}

void Game::gameOver()
{
    scene->clear();
    wintimer->stop();
    LostWindow* l=new LostWindow;
   view->hide();
   l->show();
   qDebug()<<" game over";
   delete this;
}




void Game::showview()
{

    view->show();
}

Castle *Game::getCastle()
{
    return castle;
}

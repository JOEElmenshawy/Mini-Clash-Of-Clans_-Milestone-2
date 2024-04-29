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
#include "wonlevel.h"
#include "lostwindow.h"
extern MainWindow *w;
Game::Game()
{
    NumberOfFences=0;
    view= new QGraphicsView;
    view->setWindowTitle("Game Project");
    scene=new QGraphicsScene;
    scene->setSceneRect(0,0,1080,750);

    view->setFixedSize(1080,750);
    view->setBackgroundBrush(QBrush(QImage(":/new/images/images/background.png")));
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    QFile file(":/new/board/clandesign.txt");
    file.open(QIODevice::ReadOnly);
    int boarddata[10][12];
    QTextStream stream(&file);
    QString temp;
    for(int i=0;i<10;i++){
        for(int j=0;j<12;j++){
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
    QPixmap fencephoto (":/new/images/images/fence.png");
    fencephoto=fencephoto.scaledToWidth(75);
    fencephoto=fencephoto.scaledToHeight(75);
    QPixmap defencephoto (":/new/images/images/cannon.png");
    defencephoto=defencephoto.scaledToWidth(75);
    defencephoto=defencephoto.scaledToHeight(75);
    QPixmap grassphoto (":/new/images/images/grass.png");
    grassphoto=grassphoto.scaledToWidth(75);
    grassphoto=grassphoto.scaledToHeight(75);

    for(int i=0;i<NumberOfFences;i++)
    {
        fence[i] = new Fence;
        fence[i]->setPixmap(fencephoto);
    }
    castle = new Castle(fence,NumberOfFences);
    castle->setPixmap(castlephoto);
    defense = new Defense;
    defense->setPixmap(defencephoto);
    QGraphicsPixmapItem emptylands[120];
    for(int i=0;i<120;i++){
        emptylands[i].setPixmap(grassphoto);
    }
    int emptyiterator =0;
    int fenceiterator=0;
    QGraphicsPixmapItem boardimages[10][12];
    for(int i=0;i<10;i++){
        for(int j=0;j<12;j++){
            if(boarddata[i][j] == 0)
            {
                emptylands[emptyiterator].setPos(75*i,75*j);
                scene->addItem(&emptylands[emptyiterator]);
                emptyiterator++;
            }else if(boarddata[i][j] == 1)
            {
                castle->setPos(75*i,75*j);
                scene->addItem(castle);
            }
            else if (boarddata[i][j] == 2)
            {
                defense->setPos(75*i,75*j);
                scene->addItem(defense);
            }
            else
            {
                fence[fenceiterator]->setPos(75*i,75*j);
                scene->addItem(fence[fenceiterator]);
                fenceiterator++;
            }
        }
    }


    view->viewport()->installEventFilter(this);
wintimer = new QTimer(this);

// Set a single-shot timer for 5 minutes
wintimer->setSingleShot(true);
wintimer->start(1 * 60* 1000); // 60 seconds in milliseconds

// Connect a slot to the timeout() signal of the timer
connect(wintimer, &QTimer::timeout, this, [=]()
{
    wintimer->stop();
    view->hide();
    WonLevel* newlevel= new WonLevel;
    newlevel->show();
});

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

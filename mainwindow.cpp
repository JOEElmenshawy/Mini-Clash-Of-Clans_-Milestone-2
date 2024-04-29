#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include <QPushButton>
#include<QBrush>
#include<QFile>
#include<QTextStream>
#include<QGraphicsPixmapItem>
#include<QGraphicsRectItem>
#include "castle.h"
#include "enemy.h"
#include "defense.h"
#include "fence.h"
extern Game *g;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap p(":/new/images/images/MainMenue.jpg");
    ui->imagelabel->setPixmap(p);
    QPushButton *pushButton = new QPushButton("Start Game", ui->imagelabel);
    pushButton->setGeometry(QRect(100, 100, 100, 30));
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::clickStart);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickStart()
{
    g= new Game;
    this->hide();
    g->showview();
}

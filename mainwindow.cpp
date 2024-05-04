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
    p=p.scaled(ui->imagelabel->size());
    ui->imagelabel->setPixmap(p);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    g= new Game;
    this->hide();
    g->showview();
}


void MainWindow::on_pushButton_3_clicked()
{
    delete g;
    this->hide();
    delete this;
}


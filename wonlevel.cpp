#include "wonlevel.h"
#include "game.h"
#include "ui_wonlevel.h"
#include <QPushButton>
extern Game *g;
extern int* hard;
WonLevel::WonLevel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WonLevel)
{
    ui->setupUi(this);
    QPixmap p(":/new/images/images/NextLevel.png");
    p=p.scaled(ui->nextlevellabel->size());
    ui->nextlevellabel->setPixmap(p);

}

WonLevel::~WonLevel()
{
    delete ui;
}


void WonLevel::on_pushButton_clicked()
{
    delete g;
    *hard+=1;
    g=new Game(*hard);
    this->hide();
    g->showview();

}


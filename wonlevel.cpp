#include "wonlevel.h"
#include "game.h"
#include "ui_wonlevel.h"
#include <QPushButton>
extern Game *g;
WonLevel::WonLevel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WonLevel)
{
    ui->setupUi(this);
    QPixmap p(":/new/images/images/MainMenue.jpg");
    ui->nextlevellabel->setPixmap(p);
    QPushButton *pushButton = new QPushButton("Next Level", ui->nextlevellabel);
    pushButton->setGeometry(QRect(100, 100, 100, 30));
    connect(pushButton, &QPushButton::clicked, this, &WonLevel::nextLevel);
}

WonLevel::~WonLevel()
{
    delete ui;
}

void WonLevel::nextLevel()
{
    delete g;
    g=new Game();
    this->hide();
    g->showview();

}

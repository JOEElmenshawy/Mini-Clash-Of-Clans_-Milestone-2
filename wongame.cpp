#include "wongame.h"
#include "ui_wongame.h"
#include <mainwindow.h>
extern Game *g;
wongame::wongame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wongame)
{
    ui->setupUi(this);
    QPixmap p(":/new/images/images/You win.jpg");
    p=p.scaled(ui->returnmenulabel->size());
    ui->returnmenulabel->setPixmap(p);


}

wongame::~wongame()
{
    delete ui;
}

void wongame::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow;
    this->hide();
    w->show();
}


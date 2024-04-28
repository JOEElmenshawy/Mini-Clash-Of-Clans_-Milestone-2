#include "lostwindow.h"
#include "ui_lostwindow.h"
#include <QPushButton>
#include <mainwindow.h>
extern Game *g;
LostWindow::LostWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LostWindow)
{
    ui->setupUi(this);
    QPixmap p(":/new/images/images/MainMenue.jpg");
    ui->returnmenulabel->setPixmap(p);
    QPushButton *pushButton = new QPushButton("Return to main menu", ui->returnmenulabel);
    pushButton->setGeometry(QRect(100, 100, 100, 30));
    connect(pushButton, &QPushButton::clicked, this, &LostWindow::returnMainMenu);

}

LostWindow::~LostWindow()
{
    delete ui;

}

void LostWindow::returnMainMenu()
{
    MainWindow *w = new MainWindow;
    this->hide();
    w->show();
}



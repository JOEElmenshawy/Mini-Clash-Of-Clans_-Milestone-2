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
    QPixmap p(":/new/images/images/GameOver.png");
    p=p.scaled(ui->returnmenulabel->size());
    ui->returnmenulabel->setPixmap(p);
    QMediaPlayer *Q = new QMediaPlayer;
    Q ->setSource(QUrl("qrc:/new/Sound/Sound/GameOver.wav"));

    QAudioOutput *audio = new QAudioOutput;
    Q->setAudioOutput(audio);
    audio->setVolume(50);
    Q->play();


}

LostWindow::~LostWindow()
{
    delete ui;

}


void LostWindow::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow;
    this->hide();
    w->show();
}


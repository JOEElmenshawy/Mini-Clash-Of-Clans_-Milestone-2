#include "defense.h"
#include<QGraphicsSceneMouseEvent>
#include"game.h"
extern Game *g;
Defense::Defense() {
    costToPass=2000;
    name="cannon";
    QPixmap defencephoto (":/Defense Images/images/1.png");
    defencephoto=defencephoto.scaledToWidth(75);
    defencephoto=defencephoto.scaledToHeight(75);
    setPixmap(defencephoto);

    rotatingPictures.resize(12);


    for(int i = 0; i < 12; i++) {
        rotatingPictures[i].load(":/Defense Images/images/" + QString::number(i+1) + ".png");
    }

    /*for(int i = 0; i < 12; i++) {
        rotatingPictures[i] = rotating[i].scaled(100*level->ratioX, 100*level->ratioY);
    }*/

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, [=](){
        CurserPoint = QCursor::pos();
     float x1 = CurserPoint.x() - x();
        float y1 = y() - CurserPoint.y();
        Ratio = y1/x1;

        Animate();});
    timer->start(200);

}





void Defense::Animate(){
    if (Ratio <= 0.726 && Ratio > 0 && CurserPoint.y() < this->y()) {
        //std::cout << "1 tenth" << std::endl;
        setPixmap(rotatingPictures[10].scaled(75,75));
    } else if (Ratio <= 3.077 && Ratio > 0.726 && CurserPoint.y() < this->y()){
        setPixmap(rotatingPictures[9].scaled(75,75));
        //std::cout << "2 tenth" << std::endl;
    } /*else if (tan <= -3.077 && tan > 3.077 && point.y() < this->y()){
        setPixmap(rotating[7]);
        std::cout << "3 tenth" << std::endl;
    }*/ else if (Ratio <= -0.726 && Ratio > -3.077 && CurserPoint.y() < this->y()){
        setPixmap(rotatingPictures[6].scaled(75,75));
        //std::cout << "4 tenth" << std::endl;
    } else if (Ratio <=  0 && Ratio > -0.726 && CurserPoint.y() < this->y()){
        setPixmap(rotatingPictures[5].scaled(75,75));
        //std::cout << "5 tenth" << std::endl;
    } else if (Ratio <= 0.726 && Ratio > 0 && CurserPoint.y() > this->y()) {
        setPixmap(rotatingPictures[4].scaled(75,75));
        //std::cout << "6 tenth" << std::endl;
    } else if (Ratio <= 3.077 && Ratio > 0.726 && CurserPoint.y() > this->y()){
        setPixmap(rotatingPictures[4].scaled(75,75));
        //std::cout << "7 tenth" << std::endl;
    } /*else if (tan <= -3.077 && tan > 3.077 && point.y() > this->y()){
        setPixmap(rotating[2]);
        std::cout << "8 tenth" << std::endl;
    }*/ else if (Ratio <= -0.726 && Ratio > -3.077 && CurserPoint.y() > this->y()){
        setPixmap(rotatingPictures[0].scaled(75,75));
        //std::cout << "9 tenth" << std::endl;
    } else if (Ratio <=  0 && Ratio > -0.726 && CurserPoint.y() > this->y()){
        setPixmap(rotatingPictures[11].scaled(75,75));
        //std::cout << "10 tenth" << std::endl;
    } else{
        if(CurserPoint.y() < this->y()){
            setPixmap(rotatingPictures[7].scaled(75,75));
            //std::cout << "3 tenth" << std::endl;
        } else if(CurserPoint.y() > this->y()){
            setPixmap(rotatingPictures[2].scaled(75,75));
            //std::cout << "8 tenth" << std::endl;
        }
    }
}




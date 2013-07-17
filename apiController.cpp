#include "apiController.h"
#include <iostream>
#include <stdlib.h>
#include <QDebug>

ApiController::ApiController(QWidget *parent)
{
    this->test=7;
}

void ApiController::newWidget(int width, int height, QPoint pos,QLabel &virtualWidget){
    qWarning("add new Widget %dx%d at %d , %d",width,height,pos.rx(),pos.ry());
    this->test++;
    QString s = QString::number(this->test);
    virtualWidget.setText(s);
}

void ApiController::moveWidget(int id, QPoint pos){
    qWarning("move Widget %d at %d , %d",id,pos.rx(),pos.ry());

}

void ApiController::changeOpacity(int id, double opacity){
    qWarning("change opacity of Widget %d at %f",id,opacity);

}
void ApiController::changeSize(int id, int width, int height){
    qWarning("change Size of Widget %d to %dx%d",id,width,height);

}
void ApiController::changeUrl(int id, QString Url){
    qWarning("change Url of Widget %d to",id);

}

void ApiController::changeVisibility(int id,bool visible){
    qWarning("change visibility of Widget %d to %d",id,visible);

}

void ApiController::setFullScreen(int id ,bool fullscreen){

}
void ApiController::deleteWidget(int id){

}

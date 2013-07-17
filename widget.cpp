#include "widget.h"
#include <QLabel>
#include <QDebug>

Widget::Widget(QWidget *parent)
{
    QPixmap pixmap;
    this->setPixmap(pixmap);

}
void Widget::setPixmapToWidget(QPixmap tempPixmap){
    qWarning()<<"Set pixmap";
    qWarning()<<tempPixmap;
    qWarning()<<"----------";

//    this->setPixmap(tempPixmap);
}
QPixmap Widget::getPixmap(){
    qWarning()<<"Get pixmap";
    qWarning()<<*this->pixmap();
   return *this->pixmap();
}

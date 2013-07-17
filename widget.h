#ifndef WIDGET_H
#define WIDGET_H
#include <QLabel>
#include <QPixmap>
#include <QGraphicsOpacityEffect>
class Widget:public QLabel
{
public:
    Widget(QWidget *parent);
    void setPixmapToWidget(QPixmap tempPixmap);
    QPixmap getPixmap();
    int _posX;
    int _posY;
    bool _visibility;
    int _width;
    int _height;
    QString _urlHttp;
    double _opacity;
    QGraphicsEffect *_Effect;
    const QPixmap *_Pixmap;
    QGraphicsOpacityEffect *_opacityEffect;
};

#endif // WIDGET_H

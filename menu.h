#ifndef MENU_H
#define MENU_H

#include <QFrame>


QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Menu : public QFrame
{
public:
    explicit Menu(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void mousePressEvent(QMouseEvent *event);


    
};

#endif // MENU_H

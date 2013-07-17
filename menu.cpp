#include <QtWidgets>

#include "menu.h"

Menu::Menu(QWidget *parent)
    : QFrame(parent)
{
    setMinimumSize(100, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    QLabel *widgetIcon = new QLabel(this);
    widgetIcon->setScaledContents(true);
    widgetIcon->setPixmap(QPixmap(":/images/widget.png"));
    widgetIcon->move(10, 10);
    widgetIcon->show();
    widgetIcon->setAttribute(Qt::WA_DeleteOnClose);

    QLabel *webbrowserIcon = new QLabel(this);
    webbrowserIcon->setPixmap(QPixmap(":/images/webbrowser.png"));
    webbrowserIcon->move(10, 80);
    webbrowserIcon->show();
    webbrowserIcon->setAttribute(Qt::WA_DeleteOnClose);
}






void Menu::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream  << QPoint(event->pos() - child->pos());
    qWarning()<<QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());




    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}


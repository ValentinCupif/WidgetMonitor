
#include <QtWidgets>
#include <QLineEdit>
#include <QCheckBox>

#include "dragwidget.h"

DragWidget::DragWidget(QWidget *parent,int x, int y)
    : QFrame(parent)
{
    setMinimumSize(x, y);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    send = new QPushButton();
    connect(send, SIGNAL(pressed()), this , SLOT(updateDataWidget()));
    this->setStyleSheet("background-color:black;");
    this->_width=300;
    this->_height=600;
    offset = new QPoint(0,0);
    this->_opacity=1;
    this->nbWidget = 0;
    apiController =  new ApiController(0);



}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
        qWarning()<<"ignore dragEnterEvent";

    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{

    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            QPoint dest = (event->pos()-*offset);
            virtualWidget->move(dest.rx(),dest.ry());
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();

    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    QLabel *child = dynamic_cast<QLabel*>(childAt(event->pos()));




    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
        QPoint offset;
        dataStream >> offset;
        QPixmap pixmap;

        if (child){
            qWarning("Get Child");
            apiController->moveWidget(virtualWidget->text().toInt(),QPoint(event->pos()- offset));
        }/*else{
            this->nbWidget++;
            qWarning()<<this->nbWidget;
            apiController->newWidget(_width,_height,QPoint(event->pos()- offset));

        }*/


        if (child){
            qWarning("It have child");
            qWarning()<<child->text();
        }else{
            QLabel *newIcon = new QLabel(this);

            newIcon->resize(_width,_height);

            QPalette Pal(palette());
            Pal.setColor(QPalette::Background, Qt::black);
            newIcon->setPalette(Pal);
            newIcon->setStyleSheet("background-color:white;");
            newIcon->setPixmap(pixmap);
            newIcon->move(event->pos() - offset);
           // newIcon->setText(QString::number(this->nbWidget));
            apiController->newWidget(_width,_height,QPoint(event->pos()- offset),*newIcon);

            newIcon->show();
            newIcon->setAttribute(Qt::WA_DeleteOnClose);
        }

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        qWarning()<<"ignore drop event";
        event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{

    QLabel *child = dynamic_cast<QLabel*>(childAt(event->pos()));
    if (child){
        qWarning()<<"le texte est ";
        qWarning()<<child->text();
    }
    virtualTemp = child;
    if (!child)
        return;
    if (event->buttons() & Qt::RightButton ){
        confWidget(*child);
    }
    if (event->buttons() & Qt::LeftButton){
        _Effect = child->graphicsEffect();
        _posX = child->pos().rx();
        _posY = child->pos().ry();
        _Effect= child->graphicsEffect();
        _width= child->size().rwidth();
        _height = child->size().rheight();
        _Effect= child->graphicsEffect();


        QString id= child->text();
        *offset=event->pos()-child->pos();

        QPixmap *pixmap = new QPixmap();



        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream  << QPoint(event->pos() - child->pos());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(*pixmap);
        drag->setHotSpot(event->pos() - child->pos());

        QPixmap tempPixmap = *pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap->rect(), QColor(127, 127, 127, 127));
        painter.end();
        qWarning()<<"id";
        qWarning()<<id;


        child->setPixmap(tempPixmap);
        child->setText(id);

        qWarning()<<child->text();

        virtualWidget= child;
        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
         //   child->close();
        } else {

        //    child->show();
        //    child->setPixmap(*pixmap);
        }
    }
}


void DragWidget::confWidget(QLabel &child)
{
    virtualWidget = new QLabel();
    virtualWidget = &child;
    QWidget* popupWidget = new QWidget();
    popupWidget->resize(300,200);
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    QVBoxLayout *verticalLayout = new QVBoxLayout;

    QLabel *labelx = new QLabel();
    labelx->setText("Position X: ");
    horizontalLayout->addWidget(labelx);
    posX = new QLineEdit();
    horizontalLayout->addWidget(posX);
    verticalLayout->addLayout(horizontalLayout);

    QHBoxLayout *horizontalLayout2 = new QHBoxLayout;
    QLabel *labely = new QLabel();
    labely->setText("Position Y: ");
    horizontalLayout2->addWidget(labely);
    posY = new QLineEdit();
    horizontalLayout2->addWidget(posY);
    verticalLayout->addLayout(horizontalLayout2);

    QHBoxLayout *horizontalLayout3 = new QHBoxLayout;
    QLabel *labelVisibility = new QLabel();
    labelVisibility->setText("Hidden: ");
    horizontalLayout3->addWidget(labelVisibility);
    visibility = new QCheckBox();
    horizontalLayout3->addWidget(visibility);
    verticalLayout->addLayout(horizontalLayout3);

    QHBoxLayout *horizontalLayout4 = new QHBoxLayout;
    QLabel *labelWidth = new QLabel();
    labelWidth->setText("Width:        ");
    horizontalLayout4->addWidget(labelWidth);
    Height = new QLineEdit();

    Width = new QLineEdit();
    horizontalLayout4->addWidget(Width);
    verticalLayout->addLayout(horizontalLayout4);

    QHBoxLayout *horizontalLayout5 = new QHBoxLayout;
    QLabel *labelHeight = new QLabel();
    labelHeight->setText("Height:       ");
    horizontalLayout5->addWidget(labelHeight);
    horizontalLayout5->addWidget(Height);
    verticalLayout->addLayout(horizontalLayout5);

    QHBoxLayout *horizontalLayout6 = new QHBoxLayout;
    QLabel *labelUrl = new QLabel();
    labelUrl->setText("Url:               ");
    horizontalLayout6->addWidget(labelUrl);
    urlHttp = new QLineEdit();
    horizontalLayout6->addWidget(urlHttp);
    verticalLayout->addLayout(horizontalLayout6);

    QHBoxLayout *horizontalLayout7 = new QHBoxLayout;
    QLabel *labelOpacity = new QLabel();
    labelOpacity->setText("Opacity:     ");
    horizontalLayout7->addWidget(labelOpacity);
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(10,100);
    slider->setSliderPosition(100);
    horizontalLayout7->addWidget(slider);
    verticalLayout->addLayout(horizontalLayout7);

    QHBoxLayout *horizontalLayout8 = new QHBoxLayout;
    horizontalLayout8->addWidget(send);
    verticalLayout->addLayout(horizontalLayout8);

    popupWidget->setLayout(verticalLayout);
    popupWidget->setWindowTitle(QObject::tr("Widget Configuration"));
    popupWidget->show();
}

void DragWidget::updateDataWidget()
{

    qWarning()<<posX->text();
    if(!(posX->text().isEmpty()&&posY->text().isEmpty())){
        _posX=posX->text().toInt();
        _posY=posY->text().toInt();
        virtualWidget->move(_posX,_posY);
        apiController->moveWidget(virtualWidget->text().toInt(),QPoint(_posX,_posY));

    }
    if(visibility->isChecked())
    {
        virtualWidget->setStyleSheet("background-color:black;");
        apiController->changeVisibility(virtualWidget->text().toInt(),false);
    }else{
        virtualWidget->setStyleSheet("background-color:white;");
        apiController->changeVisibility(virtualWidget->text().toInt(),true);
    }
    if((Width->text().toInt()&&Height->text().toInt()) != 0){
        _width=Width->text().toInt();
        _height=Height->text().toInt();

        virtualWidget->resize(_width,_height);
        apiController->changeSize(virtualWidget->text().toInt(),_width,_height);
    }
    double value = slider->value();
    double value2 = value/100;
    double opacity=value2;
    QGraphicsOpacityEffect*	effect01  = new QGraphicsOpacityEffect();
    effect01->setOpacity(value2);
    virtualWidget->setGraphicsEffect(effect01);
    apiController->changeOpacity(virtualWidget->text().toInt(),value2);
    if(!urlHttp->text().isEmpty()){
        qWarning()<<urlHttp->text();
        apiController->changeUrl(virtualWidget->text().toInt(),urlHttp->text());
    }
}




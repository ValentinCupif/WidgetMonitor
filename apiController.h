#ifndef WIDGETCONFI_H
#define WIDGETCONFI_H
#include <QWidget>
#include <QLabel>
class ApiController : QWidget
{
public:
    ApiController(QWidget *parent);

    void newWidget(int width, int height, QPoint pos,QLabel &virtualWidget);
    void moveWidget(int id, QPoint pos);
    void changeOpacity(int id, double opacity);
    void changeSize(int id, int width, int height);
    void changeUrl(int id, QString Url);
    void changeVisibility(int id,bool visible);
    void setFullScreen(int id ,bool fullscreen);
    void deleteWidget(int id);
private:
    int test;

};

#endif // WIDGETCONFI_H

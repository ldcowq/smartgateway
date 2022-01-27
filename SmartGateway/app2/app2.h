#ifndef APP2_H
#define APP2_H
#include <QWidget>
#include<QPushButton>
#include <wiringPi.h>
#include <QThread>
#include"camera/monitorcateye.h"
#include"../album/album.h"
#include"../camera/camera.h"
#include"camera/cateye.h"
class App2 : public QWidget
{
    Q_OBJECT
public:
    explicit App2(QWidget *parent);
    QWidget *mainWidget;
    void resizeEvent(QResizeEvent *event);
    void layoutInit();
    QPushButton *albumPushButton;
    QPushButton *cameraPushButton;
    Album *album;
    //Camera *camera;
    Cateye *cateye=nullptr;
    QTimer *timer_Gpio_0;
signals:

public slots:
};

#endif // APP2_H

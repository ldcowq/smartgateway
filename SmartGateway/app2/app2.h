#ifndef APP2_H
#define APP2_H
#include <QWidget>
#include<QPushButton>
#include"../album/album.h"

#ifdef LINUX
//#include"../camera/camera.h"
#else
#include"../camera/camera.h"
#endif
class App2 : public QWidget
{
    Q_OBJECT
public:
    explicit App2(QWidget *parent = 0);

    QWidget *mainWidget;
    void resizeEvent(QResizeEvent *event);
    void layoutInit();
    QPushButton *albumPushButton;
    QPushButton *cameraPushButton;
    Album *album;
#ifdef LINUX
//Camera *camera;
#else
Camera *camera;
#endif
signals:

public slots:
};

#endif // APP2_H

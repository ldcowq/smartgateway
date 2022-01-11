#ifndef APP2_H
#define APP2_H
#include <QWidget>
#include<QPushButton>
#include"../album/album.h"
#include"../camera/camera.h"
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
    Camera *camera;
signals:

public slots:
};

#endif // APP2_H

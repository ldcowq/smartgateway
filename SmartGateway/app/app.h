#ifndef APP_H
#define APP_H
#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include <QEvent>
#include<QStringList>
#include<QTimer>
#include<QPixmap>
#include<QDebug>
#include<QPainter>
#include"../album/album.h"
#include"../video/video.h"
#include"../music/music.h"
#include"../environment/environment.h"
#include"../homecontrol/homecontrol.h"
class App : public QWidget
{
    Q_OBJECT
public:
    explicit App(QWidget *parent = 0);
    QWidget *mainWidget;
    void resizeEvent(QResizeEvent *event);
    void layoutInit();
    QPushButton *musicPushButton;
    QPushButton *environmentPushButton;
    QPushButton *videoPushButton;
    QPushButton *controlPushButton;
    QPushButton *monitorPushbutton;
    QLabel *albumLabel;
    bool eventFilter(QObject *obj, QEvent *e);
    Album *album;
    QStringList fileList;
    int imageCount=0;//图片数量
    int currentImageIndex=0;
    QTimer *imageTimer;

    Video *video;
    Music *music;
    Environment *environment;
    HomeControl *homeControl;
signals:
public slots:
};

#endif // APP_H

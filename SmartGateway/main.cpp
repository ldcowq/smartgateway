#pragma execution_character_set("utf-8")
#include "smartgateway.h"
#include "album/album.h"
#include "video/video.h"
#include "environment/environment.h"
#include "music/music.h"
#include "camera/camera.h"
#include "monitor/monitor.h"
#include "camera/cateye.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    a.setQuitOnLastWindowClosed(false);
    SmartGateway w;
    w.show();
    w.move(200,200);
//    Album album;
//    album.show();
//    Video video;
//    video.show();
//    Environment e;
//    e.show();
//    e.move(200,200);
//    Music music;
//    music.show();
//    Camera c;
//    c.show();
//    Monitor m;
//    m.show();
//    Cateye cateye;
//    cateye.show();
    return a.exec();
}

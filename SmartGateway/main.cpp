#pragma execution_character_set("utf-8")
#include "smartgateway.h"
#include "album/album.h"
#include "video/video.h"
#include "environment/environment.h"
#include "music/music.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setQuitOnLastWindowClosed(false);
//    SmartGateway w;
//    w.show();
//    w.move(200,200);
//    Album album;
//    album.show();
//    Video video;
//    video.show();
//    Environment e;
//    e.show();
      Music music;
      music.show();
    return a.exec();
}

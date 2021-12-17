#include "smartgateway.h"
#include "album/album.h"
#include "video/video.h"
#include "environment/environment.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setQuitOnLastWindowClosed(false);
    SmartGateway w;
    w.show();
//    Album album;
//    album.show();
//    Video video;
//    video.show();
//    Environment e;
//    e.show();
    w.move(200,200);
    return a.exec();
}

#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
//#include <QMediaPlayer>
//#include <QMediaPlaylist>
//#include <QVideoWidget>
//#include <QtMultimedia>
//#include <QtMultimediaWidgets>
#include <QStringList>
#include <QUrl>
#include <QProcess>
#include "tools/filetools.h"
class Video : public QWidget
{
    Q_OBJECT
public:
    explicit Video(QWidget *parent = 0);
    QWidget *mainWidget;
//    QMediaPlayer *mediaPlayer;
//    QMediaPlaylist *mediaPlayerList;
//    QVideoWidget *videoWidget;
    QListWidget *playList;
    QPushButton *playPushButton;
    QPushButton *exitPushButton;
    QPushButton *nextPushButton;
    QPushButton *lastPushButton;
    QStringList fileList;
    QProcess *myProcess;
    QString cmd;//播放器命令
    QListWidgetItem *currentItem;//当前播放的视频
    void layoutInit();
    int videoCount;
signals:

public slots:
};

#endif // VIDEO_H

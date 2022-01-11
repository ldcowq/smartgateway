#ifndef VIDEO_H
#define VIDEO_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QStringList>
#include <QUrl>
#include <QTimer>
#include <QProcess>
#include "tools/filetools.h"
#include "video/customslider.h"
class Video : public QWidget
{
    Q_OBJECT
public:
    explicit Video(QWidget *parent = 0);
    ~Video();
    QWidget *mainWidget;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *mediaPlayerList;
    QVideoWidget *videoWidget;
    QListWidget *playList;
    QPushButton *playPushButton;
    QPushButton *exitPushButton;
    QPushButton *nextPushButton;
    QPushButton *lastPushButton;
    CustomSlider *customSlider;
    QStringList fileList;
    QListWidgetItem *currentItem;//当前播放的视频
    void layoutInit();
    int videoCount;
    QTimer *sliderTimer;
    int maxValue = 1000;
signals:

public slots:
};

#endif // VIDEO_H

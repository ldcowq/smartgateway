#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "monitor/opencvdecode.h"
#include "video/video.h"
#include "album/album.h"
#include <QDebug>
#include <QPushButton>
#include <QImage>
#include <QLabel>
using namespace cv;
using namespace std;
class Monitor : public QWidget
{
    Q_OBJECT
public:
    explicit Monitor(QWidget *parent = nullptr);
    ~Monitor();

    void layoutInit();

    OpencvDecode *decodeThread;
    QLabel *lookVideoLable;
    QLabel *lookPhotoLable;
    QLabel *opencvShowQLabel;
    QPushButton *recordPushButton;
    QPushButton *printScreenPushButton;
    QPushButton *exitPushButton;

    bool isRecording = false;
    bool eventFilter(QObject * watched, QEvent * event);
    Video *videoWidget;
    Album *albumWidget;
    QPixmap PixmapToRound(QPixmap &src, int radius);
signals:
    void stopSubThread();
public slots:
};

#endif // MONITOR_H

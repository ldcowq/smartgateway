#ifndef CATEYE_H
#define CATEYE_H

#include <QWidget>
#include <QObject>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "monitor/opencvdecode.h"
#include "camera/monitorcateye.h"
#include "album/album.h"
#include <QDebug>
#include <QPixmap>
#include <QPushButton>
#include <QImage>
#include <QLabel>
#include <QCoreApplication>
class Cateye : public QWidget
{
    Q_OBJECT
public:
    explicit Cateye(QWidget *parent = nullptr);
    ~Cateye();

    void layoutInit();
    QLabel *opencvShowQLabel;
    QLabel *lookPhotoLable;
    QPushButton *takePhotoPushButton;
    QPushButton *exitPushButton;
    Album *albumWidget;
    bool isRecording = false;
    bool eventFilter(QObject * watched, QEvent * event);
    QThread *monitorCateyeThread;
    MonitorCateye *monitorCateye;
    QPixmap PixmapToRound(QPixmap &src, int radius);
signals:
};

#endif // CATEYE_H

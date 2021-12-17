#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QPushButton>
#include <QCamera>
#include<QDebug>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QImage>
#include <QLabel>
#include <QDateTime>
#include <QEvent>
#include"../album/album.h"
class Camera : public QWidget
{
    Q_OBJECT
public:
    explicit Camera(QWidget *parent = 0);
    void layoutInit();
    QPushButton *exitPushButton;
    QPushButton *takePhotoPushButton;
    QLabel *openAlbumLabel;

    QCamera *camera;//系统摄像头
    QCameraViewfinder *cameraViewFinder;//系统摄像头取景器
    QCameraImageCapture *cameraImageCapture;//截图部件
    int imageNum = 0;
    Album *album;

    bool eventFilter(QObject * watched, QEvent * event);
signals:

public slots:
};

#endif // CAMERA_H

#ifndef ALBUM_H
#define ALBUM_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDir>
#include <QPixmap>
#include "tools/filetools.h"
class Album : public QWidget
{
    Q_OBJECT
public:
    explicit Album(QString path);
    QPushButton *exitPushButton;
    QPushButton *lastPagePushButton;
    QPushButton *nextPagePushButton;
    QPushButton *zoomInPushButton;//放大
    QPushButton *zoomOutPushButton;//缩小
    QPushButton *rotateRightPushButton;//右转
    QPushButton *rotateLeftPushButton;//左转
    QLabel *showPic;
    QPixmap pixmap;
    QStringList fileList;
    void layoutInit();
    int imageCount = 0 ;
    int currentImageIndex = 0;//当前图片索引
    int lastPageIndex;//上一张图片索引
    int nextPageIndex;//下一张图片索引
    int rotateAngle = 0;
    float zoomValue = 1.0;
signals:

public slots:
};

#endif // ALBUM_H

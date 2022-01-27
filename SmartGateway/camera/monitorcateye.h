#ifndef MONITORCATEYE_H
#define MONITORCATEYE_H

#include <QObject>
#include <QThread>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QDebug>
#include <QImage>
#include <QDateTime>
#include <QCoreApplication>
#define cout qDebug() << "[" <<__FILE__ <<":"<<__FUNCTION__<<":"<<__LINE__ <<"]"
using namespace cv;
using namespace std;
class MonitorCateye : public QObject
{
    Q_OBJECT
public:
    explicit MonitorCateye(QObject *parent = nullptr);
    ~MonitorCateye();
    QImage MatToQimage(const Mat &mat);
    Mat currentFrame;
    VideoCapture videoCapture;
    VideoWriter videoWriter;
    bool isShowVideo = false;
protected:
    void run();
signals:
    void sendFrame(Mat mat);
public slots:
    void startMonitor();
};

#endif // MONITORCATEYE_H

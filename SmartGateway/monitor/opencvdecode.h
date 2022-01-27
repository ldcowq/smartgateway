#ifndef OPENCVDECODE_H
#define OPENCVDECODE_H

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
class OpencvDecode : public QThread
{
    Q_OBJECT
public:
    OpencvDecode(QObject *parent = nullptr);
    ~OpencvDecode();
    QImage MatToQimage(const Mat &mat);
    Mat currentFrame;
    VideoCapture videoCapture;
    VideoWriter videoWriter;
    bool isSave = false;
    QString path;
protected:
    void run();
signals:
    void sendFrameSig(Mat mat);
};

#endif // OPENCVDECODE_H

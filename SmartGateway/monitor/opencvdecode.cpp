#include "opencvdecode.h"

OpencvDecode::OpencvDecode(QObject *parent):QThread (parent)
{
    qRegisterMetaType<Mat>("Mat");
}

OpencvDecode::~OpencvDecode()
{
    this->wait();
}


void OpencvDecode::run()
{

    videoCapture.open("/dev/video0");
    if(!videoCapture.isOpened())
    {
        cout<<"open camera error!";
        return;
    }

    while (!isInterruptionRequested())
    {
        videoCapture>>currentFrame;
        //videoCapture.read(currentFrame);
        if(currentFrame.empty()) continue;
        emit sendFrameSig(currentFrame);
        if(isSave)
        {
            if(!videoWriter.isOpened())
            {
                videoWriter.open(path.toStdString(),VideoWriter::fourcc('X','V','I','D'), 20.0, Size(640, 480),true);
            }
            videoWriter.write(currentFrame);
        }
    }

    if(videoCapture.isOpened())
    {
        videoCapture.release();
    }
    if(videoWriter.isOpened())
    {
        videoWriter.release();
    }
}


QImage OpencvDecode::MatToQimage(const Mat &mat)
{

    //CV_8UC1 8位无符号的单通道---灰度图片
    if(mat.type() == CV_8UC1)
    {
        //使用给定的大小和格式构造图像
        //QImage(int width, int height, Format format)
        QImage qImage(mat.cols,mat.rows,QImage::Format_Indexed8);
        //扩展颜色表的颜色数目
        qImage.setColorCount(256);

        //在给定的索引设置颜色
        for(int i = 0; i < 256; i ++)
        {
            //得到一个黑白图
            qImage.setColor(i,qRgb(i,i,i));
        }
        //复制输入图像,data数据段的首地址
        uchar *pmat = mat.data;
        //
        for(int row = 0; row < mat.rows; row ++)
        {
            //遍历像素指针
            uchar *pDest = qImage.scanLine(row);
            //从源mat所指的内存地址的起始位置开始拷贝n个
            //字节到目标dest所指的内存地址的起始位置中
            memcmp(pDest,pmat,mat.cols);
            //图像层像素地址
            pmat += mat.step;
        }
        return qImage;
    }
    //为3通道的彩色图片
    else if(mat.type() == CV_8UC3)
    {
        //得到图像的的首地址
        const uchar *pmat = (const uchar*)mat.data;
        //以mat构造图片
        QImage qImage(pmat,mat.cols,mat.rows,mat.step,QImage::Format_RGB888);
        //在不改变实际图像数据的条件下，交换红蓝通道
        return qImage.rgbSwapped();
    }
    //四通道图片，带Alpha通道的RGB彩色图像
    else if(mat.type() == CV_8UC4)
    {
        const uchar *pmat = (const uchar*)mat.data;
        QImage qImage(pmat, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        //返回图像的子区域作为一个新图像
        return qImage.copy();
    }
    else
    {
        cout<<"ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

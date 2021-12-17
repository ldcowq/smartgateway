#include "camera.h"
#include <QDebug>
Camera::Camera(QWidget *parent) : QWidget(parent)
{
    layoutInit();
    this->move(200,200);
    camera=new QCamera();//系统摄像头
    cameraViewFinder=new QCameraViewfinder(this);//系统摄像头取景器
    cameraViewFinder->setGeometry(0,0,700,480);
    cameraViewFinder->show();
    cameraImageCapture= new QCameraImageCapture(camera); //截图部件
    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(cameraViewFinder);
    camera->start();
    FileTools::getFileAbsolutePath("D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/album/pictures",&imageNum);
    connect(exitPushButton,&QPushButton::clicked,this,[=](){
        camera->stop();
        delete camera;
        delete cameraImageCapture;
        this->close();
    });

    connect(takePhotoPushButton,&QPushButton::clicked,this,[=](){
        cameraImageCapture->capture();

    });

    connect(cameraImageCapture,&QCameraImageCapture::imageCaptured,this,[=](int id,QImage image){
//        qDebug()<<id;
//        QDateTime dateTime = QDateTime::currentDateTime();
//        QString photoName = dateTime.toString("yyyy-MM-dd-hh:m:ss");
        openAlbumLabel->setPixmap(QPixmap::fromImage(image));
        const QPixmap *pixmap = openAlbumLabel->pixmap();
        if(pixmap)
        {
            //qDebug()<<photoName<<endl;
            //pixmap->save("/mnt/sd/image/kk.jpg");
#ifdef LINUX
         pixmap->save("/home/ldc/daily/image/"+photoName+".jpg");
#else

         imageNum = imageNum +1;
         qDebug()<<imageNum<<endl;
         QString str = QString::number(imageNum);
         QString savePath = "D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/album/pictures/"+str+".jpg";
         qDebug()<<savePath<<endl;
         pixmap->save(savePath,0);
#endif
        }
    });




}

void Camera::layoutInit()
{
    this->setGeometry(0,0,800,480);
    this->setStyleSheet("background-color:rgb(0,0,0)");
    this->show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    exitPushButton = new QPushButton("退出",this);
    exitPushButton->setGeometry(715,40,70,50);
    exitPushButton->setStyleSheet("color:white;background-color:grey");
    exitPushButton->show();


    takePhotoPushButton= new QPushButton("拍照",this);
    takePhotoPushButton->setGeometry(715,200,70,50);
    takePhotoPushButton->setStyleSheet("color:white;background-color:grey");
    takePhotoPushButton->show();


    openAlbumLabel= new QLabel("相册",this);
    openAlbumLabel->setGeometry(705,340,90,90);
    openAlbumLabel->setStyleSheet("color:white;background-color:grey");
    openAlbumLabel->setScaledContents(true);
    openAlbumLabel->show();
    openAlbumLabel->installEventFilter(this);
}


/*　　　　　　　　　　　事件过滤　　　　　　　　　　　*/
bool Camera::eventFilter(QObject * watched, QEvent *event)
{
    if (watched == openAlbumLabel)
    {
        if ( event->type()== QEvent::MouseButtonPress)
        {
            album = new Album();
        }
    }
    return false;//处理完事件后，不需要事件继续传播
    //return SmartGateway::eventFilter(watched, event);//继续传播，如果注释上一行，程序不能运行
}

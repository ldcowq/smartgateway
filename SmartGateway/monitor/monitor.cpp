#include "monitor.h"
Monitor::Monitor(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0,0,800,480);
    this->show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    move(200,200);
    layoutInit();
    decodeThread = new OpencvDecode(this);
    decodeThread->start();


    //show the video
    connect(decodeThread,&OpencvDecode::sendFrameSig,this,[=](Mat mat){
        QImage image = decodeThread->MatToQimage(mat);
        opencvShowQLabel->setPixmap(QPixmap::fromImage(image));
    });

    //record the video
    connect(recordPushButton,&QPushButton::clicked,this,[=](){
        isRecording = !isRecording;
        if(isRecording)
        {
            //start to record
            decodeThread->path ="/home/pi/workdir/smgw_media/Monitor_videos/"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".avi";
            decodeThread->isSave = true;
            recordPushButton->setStyleSheet("QPushButton{border-image:url("":/monitor/monitorIcon/monitor_stop_record.png"")}");
        }else
        {
            //stop to record
            decodeThread->isSave = false;
            recordPushButton->setStyleSheet("QPushButton{border-image:url("":/monitor/monitorIcon/monitor_start_record.png"")}");
            QImage image = decodeThread->MatToQimage(decodeThread->currentFrame);
            QPixmap pixmap = QPixmap::fromImage(image);
            pixmap.scaled(lookVideoLable->size());
            pixmap = PixmapToRound(pixmap,25);
            lookVideoLable->setPixmap(pixmap);
        }
    });


    connect(printScreenPushButton,&QPushButton::clicked,this,[=](){
        QImage image = decodeThread->MatToQimage(decodeThread->currentFrame);
        image.save("/home/pi/workdir/smgw_media/Monitor_photos/"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".jpg");
        QPixmap pixmap = QPixmap::fromImage(image);
        pixmap.scaled(lookPhotoLable->size());
        pixmap = PixmapToRound(pixmap,25);
        lookPhotoLable->setPixmap(pixmap);
    });

    connect(exitPushButton,&QPushButton::clicked,this,[=](){
        decodeThread->requestInterruption();//stop sub thread
        decodeThread->quit();
        this->close();
    });
}

Monitor::~Monitor()
{
    decodeThread->requestInterruption();//stop sub thread
    decodeThread->quit();
    this->close();
}

void Monitor::layoutInit()
{
    this->setStyleSheet("background-color:black");

    opencvShowQLabel = new QLabel(this);
    opencvShowQLabel->setGeometry(0,0,640,480);
    opencvShowQLabel->setStyleSheet("color:black");
    opencvShowQLabel->show();

    lookVideoLable= new QLabel(this);
    lookVideoLable->setGeometry(690,30,64,64);
    lookVideoLable->setScaledContents(true);
    lookVideoLable->show();
    lookVideoLable->installEventFilter(this);
    lookVideoLable->setStyleSheet("QLabel{"
                                  "background-color:transparent;"
                                  "border-radius:30px;"
                                  "border:2px solid gray}");

    recordPushButton = new QPushButton(this);
    recordPushButton->setGeometry(690,120,64,64);
    recordPushButton->setStyleSheet("QPushButton{border-image:url("":/monitor/monitorIcon/monitor_start_record.png"")}");
    recordPushButton->show();

    printScreenPushButton = new QPushButton(this);
    printScreenPushButton->setGeometry(690,210,64,64);
    printScreenPushButton->show();
    printScreenPushButton->setStyleSheet("QPushButton{border-image:url("":/monitor/monitorIcon/monitor_printScreen.png"");}"
                                  "QPushButton:hover{border-image:url("":/monitor/monitorIcon/monitor_printScreen_hover.png"");}");

    exitPushButton = new QPushButton(this);
    exitPushButton->setGeometry(690,300,64,64);
    exitPushButton->show();
    exitPushButton->setStyleSheet("QPushButton{border-image:url("":/monitor/monitorIcon/monitor_exit.png"");}"
                                  "QPushButton:hover{border-image:url("":/monitor/monitorIcon/monitor_exit_hover.png"");}");

    lookPhotoLable= new QLabel(this);
    lookPhotoLable->setGeometry(690,390,64,64);
    lookPhotoLable->setStyleSheet("QLabel{"
                                  "background-color:transparent;"
                                  "border-radius:30px;"
                                  "border:2px solid gray}");
    lookPhotoLable->setScaledContents(true);
    lookPhotoLable->show();
    lookPhotoLable->installEventFilter(this);
}

/*　　　　　　　　　　　事件过滤　　　　　　　　　　　*/
bool Monitor::eventFilter(QObject * watched, QEvent *event)
{
    if (watched == lookVideoLable)
    {
        if ( event->type()== QEvent::MouseButtonPress)
        {
            videoWidget = new Video();
        }
    }else if (watched ==lookPhotoLable)
    {
        if ( event->type()== QEvent::MouseButtonPress)
        {
            albumWidget = new Album("/home/pi/workdir/smgw_media/Monitor_photos");
        }
    }
    return false;//处理完事件后，不需要事件继续传播
    //return SmartGateway::eventFilter(watched, event);//继续传播，如果注释上一行，程序不能运行
}

QPixmap Monitor::PixmapToRound(QPixmap &src, int radius)
{
    if (src.isNull()) {
        return QPixmap();
    }

    QSize size(2 * radius, 2 * radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}









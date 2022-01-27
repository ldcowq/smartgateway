#include "cateye.h"
#include <QPainter>
#include <QBitmap>
Cateye::Cateye(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0,0,800,480);
    this->show();
    //this->setAttribute(Qt::WA_DeleteOnClose,true);
    move(200,200);
    layoutInit();

    monitorCateyeThread = new QThread;
    monitorCateye = new MonitorCateye;
    monitorCateye->moveToThread(monitorCateyeThread);//对象移动到线程中
    monitorCateye->isShowVideo=false;
    monitorCateyeThread->start();//启动线程,需要通过信号触发getWeatherInfo
    connect(monitorCateyeThread, &QThread::finished, monitorCateyeThread, &QObject::deleteLater);
    connect(monitorCateyeThread,&QThread::started,monitorCateye,&MonitorCateye::startMonitor);

    //show the video
    connect(monitorCateye,&MonitorCateye::sendFrame,this,[=](Mat mat){
        QImage image = monitorCateye->MatToQimage(mat);
        opencvShowQLabel->setPixmap(QPixmap::fromImage(image));
    });

    connect(takePhotoPushButton,&QPushButton::clicked,this,[=](){
        QImage image = monitorCateye->MatToQimage(monitorCateye->currentFrame);
        image.save("/home/pi/workdir/smgw_media/Cateye_photos/"+QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".jpg");
        QPixmap pixmap = QPixmap::fromImage(image);
        pixmap.scaled(lookPhotoLable->size());
        pixmap = PixmapToRound(pixmap,25);
        lookPhotoLable->setPixmap(pixmap);
    });

    connect(exitPushButton,&QPushButton::clicked,this,[=](){
        //monitorCateye->isShowVideo=false;
        //monitorCateyeThread->exit();
        //delete monitorCateye;
        //monitorCateyeThread->wait();
        //this->close();
        monitorCateye->isShowVideo=false;
        this->hide();
    });
}

Cateye::~Cateye()
{
//    monitorCateye->isShowVideo=false;
//    monitorCateyeThread->exit();
//    delete monitorCateye;
//    monitorCateyeThread->wait();
//    this->close();
}

void Cateye::layoutInit()
{
    this->setStyleSheet("background-color:black");

    opencvShowQLabel = new QLabel(this);
    opencvShowQLabel->setGeometry(0,0,640,480);
    opencvShowQLabel->setStyleSheet("color:black");
    opencvShowQLabel->show();

    takePhotoPushButton = new QPushButton(this);
    takePhotoPushButton->setGeometry(690,210,64,64);
    takePhotoPushButton->show();
    takePhotoPushButton->setStyleSheet("QPushButton{border-image:url("":/monitor/monitorIcon/monitor_printScreen.png"");}"
                                  "QPushButton:hover{border-image:url("":/monitor/monitorIcon/monitor_printScreen_hover.png"");}");

    exitPushButton = new QPushButton(this);
    exitPushButton->setGeometry(690,300,64,64);
    exitPushButton->show();
    exitPushButton->setStyleSheet("QPushButton{border-image:url("":/monitor/monitorIcon/monitor_exit.png"");}"
                                  "QPushButton:hover{border-image:url("":/monitor/monitorIcon/monitor_exit_hover.png"");}");

    lookPhotoLable= new QLabel(this);
    lookPhotoLable->setGeometry(690,390,64,64);
    lookPhotoLable->setScaledContents(true);
    lookPhotoLable->show();
    lookPhotoLable->installEventFilter(this);
    lookPhotoLable->setStyleSheet("QLabel{"
                                  "background-color:transparent;"
                                  "border-radius:30px;"
                                  "border:2px solid gray}");
}

/*　　　　　　　　　　　事件过滤　　　　　　　　　　　*/
bool Cateye::eventFilter(QObject * watched, QEvent *event)
{
    if(watched ==lookPhotoLable)
    {
        if ( event->type()== QEvent::MouseButtonPress)
        {
            albumWidget = new Album("/home/pi/workdir/smgw_media/Cateye_photos/");
        }
    }
    return false;//处理完事件后，不需要事件继续传播
    //return SmartGateway::eventFilter(watched, event);//继续传播，如果注释上一行，程序不能运行
}

QPixmap Cateye::PixmapToRound(QPixmap &src, int radius)
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







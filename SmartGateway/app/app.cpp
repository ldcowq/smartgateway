#include "app.h"

App::App(QWidget *parent) : QWidget(parent)
{
    this->setParent(parent);
    this->setGeometry(230, 0, 570, 480);
    this->setFixedSize(570, 480);
    //this->setStyleSheet("background-color:grey");//设置滚动窗体背景,如果不设置就是整个smartgateway的背景
    layoutInit();
}
void App::layoutInit()
{
    mainWidget = new QWidget(this);
    environmentPushButton = new QPushButton("空气环境",this);
    environmentPushButton->setGeometry(0,20,230,130);
    environmentPushButton->setStyleSheet("border-image:url("":/app/image/environment.png"");border-radius:15px;text-align:bottom;color:white;font-size:20px;padding-bottom:10px;");
    environment = new Environment();
    environment->move(200,200);
    environment->hide();
    connect(environmentPushButton,&QPushButton::clicked,this,[=](){
        if(environment!=nullptr)
        {
            environment->show();
        }
    });

    controlPushButton= new QPushButton("家电控制",this);
    controlPushButton->setGeometry(240,20,150,130);
    controlPushButton->setStyleSheet("border-image:url("":/app/image/control.png"");border-radius:15px;text-align:bottom;color:white;font-size:20px;padding-bottom:10px;");
    connect(controlPushButton,&QPushButton::clicked,this,[=](){
       homeControl = new HomeControl();
    });

    monitorPushbutton=new QPushButton("视频监控",this);
    monitorPushbutton->setGeometry(400,20,150,130);
    monitorPushbutton->setStyleSheet("border-image:url("":/app/image/monitor.png"");border-radius:15px;text-align:bottom;color:white;font-size:20px;padding-bottom:10px;");
    connect(monitorPushbutton,&QPushButton::clicked,this,[=](){
       monitor = new Monitor();
    });

    musicPushButton = new QPushButton("音乐播放器",this);
    musicPushButton->setGeometry(400,300,150,155);
    musicPushButton->setStyleSheet("border-image:url("":/app/image/music.png"");border-radius:15px;text-align:bottom;color:white;font-size:20px;padding-bottom:13px;");
    connect(musicPushButton,&QPushButton::clicked,this,[=](){
       music = new Music();
    });


    videoPushButton= new QPushButton("视频播放器",this);
    videoPushButton->setGeometry(400,160,150,130);
    videoPushButton->setStyleSheet("border-image:url("":/app/image/video.png"");border-radius:15px;text-align:bottom;color:white;font-size:20px;padding-bottom:10px;");
    connect(videoPushButton,&QPushButton::clicked,this,[=](){
       video = new Video();
    });

    fileList = FileTools::getFileAbsolutePath("/home/pi/workdir/smgw_media/photos/",&imageCount);//获取制定目录下的所有图片绝对路径
    imageTimer = new QTimer(this);
    imageTimer->start(2000);
    albumLabel = new QLabel(this);
    albumLabel->setGeometry(0,160,390,295);
    albumLabel->setFixedSize(390,295);
    albumLabel->setStyleSheet("border:1px solid;border-color:white;background-color:black");
    albumLabel->installEventFilter(this);
    albumLabel->setContentsMargins(0,0,0,0);
    connect(imageTimer,&QTimer::timeout,this,[=](){//定时更换图片
        QPixmap pixmap(fileList.at(currentImageIndex));
        pixmap = pixmap.scaled(albumLabel->width(),albumLabel->height(),Qt::KeepAspectRatio);
        albumLabel->setPixmap(pixmap);
        if(currentImageIndex==(imageCount-1)) currentImageIndex = currentImageIndex-imageCount;
        currentImageIndex++;
    });
}

/*　　　　　　　　　　　事件过滤　　　　　　　　　　　*/
bool App::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == albumLabel)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            album = new Album("/home/pi/workdir/smgw_media/photos/");
        }
    }
    return false;//处理完事件后，不需要事件继续传播
}

void App::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    mainWidget->resize(this->size());
}

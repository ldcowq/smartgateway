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
        //environment = new Environment();
        if(environment!=nullptr)
        {
            environment->show();
        }
        qDebug()<<"environment 按下";
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

    //fileList = FileTools::getFileAbsolutePath("/mnt/sd/image/",&imageCount);//获取制定目录下的所有图片绝对路径
    //fileList = FileTools::getFileAbsolutePath("/home/ldc/daily/image/",&imageCount);//获取制定目录下的所有图片绝对路径
    fileList = FileTools::getFileAbsolutePath("D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/album/pictures",&imageCount);//获取制定目录下的所有图片绝对路径
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
        //albumLabel->setScaledContents(true);
        pixmap = pixmap.scaled(albumLabel->width(),albumLabel->height(),Qt::KeepAspectRatio);
//        qDebug()<<albumLabel->size()<<endl;
//        qDebug()<<pixmap.size()<<endl;
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
            album = new Album();
//            connect(album,&Album::destroyed,this,[=](){//当album对象销毁后，发送显示主菜单信号
//                emit showMenu();
//            });
        }
    }

    return false;//处理完事件后，不需要事件继续传播
}

void App::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    mainWidget->resize(this->size());
}
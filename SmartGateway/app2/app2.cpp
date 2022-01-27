#include "app2.h"
#include "camera/cateye.h"
#include <QTimer>

App2::App2(QWidget *parent) : QWidget(parent)
{
    this->setParent(parent);
    this->setGeometry(230, 0, 570, 480);
    this->setFixedSize(570, 480);
    //this->setStyleSheet("background-color:grey");//设置滚动窗体背景,如果不设置就是整个smartgateway的背景
    layoutInit();

    wiringPiSetup();
    pinMode(11,INPUT);
    timer_Gpio_0 = new QTimer();
    timer_Gpio_0->setInterval(500);
    timer_Gpio_0->start();
    connect(timer_Gpio_0,&QTimer::timeout,this,[=](){
        int ret = digitalRead(0);
        if(cateye->isHidden()&&ret==1)
        {
            cateye->monitorCateye->isShowVideo=true;
            cateye->show();
        }
    });
}

void App2::layoutInit()
{
    mainWidget = new QWidget(this);
    albumPushButton=new QPushButton("相册",this);
    albumPushButton->setGeometry(10,20,230,130);
    albumPushButton->setStyleSheet("border-image:url("":/app2/image/album.png"");border-radius:15px;text-align:bottom;color:white;font-size:20px;padding-bottom:10px;");
    connect(albumPushButton,&QPushButton::clicked,this,[=](){
        album = new Album("/home/pi/workdir/smgw_media/photos/");
    });

    cateye = new Cateye();
    cateye->hide();
    cateye->move(200,200);
    cameraPushButton= new QPushButton("相机",this);
    cameraPushButton->setGeometry(250,20,150,130);
    cameraPushButton->setStyleSheet("border-image:url("":/app2/image/camera.png"");border-radius:15px;text-align:bottom;color:white;font-size:20px;padding-bottom:10px;");
    connect(cameraPushButton,&QPushButton::clicked,this,[=](){
        cateye->monitorCateye->isShowVideo=true;
        cateye->show();
    });
}


void App2::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    mainWidget->resize(this->size());
}

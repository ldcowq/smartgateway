#include<QWidget>
#include<QThreadPool>
#include<iostream>
#include<QDebug>
#include<QTextCodec>
#include "smartgateway.h"
SmartGateway::SmartGateway(QWidget *parent): QWidget(parent)
{

    this->setParent(parent);
    this->setGeometry(0, 0, 800, 480);
    this->setFixedSize(800, 480);
    this->setStyleSheet("background-color:rgb(30,41,61)");
    layoutInit();//初始化界面
}
SmartGateway::~SmartGateway()
{

}

void SmartGateway::layoutInit()
{
    /******************界面时钟功能**********************/
    clock_timer=new QTimer(this);//创建一个定时器对象
    time_QLabel = new QLabel(this);//显示标签
    ampm_QLabel = new QLabel(this);//显示上下午标签
    line_QLabel = new QLabel(this);//显示横线的标签
    date_QLabel = new QLabel(this);//显示日期的标签
    connect(clock_timer,&QTimer::timeout,time_QLabel,[=](){//定时器发出timeout信号
        currentDateTime = QDateTime::currentDateTime();
        time_QLabel->setText(currentDateTime.toString("hh:mm"));
        ampm_QLabel->setText(currentDateTime.toString("A"));
        date_QLabel->setText(currentDateTime.toString("yyyy 年 MM 月 dd 日"));
    });

    time_QLabel->setGeometry(20,20,170,70);
    time_QLabel->setStyleSheet("font-size:58px;color:white");

    ampm_QLabel->setAlignment(Qt::AlignCenter);
    ampm_QLabel->setGeometry(170,50,40,40);
    ampm_QLabel->setStyleSheet("font-size:20px;color:white");

    line_QLabel->setAlignment(Qt::AlignCenter);
    line_QLabel->setGeometry(25,92,180,2);
    line_QLabel->setText("————————");
    line_QLabel->setStyleSheet("border: 2px solid;border-color:white;font-size:20px;color:white");

    date_QLabel->setAlignment(Qt::AlignCenter);
    date_QLabel->setGeometry(20,95,190,40);
    date_QLabel->setStyleSheet("font-size:20px;color:white");
    clock_timer->start(1000);//开启时钟定时

    /********************天气界面***********************/
    weather_cityName_QLabel = new QLabel("位置",this);//显示城市名称
    weather_cityName_QLabel->setGeometry(20,150,90,55);
    weather_cityName_QLabel->setAlignment(Qt::AlignCenter);
    //weather_cityName_QLabel->setStyleSheet("border: 1px solid;border-color:red;font-size:36px;color:white");
    weather_cityName_QLabel->setStyleSheet("font-size:36px;color:white");
    weather_cityName_QLabel->installEventFilter(this);//给控件安装事件过滤器,给标签增加点击功能

    weather_temperature_QLabel = new QLabel("℃",this);//显示城市天气温度
    weather_temperature_QLabel->setGeometry(20,200,90,55);
    weather_temperature_QLabel->setAlignment(Qt::AlignCenter);
    //weather_temperature_QLabel->setStyleSheet("border: 1px solid;border-color:red;font-size:36px;color:white");
    weather_temperature_QLabel->setStyleSheet("font-size:36px;color:white");
    weather_temperature_QLabel->installEventFilter(this);//给控件安装事件过滤器,给标签增加点击功能

    weather_image_QLabel = new QLabel(this);//显示天气状态图片
    weather_image_QLabel->setGeometry(120,140,80,80);
    weather_image_QLabel->setAlignment(Qt::AlignCenter);
    weather_image_QLabel->setStyleSheet("border-image:url("":/weather/image/refresh.png"")");
    //weather_image_QLabel->setStyleSheet("border: 1px solid;border-color:red;font-size:36px;color:white");
    weather_image_QLabel->installEventFilter(this);//给控件安装事件过滤器,给标签增加点击功能

    weather_imageName_QLabel = new QLabel("点击刷新",this);//显示天气状态文字
    weather_imageName_QLabel->setGeometry(125,220,70,30);
    weather_imageName_QLabel->setAlignment(Qt::AlignCenter);
    //weather_imageName_QLabel->setStyleSheet("border: 1px solid;border-color:red;font-size:12px;color:white");
    weather_imageName_QLabel->setStyleSheet("font-size:18px;color:white");
    weather_imageName_QLabel->installEventFilter(this);//给控件安装事件过滤器,给标签增加点击功能

    qDebug() << "SmartGateway: " << QThread::currentThread();
    QThread *weatherInfoThread = new QThread;//获取天气信息的子线程
    WeatherInfo *weatherInfo = new WeatherInfo;//创建天气信息对象
    weatherInfo->moveToThread(weatherInfoThread);//对象移动到线程中
    weatherInfoThread->start();//启动线程，但是不会执行获取天气函数，需要通过信号触发getWeatherInfo
    connect(weatherInfoThread, &QThread::finished, weatherInfoThread, &QObject::deleteLater);
    connect(weatherInfoThread,&QThread::started,weatherInfo,&WeatherInfo::getWeatherInfo);
    connect(weatherInfo,&WeatherInfo::updateWeather,this,[=](QString cityName,QString cityTemperture,QString weatherImagePath,QString weatherStatus){
        weather_cityName_QLabel->setText(cityName);
        weather_temperature_QLabel->setText(cityTemperture);
        weather_imageName_QLabel->setText(weatherStatus);
        weather_image_QLabel->setStyleSheet(weatherImagePath);
    });
    /**************************留言板界面********************************/
    messageBoard_Title = new QLabel("留　言　板",this);
    messageBoard_Title->setGeometry(10,260,210,30);
    messageBoard_Title->setAlignment(Qt::AlignCenter);
    messageBoard_Title->setStyleSheet("border: 1px solid;border-color:white;font-size:22px;color:white");

    messageBoard_content = new QLabel("点击开始留言！",this);
    messageBoard_content->setGeometry(10,290,210,180);
    messageBoard_content->setAlignment(Qt::AlignCenter);
    messageBoard_content->setStyleSheet("border: 1px solid;border-color:white;font-size:16px;color:white");
    messageBoard_content->installEventFilter(this);

    /**************************app界面****************************/
    appWidget = new QWidget(this);//右边主窗口
    appWidget->setGeometry(230,0,570,480);
    //appWidget->setStyleSheet("border:1px solid;border-color:red");

    mySlidePage = new SlidePage(appWidget);//创建滑动页面
    mySlidePage->resize(appWidget->size());//自适应右边窗口

    appPageOne = new App(appWidget);//创建第一个app页面
    appPageTwo = new App2(appWidget);//创建第二个app页面

    mySlidePage->addPage(appPageOne);//添加到滑动页面
    mySlidePage->addPage(appPageTwo);//添加到滑动页面
}


/**************************事件过滤******************************/
bool SmartGateway::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == weather_cityName_QLabel||watched == weather_temperature_QLabel||watched == weather_image_QLabel||watched == weather_imageName_QLabel)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            //getCityName();//单击获取最新的天气
        }
    }

    if(watched == messageBoard_content)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            messageBoard_content->setText("");
            //调用语音助手
        }
    }
    return false;//处理完事件后，不需要事件继续传播
    //return SmartGateway::eventFilter(watched, event);//继续传播，如果注释上一行，程序不能运行
}

void SmartGateway::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    mySlidePage->resize(appWidget->size());
}

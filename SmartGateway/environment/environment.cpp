#include "environment.h"
#include<ctime>


//double globalTemperature;
//double globalHumidity;
//double globalCarbon;
//double globalSmoke;
Environment::Environment(QWidget *parent) : QWidget(parent)
{
    layoutInit();//界面初始化
    this->setAttribute(Qt::WA_DeleteOnClose,false);//关闭界面，不释放资源
    qDebug() << "主线程对象的地址: " << QThread::currentThread();
    int count = 0;
    //创建子线程
    subThread= new QThread;

    // 千万不要指定给创建的任务对象指定父对象
    // 如果指定了: QObject::moveToThread: Cannot move objects with a parent
    getSensorDataBySerialTask = new GetSensorDataBySerial;

    //将任务对象移动到子线程中
    getSensorDataBySerialTask->moveToThread(subThread);
    //启动子线程
    subThread->start();
    connect(subThread, &QThread::started, getSensorDataBySerialTask, &GetSensorDataBySerial::working);//子线程开启后，自动执行working()函数
    connect(subThread,&QThread::finished,getSensorDataBySerialTask,&QObject::deleteLater);//释放getSensorDataBySerialTask对象空间
    connect(subThread,&QThread::finished,subThread,&QObject::deleteLater);//释放subThread对象空间
    connect(getSensorDataBySerialTask,&GetSensorDataBySerial::finished,subThread,&QThread::quit);
    connect(getSensorDataBySerialTask,&GetSensorDataBySerial::noSensorSignal,this,[=]()mutable{
        count++;
        if(this->isHidden()){
            //qDebug()<<"窗体已经隐藏！"<<endl;
            count = 0;
            return ;
        }else {
            if(count==1)
            {
                if(QMessageBox::information(this, "警告！", "没有检测到传感器设备！",QMessageBox::Yes, QMessageBox::Yes)==QMessageBox::Yes)
                {
                    this->hide();
                    count = 0;
                }
            }
        }
    });

    //修改温湿度曲线ui
    connect(getSensorDataBySerialTask,&GetSensorDataBySerial::updateSensorData,mainWidget,[=](int temperature,int humidity,int carbon,int smoke){
        temperature_Label->setText("温度:"+QString::number(temperature,'x',1)+"℃");
        humidity_Label->setText("湿度:"+QString::number(humidity,'x',1)+"%");
        carbon_Label->setText("烟雾浓度:"+QString::number(carbon,'x',1)+"%");
        smoke_Label->setText("一氧化碳:"+QString::number(smoke,'x',1)+"%");
        //设置温度曲线数据
        QList<QPointF> temperature_points;
        temperature_points.clear();
        temperature_ylist.append(temperature);
        int j = 0;
        if(temperature_ylist.length()>60)
        {
            temperature_ylist.removeFirst();
            for(int i=0;i<60;i++)
            {
                j=j+3;//每3秒更新一次数据，同步串口的发送时间
                temperature_points.append(QPointF(j,temperature_ylist.at(i)));
            }
        }else {
            for(int i=0;i<temperature_ylist.length();i++)
            {
                j=j+3;//每3秒更新一次数据，同步串口的发送时间
                temperature_points.append(QPointF(j,temperature_ylist.at(i)));
            }
        }
        //qDebug()<<temperature_points<<endl;
        temperature_Series->replace(temperature_points);


        //设置湿度曲线数据
        QList<QPointF> humidity_points;
        humidity_points.clear();
        humidity_ylist.append(humidity);
        j = 0;
        if(humidity_ylist.length()>60)
        {
            humidity_ylist.removeFirst();
            for(int i=0;i<60;i++)
            {
                j=j+3;//每3秒更新一次数据，同步串口的发送时间
                humidity_points.append(QPointF(j,humidity_ylist.at(i)));
            }
        }else {
            for(int i=0;i<humidity_ylist.length();i++)
            {
                j=j+3;//每3秒更新一次数据，同步串口的发送时间
                humidity_points.append(QPointF(j,humidity_ylist.at(i)));
            }
        }
        //qDebug()<<humidity_points<<endl;
        humidity_Series->replace(humidity_points);


        //设置一氧化碳浓度曲线数据
        QList<QPointF> carbon_points;
        carbon_points.clear();
        carbon_ylist.append(carbon);
        j = 0;
        if(carbon_ylist.length()>60)
        {
            carbon_ylist.removeFirst();
            for(int i=0;i<60;i++)
            {
                j=j+3;//每3秒更新一次数据，同步串口的发送时间
                carbon_points.append(QPointF(j,carbon_ylist.at(i)));
            }
        }else {
            for(int i=0;i<carbon_ylist.length();i++)
            {
                j=j+3;//每3秒更新一次数据，同步串口的发送时间
                carbon_points.append(QPointF(j,carbon_ylist.at(i)));
            }
        }
        //qDebug()<<carbon_points<<endl;
        carbon_Series->replace(carbon_points);


        //设置烟雾浓度曲线数据
        QList<QPointF> smoke_points;
        smoke_points.clear();
        smoke_ylist.append(smoke);
        j = 0;
        if(smoke_ylist.length()>60)
        {
            smoke_ylist.removeFirst();
            for(int i=0;i<60;i++)
            {
                j=j+3;//每3秒更新一次数据，同步串口的发送时间
                smoke_points.append(QPointF(j,smoke_ylist.at(i)));
            }
        }else {
            for(int i=0;i<smoke_ylist.length();i++)
            {
                j=j+3;//每3秒更新一次数据，同步串口的发送时间
                smoke_points.append(QPointF(j,smoke_ylist.at(i)));
            }
        }
        //qDebug()<<smoke_points<<endl;
        smoke_Series->replace(smoke_points);
    });
}




void Environment::layoutInit()
{
    this->setGeometry(0,0,800,480);
    this->show();
    this->setFixedSize(800,480);
    this->setAttribute(Qt::WA_DeleteOnClose,true);//关闭窗口同时释放空间，因为要后台运行获取数据，不能释放。
    //非窗口的部件是子部件，显示在它们的父部件中
    //this->setWindowFlags(Qt::Window);//设置窗口属性，否则子类不显示或者子类调用show方法

    mainWidget = new QWidget(this);
    mainWidget->setGeometry(0,0,800,480);
    mainWidget->show();
    mainWidget->setObjectName("environment");
    //mainWidget->setStyleSheet("#environment{border-image:url(/mnt/sd/image/4.jpg)}");


    exitPushButton= new QPushButton("返回",mainWidget);
    exitPushButton->setGeometry(0,0,50,30);
    exitPushButton->show();
    connect(exitPushButton,&QPushButton::clicked,mainWidget,[=](){
        this->hide();
    });

    /*******************实时数据设置************************/
    realTimeData_Label = new QLabel("实时数据",mainWidget);
    realTimeData_Label->setGeometry(20,40,120,40);
    realTimeData_Label->setStyleSheet("font: bold 30px;");
    realTimeData_Label->show();

    temperature_Label = new QLabel("温度: °C",mainWidget);
    temperature_Label->setGeometry(10,80,145,30);
    temperature_Label->setStyleSheet("font-size:20px");
    temperature_Label->show();

    humidity_Label= new QLabel("湿度: %",mainWidget);
    humidity_Label->setGeometry(10,120,145,30);
    humidity_Label->setStyleSheet("font-size:20px");
    humidity_Label->show();

    carbon_Label= new QLabel("烟雾浓度: %",mainWidget);
    carbon_Label->setGeometry(10,160,145,30);
    carbon_Label->setStyleSheet("font-size:20px");
    carbon_Label->show();

    smoke_Label= new QLabel("一氧化碳:  %",mainWidget);
    smoke_Label->setGeometry(10,200,145,30);
    smoke_Label->setStyleSheet("font-size:20px");
    smoke_Label->show();

    /***********************图表窗口设置**********************/

    //温度图表：
    temperature_chart = new QChart();// 构建图表对象
    temperature_chart->legend()->hide();//隐藏图列
    temperature_chart->setTitle("实时温度曲线");
    temperature_chart->setTheme(QChart::ChartThemeQt);//设置图表主题
    temperature_chart->setAnimationOptions(QChart::NoAnimation);//设置图表的动画效果

    temp_axisX = new QValueAxis();//创建x轴
    temp_axisY = new QValueAxis();//创建y轴
    temperature_chart->addAxis(temp_axisX,Qt::AlignBottom);//给图表添加x轴
    temperature_chart->addAxis(temp_axisY,Qt::AlignLeft);//给图表添加y轴

    temp_axisX->setRange(0,180);//设置x轴的范围
    temp_axisY->setRange(0,50);//设置y轴的范围



    temperature_Series = new QSplineSeries();// 构建曲线系列对象
    temperature_chart->addSeries(temperature_Series);//图表添加曲线系列
    temperature_Series->attachAxis(temp_axisX);//曲线关联x轴
    temperature_Series->attachAxis(temp_axisY);//曲线关联y轴

    temperature_chartView = new QChartView(temperature_chart,mainWidget);//构建图表显示视图
    temperature_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    temperature_chartView->setGeometry(160,0,315,240);
    temperature_chartView->show();

    //湿度图表：
    humidity_chart = new QChart();// 构建图表对象
    humidity_chart->legend()->hide();//隐藏图列
    humidity_chart->setTitle("实时湿度曲线");
    humidity_chart->setAnimationOptions(QChart::NoAnimation);//设置图表的动画效果

    humi_axisX = new QValueAxis();//创建x轴
    humi_axisY = new QValueAxis();//创建y轴
    humidity_chart->addAxis(humi_axisX,Qt::AlignBottom);//给图表添加x轴
    humidity_chart->addAxis(humi_axisY,Qt::AlignLeft);//给图表添加y轴

    humi_axisX->setRange(0,180);//设置x轴的范围
    humi_axisY->setRange(0,100);//设置y轴的范围

    humidity_Series = new QSplineSeries();// 构建曲线系列对象
    humidity_chart->addSeries(humidity_Series);//图表添加曲线系列
    humidity_Series->attachAxis(humi_axisX);//曲线关联x轴
    humidity_Series->attachAxis(humi_axisY);//曲线关联y轴

    humidity_chartView = new QChartView(humidity_chart,mainWidget);//构建图表显示视图
    humidity_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    humidity_chartView->setGeometry(480,0,315,240);
    humidity_chartView->show();

    //一氧化碳图表：
    carbon_chart = new QChart();// 构建图表对象
    carbon_chart->legend()->hide();//隐藏图列
    carbon_chart->setTitle("实时一氧化碳浓度曲线");
    carbon_chart->setAnimationOptions(QChart::NoAnimation);//设置图表的动画效果

    carbon_axisX = new QValueAxis();//创建x轴
    carbon_axisY = new QValueAxis();//创建y轴
    carbon_chart->addAxis(carbon_axisX,Qt::AlignBottom);//给图表添加x轴
    carbon_chart->addAxis(carbon_axisY,Qt::AlignLeft);//给图表添加y轴

    carbon_axisX->setRange(0,180);//设置x轴的范围
    carbon_axisY->setRange(0,100);//设置y轴的范围

    carbon_Series = new QSplineSeries();// 构建曲线系列对象
    carbon_chart->addSeries(carbon_Series);//图表添加曲线系列
    carbon_Series->attachAxis(carbon_axisX);//曲线关联x轴
    carbon_Series->attachAxis(carbon_axisY);//曲线关联y轴

    carbon_chartView = new QChartView(carbon_chart,mainWidget);//构建图表显示视图
    carbon_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    carbon_chartView->setGeometry(160,240,315,240);
    carbon_chartView->show();

    //烟雾浓度图表：
    smoke_chart = new QChart();// 构建图表对象
    smoke_chart->legend()->hide();//隐藏图列
    smoke_chart->setTitle("实时烟雾浓度曲线");
    smoke_chart->setAnimationOptions(QChart::NoAnimation);//设置图表的动画效果

    smoke_axisX = new QValueAxis();//创建x轴
    smoke_axisY = new QValueAxis();//创建y轴
    smoke_chart->addAxis(smoke_axisX,Qt::AlignBottom);//给图表添加x轴
    smoke_chart->addAxis(smoke_axisY,Qt::AlignLeft);//给图表添加y轴

    smoke_axisX->setRange(0,180);//设置x轴的范围
    smoke_axisY->setRange(0,100);//设置y轴的范围

    smoke_Series = new QSplineSeries();// 构建曲线系列对象
    smoke_chart->addSeries(smoke_Series);//图表添加曲线系列
    smoke_Series->attachAxis(smoke_axisX);//曲线关联x轴
    smoke_Series->attachAxis(smoke_axisY);//曲线关联y轴

    smoke_chartView = new QChartView(smoke_chart,mainWidget);//构建图表显示视图
    smoke_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    smoke_chartView->setGeometry(480,240,315,240);
    smoke_chartView->show();

}

#include "environment.h"
#include<ctime>

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

    connect(this,&Environment::livingRoomLight,getSensorDataBySerialTask,&GetSensorDataBySerial::onLivingRoomLight);
    connect(this,&Environment::livingRoomBeep,getSensorDataBySerialTask,&GetSensorDataBySerial::onLivingRoomBeep);
    connect(this,&Environment::kitchenLight,getSensorDataBySerialTask,&GetSensorDataBySerial::onkitchenLight);
    connect(this,&Environment::kitchenFan,getSensorDataBySerialTask,&GetSensorDataBySerial::onkitchenFan);

    connect(getSensorDataBySerialTask,&GetSensorDataBySerial::sendLivingRoomHeartBeat,this,[=](int deviceId,int state){
        if(state==1)
        {
            livingRoomLight_Label->setText("节点1       在线/");
            livingRoomBeep_Label->setText("节点1       在线/");
            livingRoomLight_PushButton->setEnabled(true);
            livingRoomBeep_PushButton->setEnabled(true);
        }else if (state==0) {
            livingRoomLight_Label->setText("节点1       离线/");
            livingRoomBeep_Label->setText("节点1       离线/");
            livingRoomLight_PushButton->setEnabled(false);
            livingRoomBeep_PushButton->setEnabled(false);
        }
    });

    connect(getSensorDataBySerialTask,&GetSensorDataBySerial::sendKitchenHeartBeat,this,[=](int deviceId,int state){
        if(state==1)
        {
            kitchenLight_Label->setText("节点2       在线/");
            kitchenFan_Label->setText("节点2       在线/");
            kitchenLight_PushButton->setEnabled(true);
            kitchenFan_PushButton->setEnabled(true);
        }else if (state==0) {
            kitchenLight_Label->setText("节点2       离线/");
            kitchenFan_Label->setText("节点2       离线/");
            kitchenLight_PushButton->setEnabled(false);
            kitchenFan_PushButton->setEnabled(false);
        }
    });

    connect(getSensorDataBySerialTask,&GetSensorDataBySerial::updateDht11Data,mainWidget,[=](int temperature,int humidity){
        if(temperature>100||temperature<0||humidity>100||humidity<0) return;
        temperature_Label->setText("温度: "+QString::number(temperature,'x',1)+"℃");
        humidity_Label->setText("湿度: "+QString::number(humidity,'x',1)+"%");
        //设置曲线数据
        humidity_points.clear();
        temperature_points.clear();
        temperature_ylist.append(temperature);
        humidity_ylist.append(humidity);
        int j = 0;
        if(temperature_ylist.length()>60)temperature_ylist.removeFirst();
        if(humidity_ylist.length()>60)humidity_ylist.removeFirst();

        for(int i=0;i<temperature_ylist.length();i++)
        {
            temperature_points.append(QPointF(j,temperature_ylist.at(i)));
            humidity_points.append(QPointF(j,humidity_ylist.at(i)));
            j=j+3;//每3秒更新一次数据，同步串口的发送时间
        }
        temperature_Series->replace(temperature_points);
        humidity_Series->replace(humidity_points);
    });

    connect(getSensorDataBySerialTask,&GetSensorDataBySerial::updateMqData,mainWidget,[=](int carbon,int smoke){
        if(carbon>100||carbon<0||smoke>100||smoke<0) return;
        carbon_Label->setText("烟雾浓度: "+QString::number(carbon,'x',1)+"%");
        smoke_Label->setText("一氧化碳: "+QString::number(smoke,'x',1)+"%");

        //设置曲线数据
        carbon_points.clear();
        smoke_points.clear();
        carbon_ylist.append(carbon);
        smoke_ylist.append(smoke);
        int j = 0;
        if(carbon_ylist.length()>60)carbon_ylist.removeFirst();
        if(smoke_ylist.length()>60)smoke_ylist.removeFirst();

        for(int i=0;i<carbon_ylist.length();i++)
        {
            carbon_points.append(QPointF(j,carbon_ylist.at(i)));
            smoke_points.append(QPointF(j,smoke_ylist.at(i)));
            j=j+3;//每3秒更新一次数据，同步串口的发送时间
        }
        carbon_Series->replace(carbon_points);
        smoke_Series->replace(smoke_points);
    });
}


void Environment::layoutInit()
{
    this->setGeometry(0,0,800,480);
    this->show();
    this->setFixedSize(800,480);
    //非窗口的部件是子部件，显示在它们的父部件中
    //this->setWindowFlags(Qt::Window);//设置窗口属性，否则子类不显示或者子类调用show方法

    mainWidget = new QWidget(this);
    mainWidget->setGeometry(0,0,800,480);
    mainWidget->show();
    mainWidget->setObjectName("environment");
    //mainWidget->setStyleSheet("#environment{border-image:url(/mnt/sd/image/4.jpg)}");

    livingRoomLight_Widget = new QWidget(mainWidget);
    livingRoomLight_Widget->show();
    livingRoomLight_Widget->setGeometry(0,0,144,140);
    livingRoomLight_Widget->setWindowFlag(Qt::FramelessWindowHint);
    livingRoomLight_Widget->setStyleSheet("QWidget{background-color:#999999;border-bottom-right-radius:25px}");
    livingRoomLight_PushButton= new QPushButton(livingRoomLight_Widget);
    livingRoomLight_PushButton->setGeometry(15,10,110,110);
    livingRoomLight_PushButton->show();
    livingRoomLight_PushButton->setEnabled(false);
    livingRoomLight_PushButton->setFocusPolicy(Qt::NoFocus);
    livingRoomLight_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/livingroom_light_close.png"")};");
    connect(livingRoomLight_PushButton,&QPushButton::clicked,mainWidget,[=](){
        livingRoomLight_PressFlag = !livingRoomLight_PressFlag;
        if(livingRoomLight_PressFlag)
        {
            livingRoomLight_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/livingroom_light_open.png"")};");
            emit livingRoomLight("111");
            //livingRoomLightStatus_Label->setStyleSheet("color:red");
            livingRoomLightStatus_Label->setText("打开");
        }else{
            livingRoomLight_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/livingroom_light_close.png"")};");
            emit livingRoomLight("110");
            //livingRoomLightStatus_Label->setStyleSheet("color:white");
            livingRoomLightStatus_Label->setText("关闭");
        }
    });
    livingRoomLight_Label = new QLabel("节点1       离线/",livingRoomLight_Widget);
    livingRoomLight_Label->setGeometry(5,115,120,20);
    livingRoomLight_Label->show();
    livingRoomLight_Label->setStyleSheet("font-size:14px;color:white");
    livingRoomLightStatus_Label = new QLabel("关闭",livingRoomLight_Widget);
    livingRoomLightStatus_Label->setGeometry(97,115,35,20);
    livingRoomLightStatus_Label->show();
    livingRoomLightStatus_Label->setStyleSheet("font-size:14px;color:white");


    livingRoomBeepWidget = new QWidget(mainWidget);
    livingRoomBeepWidget->show();
    livingRoomBeepWidget->setGeometry(164,0,144,140);
    livingRoomBeepWidget->setWindowFlag(Qt::FramelessWindowHint);
    livingRoomBeepWidget->setStyleSheet("QWidget{background-color:#999999;border-bottom-left-radius:25px;border-bottom-right-radius:25px}");
    livingRoomBeep_PushButton= new QPushButton(livingRoomBeepWidget);
    livingRoomBeep_PushButton->setGeometry(30,15,80,80);
    livingRoomBeep_PushButton->show();
    livingRoomBeep_PushButton->setEnabled(false);
    livingRoomBeep_PushButton->setFocusPolicy(Qt::NoFocus);
    livingRoomBeep_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/beep_close.png"")};");
    connect(livingRoomBeep_PushButton,&QPushButton::clicked,mainWidget,[=](){
        livingRoomBeep_PressFlag = !livingRoomBeep_PressFlag;
        if(livingRoomBeep_PressFlag)
        {
            livingRoomBeep_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/beep_open.png"")};");
            emit livingRoomBeep("121");
            //livingRoomLightStatus_Label->setStyleSheet("color:red");
            livingRoomBeepStatus_Label->setText("打开");
        }else{
            livingRoomBeep_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/beep_close.png"")};");
            emit livingRoomBeep("120");
            livingRoomBeepStatus_Label->setText("关闭");
          //livingRoomBeepStatus_Label->setStyleSheet("color:white");
        }
    });
    livingRoomBeep_Label = new QLabel("节点1       离线/",livingRoomBeepWidget);
    livingRoomBeep_Label->setGeometry(10,115,120,15);
    livingRoomBeep_Label->show();
    livingRoomBeep_Label->setStyleSheet("font-size:14px;color:white");//在线/打开
    livingRoomBeepStatus_Label = new QLabel("关闭",livingRoomBeepWidget);
    livingRoomBeepStatus_Label->setGeometry(102,115,35,15);
    livingRoomBeepStatus_Label->show();
    livingRoomBeepStatus_Label->setStyleSheet("font-size:14px;color:white");//在线/打开

    kitchenLight_Widget = new QWidget(mainWidget);
    kitchenLight_Widget->show();
    kitchenLight_Widget->setGeometry(328,0,144,140);
    kitchenLight_Widget->setWindowFlag(Qt::FramelessWindowHint);
    kitchenLight_Widget->setStyleSheet("QWidget{background-color:#999999;border-bottom-left-radius:25px;border-bottom-right-radius:25px}");
    kitchenLight_PushButton= new QPushButton(kitchenLight_Widget);
    kitchenLight_PushButton->setGeometry(30,15,80,80);
    kitchenLight_PushButton->show();
    kitchenLight_PushButton->setEnabled(false);
    kitchenLight_PushButton->setFocusPolicy(Qt::NoFocus);
    kitchenLight_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/kitchen_light_close.png"")};");
    connect(kitchenLight_PushButton,&QPushButton::clicked,mainWidget,[=](){
        kitchenLight_PressFlag = !kitchenLight_PressFlag;
        if(kitchenLight_PressFlag)
        {
            kitchenLight_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/kitchen_light_open.png"")};");
            emit kitchenLight("211");
            //kitchenLightStatus_Label->setStyleSheet("color:red");
            kitchenLightStatus_Label->setText("打开");
        }else{
            kitchenLight_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/kitchen_light_close.png"")};");
            emit kitchenLight("210");
            kitchenLightStatus_Label->setText("关闭");
          //kitchenLightStatus_Label->setStyleSheet("color:white");
        }
    });
    kitchenLight_Label = new QLabel("节点1       离线/",kitchenLight_Widget);
    kitchenLight_Label->setGeometry(10,115,120,15);
    kitchenLight_Label->show();
    kitchenLight_Label->setStyleSheet("font-size:14px;color:white");//在线/打开
    kitchenLightStatus_Label = new QLabel("关闭",kitchenLight_Widget);
    kitchenLightStatus_Label->setGeometry(102,115,35,15);
    kitchenLightStatus_Label->show();
    kitchenLightStatus_Label->setStyleSheet("font-size:14px;color:white");//在线/打开

    kitchenFan_Widget = new QWidget(mainWidget);
    kitchenFan_Widget->show();
    kitchenFan_Widget->setGeometry(492,0,144,140);
    kitchenFan_Widget->setWindowFlag(Qt::FramelessWindowHint);
    kitchenFan_Widget->setStyleSheet("QWidget{background-color:#999999;border-bottom-left-radius:25px;border-bottom-right-radius:25px}");
    kitchenFan_PushButton= new QPushButton(kitchenFan_Widget);
    kitchenFan_PushButton->setGeometry(30,15,80,80);
    kitchenFan_PushButton->show();
    kitchenFan_PushButton->setEnabled(false);
    kitchenFan_PushButton->setFocusPolicy(Qt::NoFocus);
    kitchenFan_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/kitchen_fan_close.png"")};");
    connect(kitchenFan_PushButton,&QPushButton::clicked,mainWidget,[=](){
        kitchenFan_PressFlag = !kitchenFan_PressFlag;
        if(kitchenFan_PressFlag)//press
        {
            kitchenFan_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/kitchen_fan_open.png"")};");
            emit kitchenFan("221");
            //kitchenLightStatus_Label->setStyleSheet("color:red");
            kitchenFanStatus_Label->setText("打开");
        }else{//not press
            kitchenFan_PushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/kitchen_fan_close.png"")};");
            emit kitchenFan("220");
            kitchenFanStatus_Label->setText("关闭");
          //kitchenLightStatus_Label->setStyleSheet("color:white");
        }
    });

    kitchenFan_Label = new QLabel("节点1       离线/",kitchenFan_Widget);
    kitchenFan_Label->setGeometry(10,115,120,15);
    kitchenFan_Label->show();
    kitchenFan_Label->setStyleSheet("font-size:14px;color:white");//在线/打开
    kitchenFanStatus_Label = new QLabel("关闭",kitchenFan_Widget);
    kitchenFanStatus_Label->setGeometry(102,115,35,15);
    kitchenFanStatus_Label->show();
    kitchenFanStatus_Label->setStyleSheet("font-size:14px;color:white");//在线/打开

    exitPushButtonWidget = new QWidget(mainWidget);
    exitPushButtonWidget->show();
    exitPushButtonWidget->setGeometry(656,0,144,140);
    exitPushButtonWidget->setWindowFlag(Qt::FramelessWindowHint);
    exitPushButtonWidget->setStyleSheet("QWidget{background-color:#999999;border-bottom-left-radius:25px}");
    exitPushButton= new QPushButton(exitPushButtonWidget);
    exitPushButton->setGeometry(32,20,80,80);
    exitPushButton->show();
    exitPushButton->setFocusPolicy(Qt::NoFocus);
    exitPushButton->setStyleSheet("QPushButton{border-image:url("":/environment/environmentIcon/environment_back.png"");}"
                                  "QPushButton:hover{border-image:url("":/environment/environmentIcon/environment_back_hover.png"")};");
    exitLabel = new QLabel("返 回",exitPushButtonWidget);
    exitLabel->setStyleSheet("color:white");
    exitLabel->show();
    exitLabel->setGeometry(55,100,50,30);

    connect(exitPushButton,&QPushButton::clicked,mainWidget,[=](){
        this->hide();
    });

    /*******************实时数据设置************************/
    realTimeData_Label = new QLabel("实 时 数 据",mainWidget);
    realTimeData_Label->setGeometry(640,180,150,40);
    realTimeData_Label->setStyleSheet("font: bold 28px;");
    realTimeData_Label->show();

    temperature_Label = new QLabel("温度: °C",mainWidget);
    temperature_Label->setGeometry(630,250,145,30);
    temperature_Label->setStyleSheet("font-size:20px");
    temperature_Label->show();

    humidity_Label= new QLabel("湿度: %",mainWidget);
    humidity_Label->setGeometry(630,300,140,30);
    humidity_Label->setStyleSheet("font-size:20px");
    humidity_Label->show();

    carbon_Label= new QLabel("烟雾浓度: %",mainWidget);
    carbon_Label->setGeometry(630,360,160,30);
    carbon_Label->setStyleSheet("font-size:20px");
    carbon_Label->show();

    smoke_Label= new QLabel("一氧化碳:  %",mainWidget);
    smoke_Label->setGeometry(630,420,160,30);
    smoke_Label->setStyleSheet("font-size:20px");
    smoke_Label->show();

    /***********************图表窗口设置**********************/
    sensorData_chart = new QChart();// 构建图表对象
    //sensorData_chart->legend()->hide();//隐藏图列
    sensorData_chart->setTitle("Sensors Data");
    sensorData_chart->setTheme(QChart::ChartThemeQt);//设置图表主题
    sensorData_chart->setAnimationOptions(QChart::NoAnimation);//设置图表的动画效果

    sensorData_axisX = new QValueAxis();//创建x轴
    sensorData_axisY = new QValueAxis();//创建y轴
    sensorData_axisX->setRange(0,180);//设置x轴的范围
    sensorData_axisY->setRange(0,120);//设置y轴的范围
    sensorData_axisX->setLabelsFont(QFont("Microsoft YaHei",10,QFont::Normal,false));
    sensorData_axisY->setLabelsFont(QFont("Microsoft YaHei",10,QFont::Normal,false));
    sensorData_axisX->setGridLineVisible(false);
    sensorData_axisY->setGridLineVisible(false);
    sensorData_axisX->setLabelFormat("%d");
    sensorData_axisY->setLabelFormat("%d");
    sensorData_axisX->setTickCount(10);
    sensorData_axisY->setTickCount(6);
    sensorData_axisX->setTitleText("time(s)");
    sensorData_axisY->setTitleText("percentage(%)");
    sensorData_axisX->setTitleFont(QFont("Microsoft YaHei",10,QFont::Normal,false));
    sensorData_axisY->setTitleFont(QFont("Microsoft YaHei",10,QFont::Normal,false));

    temperature_Series = new QSplineSeries();// 构建曲线系列对象
    temperature_Series->setColor(QColor("#FF9900"));
    temperature_Series->setName("temperature °C");
    temperature_Series->setPointsVisible(true);
    temperature_Series->setPointLabelsFormat("(@xPoint,@yPoint)");
    connect(temperature_Series,&QSplineSeries::hovered,this,[=](const QPointF &point,bool state){
         if(state)
         {
              pointLabel->setText(QString::number(point.y()));
              QPoint curposition = mapFromGlobal(QCursor::pos());
              pointLabel->move(curposition.x()-10,curposition.y()-15);
              //qDebug()<<curposition.x()<<curposition.y();
              pointLabel->show();
              pointLabel->setStyleSheet("QLable{font: bold 10px};"
                                        "QLable{background-color:#d5e4ff}");
         }else {
              pointLabel->hide();
         }
    });

    humidity_Series = new QSplineSeries();// 构建曲线系列对象
    humidity_Series->setColor(QColor("#0099CC"));
    humidity_Series->setName("humidity %");
    humidity_Series->setPointsVisible(true);
    humidity_Series->setPointLabelsFormat("(@xPoint,@yPoint)");
    connect(humidity_Series,&QSplineSeries::hovered,this,[=](const QPointF &point,bool state){
         if(state)
         {
              pointLabel->setText(QString::number(point.y()));
              QPoint curposition = mapFromGlobal(QCursor::pos());
              pointLabel->move(curposition.x()-10,curposition.y()-15);
              //qDebug()<<curposition.x()<<curposition.y();
              pointLabel->show();
              pointLabel->setStyleSheet("QLable{font: bold 10px};"
                                        "QLable{background-color:#d5e4ff}");
         }else {
              pointLabel->hide();
         }
    });


    carbon_Series = new QSplineSeries();// 构建曲线系列对象
    carbon_Series->setColor(QColor("#FF6666"));
    carbon_Series->setName("carbon %");
    carbon_Series->setPointsVisible(true);
    carbon_Series->setPointLabelsFormat("(@xPoint,@yPoint)");
    connect(carbon_Series,&QSplineSeries::hovered,this,[=](const QPointF &point,bool state){
         if(state)
         {
              pointLabel->setText(QString::number(point.y()));
              QPoint curposition = mapFromGlobal(QCursor::pos());
              pointLabel->move(curposition.x()-10,curposition.y()-15);
              //qDebug()<<curposition.x()<<curposition.y();
              pointLabel->show();
              pointLabel->setStyleSheet("QLable{font: bold 10px};"
                                        "QLable{background-color:#d5e4ff}");
         }else {
              pointLabel->hide();
         }
    });

    smoke_Series = new QSplineSeries();// 构建曲线系列对象
    smoke_Series->setColor(QColor("#339933"));
    smoke_Series->setName("smoke %");
    smoke_Series->setPointsVisible(true);
    smoke_Series->setPointLabelsFormat("(@xPoint,@yPoint)");
    connect(smoke_Series,&QSplineSeries::hovered,this,[=](const QPointF &point,bool state){
         if(state)
         {
              pointLabel->setText(QString::number(point.y()));
              QPoint curposition = mapFromGlobal(QCursor::pos());
              pointLabel->move(curposition.x()-10,curposition.y()-15);
              //qDebug()<<curposition.x()<<curposition.y();
              pointLabel->show();
              pointLabel->setStyleSheet("QLable{font: bold 10px};"
                                        "QLable{background-color:#d5e4ff}");
         }else {
              pointLabel->hide();
         }
    });

    sensorData_chart->addSeries(temperature_Series);//图表添加曲线系列
    sensorData_chart->addSeries(humidity_Series);//图表添加曲线系列
    sensorData_chart->addSeries(carbon_Series);//图表添加曲线系列
    sensorData_chart->addSeries(smoke_Series);//图表添加曲线系列
    sensorData_chart->setAxisX(sensorData_axisX,temperature_Series);
    sensorData_chart->setAxisY(sensorData_axisY,temperature_Series);
    sensorData_chart->setAxisX(sensorData_axisX,humidity_Series);
    sensorData_chart->setAxisY(sensorData_axisY,humidity_Series);
    sensorData_chart->setAxisX(sensorData_axisX,carbon_Series);
    sensorData_chart->setAxisY(sensorData_axisY,carbon_Series);
    sensorData_chart->setAxisX(sensorData_axisX,smoke_Series);
    sensorData_chart->setAxisY(sensorData_axisY,smoke_Series);

    sensorData_chartView = new QChartView(sensorData_chart,mainWidget);//构建图表显示视图
    sensorData_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    sensorData_chartView->setGeometry(0,160,600,320);
    sensorData_chartView->show();

    pointLabel = new QLabel(this);
    pointLabel->setFixedSize(30,15);

}

//    //温度图表：
//    temperature_chart = new QChart();// 构建图表对象
//    temperature_chart->legend()->hide();//隐藏图列
//    temperature_chart->setTitle("实时温度曲线");
//    temperature_chart->setTheme(QChart::ChartThemeQt);//设置图表主题
//    temperature_chart->setAnimationOptions(QChart::NoAnimation);//设置图表的动画效果

//    temp_axisX = new QValueAxis();//创建x轴
//    temp_axisY = new QValueAxis();//创建y轴
//    temperature_chart->addAxis(temp_axisX,Qt::AlignBottom);//给图表添加x轴
//    temperature_chart->addAxis(temp_axisY,Qt::AlignLeft);//给图表添加y轴

//    temp_axisX->setRange(0,180);//设置x轴的范围
//    temp_axisY->setRange(0,50);//设置y轴的范围



//    temperature_Series = new QSplineSeries();// 构建曲线系列对象
//    temperature_chart->addSeries(temperature_Series);//图表添加曲线系列
//    temperature_Series->attachAxis(temp_axisX);//曲线关联x轴
//    temperature_Series->attachAxis(temp_axisY);//曲线关联y轴

//    temperature_chartView = new QChartView(temperature_chart,mainWidget);//构建图表显示视图
//    temperature_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
//    temperature_chartView->setGeometry(160,0,315,240);
//    temperature_chartView->show();

//    //湿度图表：
//    humidity_chart = new QChart();// 构建图表对象
//    humidity_chart->legend()->hide();//隐藏图列
//    humidity_chart->setTitle("实时湿度曲线");
//    humidity_chart->setAnimationOptions(QChart::NoAnimation);//设置图表的动画效果

//    humi_axisX = new QValueAxis();//创建x轴
//    humi_axisY = new QValueAxis();//创建y轴
//    humidity_chart->addAxis(humi_axisX,Qt::AlignBottom);//给图表添加x轴
//    humidity_chart->addAxis(humi_axisY,Qt::AlignLeft);//给图表添加y轴

//    humi_axisX->setRange(0,180);//设置x轴的范围
//    humi_axisY->setRange(0,100);//设置y轴的范围

//    humidity_Series = new QSplineSeries();// 构建曲线系列对象
//    humidity_chart->addSeries(humidity_Series);//图表添加曲线系列
//    humidity_Series->attachAxis(humi_axisX);//曲线关联x轴
//    humidity_Series->attachAxis(humi_axisY);//曲线关联y轴

//    humidity_chartView = new QChartView(humidity_chart,mainWidget);//构建图表显示视图
//    humidity_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
//    humidity_chartView->setGeometry(480,0,315,240);
//    humidity_chartView->show();

//    //一氧化碳图表：
//    carbon_chart = new QChart();// 构建图表对象
//    carbon_chart->legend()->hide();//隐藏图列
//    carbon_chart->setTitle("实时一氧化碳浓度曲线");
//    carbon_chart->setAnimationOptions(QChart::NoAnimation);//设置图表的动画效果

//    carbon_axisX = new QValueAxis();//创建x轴
//    carbon_axisY = new QValueAxis();//创建y轴
//    carbon_chart->addAxis(carbon_axisX,Qt::AlignBottom);//给图表添加x轴
//    carbon_chart->addAxis(carbon_axisY,Qt::AlignLeft);//给图表添加y轴

//    carbon_axisX->setRange(0,180);//设置x轴的范围
//    carbon_axisY->setRange(0,100);//设置y轴的范围

//    carbon_Series = new QSplineSeries();// 构建曲线系列对象
//    carbon_chart->addSeries(carbon_Series);//图表添加曲线系列
//    carbon_Series->attachAxis(carbon_axisX);//曲线关联x轴
//    carbon_Series->attachAxis(carbon_axisY);//曲线关联y轴

//    carbon_chartView = new QChartView(carbon_chart,mainWidget);//构建图表显示视图
//    carbon_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
//    carbon_chartView->setGeometry(160,240,315,240);
//    carbon_chartView->show();

//    //烟雾浓度图表：
//    smoke_chart = new QChart();// 构建图表对象
//    smoke_chart->legend()->hide();//隐藏图列
//    smoke_chart->setTitle("实时烟雾浓度曲线");
//    smoke_chart->setAnimationOptions(QChart::NoAnimation);//设置图表的动画效果

//    smoke_axisX = new QValueAxis();//创建x轴
//    smoke_axisY = new QValueAxis();//创建y轴
//    smoke_chart->addAxis(smoke_axisX,Qt::AlignBottom);//给图表添加x轴
//    smoke_chart->addAxis(smoke_axisY,Qt::AlignLeft);//给图表添加y轴

//    smoke_axisX->setRange(0,180);//设置x轴的范围
//    smoke_axisY->setRange(0,100);//设置y轴的范围

//    smoke_Series = new QSplineSeries();// 构建曲线系列对象
//    smoke_chart->addSeries(smoke_Series);//图表添加曲线系列
//    smoke_Series->attachAxis(smoke_axisX);//曲线关联x轴
//    smoke_Series->attachAxis(smoke_axisY);//曲线关联y轴

//    smoke_chartView = new QChartView(smoke_chart,mainWidget);//构建图表显示视图
//    smoke_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
//    smoke_chartView->setGeometry(480,240,315,240);
//    smoke_chartView->show();

//设置温度曲线数据
//        QList<QPointF> temperature_points;
//        temperature_points.clear();
//        temperature_ylist.append(temperature);
//        int j = 0;
//        if(temperature_ylist.length()>60)
//        {
//            temperature_ylist.removeFirst();
//            for(int i=0;i<60;i++)
//            {
//                j=j+3;//每3秒更新一次数据，同步串口的发送时间
//                temperature_points.append(QPointF(j,temperature_ylist.at(i)));
//            }
//        }else {
//            for(int i=0;i<temperature_ylist.length();i++)
//            {
//                j=j+3;//每3秒更新一次数据，同步串口的发送时间
//                temperature_points.append(QPointF(j,temperature_ylist.at(i)));
//            }
//        }
//        //qDebug()<<temperature_points<<endl;
//        temperature_Series->replace(temperature_points);


//        //设置湿度曲线数据
//        QList<QPointF> humidity_points;
//        humidity_points.clear();
//        humidity_ylist.append(humidity);
//        j = 0;
//        if(humidity_ylist.length()>60)
//        {
//            humidity_ylist.removeFirst();
//            for(int i=0;i<60;i++)
//            {
//                j=j+3;//每3秒更新一次数据，同步串口的发送时间
//                humidity_points.append(QPointF(j,humidity_ylist.at(i)));
//            }
//        }else {
//            for(int i=0;i<humidity_ylist.length();i++)
//            {
//                j=j+3;//每3秒更新一次数据，同步串口的发送时间
//                humidity_points.append(QPointF(j,humidity_ylist.at(i)));
//            }
//        }
//        //qDebug()<<humidity_points<<endl;
//        humidity_Series->replace(humidity_points);


//        //设置一氧化碳浓度曲线数据
//        QList<QPointF> carbon_points;
//        carbon_points.clear();
//        carbon_ylist.append(carbon);
//        j = 0;
//        if(carbon_ylist.length()>60)
//        {
//            carbon_ylist.removeFirst();
//            for(int i=0;i<60;i++)
//            {
//                j=j+3;//每3秒更新一次数据，同步串口的发送时间
//                carbon_points.append(QPointF(j,carbon_ylist.at(i)));
//            }
//        }else {
//            for(int i=0;i<carbon_ylist.length();i++)
//            {
//                j=j+3;//每3秒更新一次数据，同步串口的发送时间
//                carbon_points.append(QPointF(j,carbon_ylist.at(i)));
//            }
//        }
//        //qDebug()<<carbon_points<<endl;
//        carbon_Series->replace(carbon_points);


//        //设置烟雾浓度曲线数据
//        QList<QPointF> smoke_points;
//        smoke_points.clear();
//        smoke_ylist.append(smoke);
//        j = 0;
//        if(smoke_ylist.length()>60)
//        {
//            smoke_ylist.removeFirst();
//            for(int i=0;i<60;i++)
//            {
//                j=j+3;//每3秒更新一次数据，同步串口的发送时间
//                smoke_points.append(QPointF(j,smoke_ylist.at(i)));
//            }
//        }else {
//            for(int i=0;i<smoke_ylist.length();i++)
//            {
//                j=j+3;//每3秒更新一次数据，同步串口的发送时间
//                smoke_points.append(QPointF(j,smoke_ylist.at(i)));
//            }
//        }
//        //qDebug()<<smoke_points<<endl;
//        smoke_Series->replace(smoke_points);

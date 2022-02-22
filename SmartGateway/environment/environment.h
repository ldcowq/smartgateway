#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QWidget>
#include <tools/switchbutton.h>
#include <QThread>
#include <environment/getsensordatabyserial.h>
#include <QLabel>
#include <QPushButton>
#include <QChartView>
#include <QChart>
#include <QSplineSeries>
#include <QValueAxis>
#include<QList>
#include<QAreaSeries>
using namespace QtCharts;
class Environment : public QWidget
{
    Q_OBJECT
public:
    explicit Environment(QWidget *parent = 0);
    QThread *subThread;
    GetSensorDataBySerial *getSensorDataBySerialTask;
    void layoutInit();

    QWidget *mainWidget;
    QLabel *realTimeData_Label;
    QLabel *temperature_Label;
    QLabel *humidity_Label;
    QLabel *carbon_Label;
    QLabel *smoke_Label;


    QWidget *exitPushButtonWidget;
    QPushButton *exitPushButton;
    QLabel *exitLabel;

    QWidget *livingRoomLight_Widget;
    QPushButton *livingRoomLight_PushButton;
    QLabel *livingRoomLight_Label;
    QLabel *livingRoomLightStatus_Label;
    bool livingRoomLight_PressFlag=false;

    QWidget *livingRoomBeepWidget;
    QPushButton *livingRoomBeep_PushButton;
    QLabel *livingRoomBeep_Label;
    QLabel *livingRoomBeepStatus_Label;
    bool livingRoomBeep_PressFlag=false;

    QWidget *kitchenLight_Widget;
    QPushButton *kitchenLight_PushButton;
    QLabel *kitchenLight_Label;
    QLabel *kitchenLightStatus_Label;
    bool kitchenLight_PressFlag=false;

    QWidget *kitchenFan_Widget;
    QPushButton *kitchenFan_PushButton;
    QLabel *kitchenFan_Label;
    QLabel *kitchenFanStatus_Label;
    bool kitchenFan_PressFlag=false;

    /*Sensors data chart*/
    QChartView *sensorData_chartView;
    QChart *sensorData_chart;
    QValueAxis *sensorData_axisX;
    QValueAxis *sensorData_axisY;
    QSplineSeries *temperature_Series;
    QSplineSeries *humidity_Series;
    QSplineSeries *carbon_Series;
    QSplineSeries *smoke_Series;
    QList<double> temperature_ylist;
    QList<double> humidity_ylist;
    QList<double> carbon_ylist;
    QList<double> smoke_ylist;
    QList<QPointF> temperature_points;
    QList<QPointF> humidity_points;
    QList<QPointF> carbon_points;
    QList<QPointF> smoke_points;

    QLabel *pointLabel;

//    /*温度图表*/
//    QChartView *temperature_chartView;
//    QChart *temperature_chart;
//    QSplineSeries *temperature_Series;
//    QValueAxis *temp_axisX;
//    QValueAxis *temp_axisY;
//    QList<double> temperature_ylist;

//    /*湿度图表*/
//    QChartView *humidity_chartView;
//    QChart *humidity_chart;
//    QSplineSeries *humidity_Series;
//    QValueAxis *humi_axisX;
//    QValueAxis *humi_axisY;
//    QList<double> humidity_ylist;


//    /*一氧化碳图表*/
//    QChartView *carbon_chartView;
//    QChart *carbon_chart;
//    QSplineSeries *carbon_Series;
//    QValueAxis *carbon_axisX;
//    QValueAxis *carbon_axisY;
//    QList<double> carbon_ylist;


//    /*烟雾图表*/
//    QChartView *smoke_chartView;
//    QChart *smoke_chart;
//    QSplineSeries *smoke_Series;
//    QValueAxis *smoke_axisX;
//    QValueAxis *smoke_axisY;
//    QList<double> smoke_ylist;


signals:
    void livingRoomLight(QString status);
    void livingRoomBeep(QString status);
    void kitchenLight(QString status);
    void kitchenFan(QString status);
public slots:
};

#endif // ENVIRONMENT_H

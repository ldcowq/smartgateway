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
    SwitchButton *sw;
    QThread *subThread;
    GetSensorDataBySerial *getSensorDataBySerialTask;
    void layoutInit();

    QWidget *mainWidget;
    QLabel *realTimeData_Label;
    QLabel *temperature_Label;
    QLabel *humidity_Label;
    QLabel *carbon_Label;
    QLabel *smoke_Label;
    QPushButton *exitPushButton;

    /*温度图表*/
    QChartView *temperature_chartView;
    QChart *temperature_chart;
    QSplineSeries *temperature_Series;
    QValueAxis *temp_axisX;
    QValueAxis *temp_axisY;
    QList<double> temperature_ylist;

    /*湿度图表*/
    QChartView *humidity_chartView;
    QChart *humidity_chart;
    QSplineSeries *humidity_Series;
    QValueAxis *humi_axisX;
    QValueAxis *humi_axisY;
    QList<double> humidity_ylist;


    /*一氧化碳图表*/
    QChartView *carbon_chartView;
    QChart *carbon_chart;
    QSplineSeries *carbon_Series;
    QValueAxis *carbon_axisX;
    QValueAxis *carbon_axisY;
    QList<double> carbon_ylist;


    /*烟雾图表*/
    QChartView *smoke_chartView;
    QChart *smoke_chart;
    QSplineSeries *smoke_Series;
    QValueAxis *smoke_axisX;
    QValueAxis *smoke_axisY;
    QList<double> smoke_ylist;


signals:

public slots:
};

#endif // ENVIRONMENT_H

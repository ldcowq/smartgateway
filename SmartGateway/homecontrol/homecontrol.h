#ifndef HOMECONTROL_H
#define HOMECONTROL_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
class HomeControl : public QWidget
{
    Q_OBJECT
public:
    explicit HomeControl(QWidget *parent = 0);
    void layoutInit();
    QSerialPort *pSerialPort;
    QString portName;//串口名字
    QPushButton * lightPushButton;
    QPushButton * fansPushButton;
    QPushButton * alarmPushButton;
signals:
    void openlight(qint16);
public slots:
};

#endif // HOMECONTROL_H

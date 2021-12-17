#ifndef GETSENSORDATABYSERIAL_H
#define GETSENSORDATABYSERIAL_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <QSerialPort>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSerialPortInfo>
#include <QtNetwork>
#include <QHostAddress>
#include <QtMqtt/qmqttclient.h>

class GetSensorDataBySerial : public QObject
{
    Q_OBJECT
public:
    explicit GetSensorDataBySerial(QObject *parent = 0);
    ~GetSensorDataBySerial();
    QSerialPort *pSerialPort;
    QTimer *timer;
    QTimer *checkPortTimer;
    QString mPortName=NULL;//串口号
    QJsonDocument doucument;
    QJsonParseError jsonError;

    QByteArray recvBuf;

    int temperatureValue;
    int humidityValue;
    int carbonValue;
    int smokeValue;

    QMqttClient* mqttClient=nullptr;
    QString publishTopic ="SmartGatewayPub";
    QString subscribeTopic = "SmartGatewaySub";
    void scanSerialPort(void);
    void initSerialPort(QString mPortName);
    void receiveSerialData();
    void connectMqtt(void);
    void disconnectMqtt(QMqttClient **mMqttClient);
    void reConnectMqtt();

signals:

    //void updateLivingData(int temperature,int humidity);
    //void updateKitchenData(int carbon,int smoke);
    void updateSensorData(int temperature=0,int humidity=0,int carbon=0,int smoke=0);
    void noSensorSignal();
    void finished();
public slots:
    void pSerialPort_onErrorOccurred(QSerialPort::SerialPortError);
    //业务处理函数
    void working();
    void onMqttConnected();
    void onMqttReceived(QByteArray message);
};

#endif // GETSENSORDATABYSERIAL_H

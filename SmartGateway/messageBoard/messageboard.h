#ifndef MESSAGEBOARD_H
#define MESSAGEBOARD_H

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QTimer>
#include <QDebug>
class MessageBoard : public QObject
{
    Q_OBJECT
public:
    explicit MessageBoard(QObject *parent = nullptr);

    QMqttClient* mqttClient=nullptr;
    QString messageTopic ="SmartGatewayMessage";
    void connectMqtt(void);
    void disconnectMqtt(QMqttClient **mMqttClient);
    void reConnectMqtt();
    QByteArray recvBuf;
    QTimer* reconnectTimer;
signals:
    void finished(void);
    void getMqttMessage(QByteArray message);
public slots:
    void working();
    void onMqttConnected();
    void onMqttReceived(QByteArray message);
};

#endif // MESSAGEBOARD_H

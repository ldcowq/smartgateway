#include "messageboard.h"

MessageBoard::MessageBoard(QObject *parent) : QObject(parent)
{

}


void MessageBoard::working()
{
    reconnectTimer = new QTimer();
    reConnectMqtt();
}

void MessageBoard::connectMqtt()
{
    if(mqttClient!=nullptr)
    {
        disconnectMqtt(&mqttClient);
    }
    mqttClient = new QMqttClient();
    mqttClient->setHostname("106.13.7.2");
    mqttClient->setPort(1883);
    mqttClient->setClientId("0002");
    mqttClient->setUsername("messageBoard");
    mqttClient->setPassword("123");
    mqttClient->connectToHost();
    connect(mqttClient,&QMqttClient::connected,this,&MessageBoard::onMqttConnected);
    connect(mqttClient,&QMqttClient::disconnected,this,[=](){
        reConnectMqtt();
    });
}

void MessageBoard::onMqttConnected()
{
    if(mqttClient->state()==QMqttClient::Connected)
    {
        qDebug() << "已连接服务器: "<<mqttClient->hostname();
        mqttClient->subscribe(QMqttTopicFilter(messageTopic));
        connect(mqttClient,&QMqttClient::messageReceived,this,&MessageBoard::onMqttReceived);
        reconnectTimer->stop();
    }else {
        reConnectMqtt();
    }
}

void MessageBoard::onMqttReceived(QByteArray message)
{
    emit getMqttMessage(message);
    qDebug()<<message<<endl;
}

void MessageBoard::disconnectMqtt(QMqttClient **mqttclient)
{
    if((*mqttclient)!=NULL||(*mqttclient)->state()==QMqttClient::Connected)
    {
        (*mqttclient)->disconnectFromHost();
        delete (*mqttclient);
    }
}

void MessageBoard::reConnectMqtt()
{
    connect(reconnectTimer,&QTimer::timeout,this,[=]{
        connectMqtt();
    });
    reconnectTimer->start(3000);
}

#include "getsensordatabyserial.h"
#include "../homecontrol/homecontrol.h"

GetSensorDataBySerial::GetSensorDataBySerial(QObject *parent) : QObject(parent)
{

}

void GetSensorDataBySerial::working()
{
    reconnectTimer = new QTimer();
    timer =new QTimer();
    checkPortTimer = new QTimer();
    scanSerialPort();
    while (mPortName==NULL) {
        QThread::sleep(1);
        qDebug() << "正在扫描设备...: ";
        scanSerialPort();
    }

    initSerialPort(mPortName);
    while (pSerialPort==NULL) {
        QThread::sleep(1);
        initSerialPort(mPortName);
    }

    qDebug() << "已检测到设备: " << mPortName;

    receiveSerialData();
    //reConnectMqtt();
}

void GetSensorDataBySerial::connectMqtt()
{
    if(mqttClient!=nullptr)
    {
        disconnectMqtt(&mqttClient);
    }
    mqttClient = new QMqttClient();
    mqttClient->setHostname("106.13.7.2");
    mqttClient->setPort(1883);
    mqttClient->setClientId("0001");
    mqttClient->setUsername("User_Gateway_1");
    mqttClient->setPassword("123");
    mqttClient->connectToHost();
    connect(mqttClient,&QMqttClient::connected,this,&GetSensorDataBySerial::onMqttConnected);
    connect(mqttClient,&QMqttClient::disconnected,this,[=](){
        reConnectMqtt();
    });
}

void GetSensorDataBySerial::onMqttConnected()
{
    if(mqttClient->state()==QMqttClient::Connected)
    {
        qDebug() << "已连接服务器: "<<mqttClient->hostname();
        mqttClient->subscribe(QMqttTopicFilter(subscribeTopic));
        connect(mqttClient,&QMqttClient::messageReceived,this,&GetSensorDataBySerial::onMqttReceived);
        reconnectTimer->stop();
    }else {
        reConnectMqtt();
    }
}

void GetSensorDataBySerial::onMqttReceived(QByteArray message)
{
    qDebug()<<"收到"<< subscribeTopic <<"主题消息:"<<"["<<message<<"]"<<endl;
    if(pSerialPort==nullptr) return ;
    //把消息转发到串口
    pSerialPort->write(message);
}

void GetSensorDataBySerial::disconnectMqtt(QMqttClient **mqttclient)
{
    if((*mqttclient)!=NULL||(*mqttclient)->state()==QMqttClient::Connected)
    {
        (*mqttclient)->disconnectFromHost();
        delete (*mqttclient);
    }
}

void GetSensorDataBySerial::reConnectMqtt()
{
    connect(reconnectTimer,&QTimer::timeout,this,[=]{
        connectMqtt();
    });
    reconnectTimer->start(3000);
}

void GetSensorDataBySerial::receiveSerialData()
{
    if(pSerialPort->open(QSerialPort::ReadWrite))
    {
        //串口获取传感器数据
        qDebug()<<"Open uart successfully!";
        connect(pSerialPort,&QSerialPort::readyRead,this,[=](){

            if(mqttClient==nullptr)
            {
                connectMqtt();
            }

            if(mqttClient->state()==QMqttClient::Disconnected)
            {
                reConnectMqtt();
            }

            timer->start(30);//一次串口读取数据开始
            connect(timer,&QTimer::timeout,this,[=](){
                recvBuf=pSerialPort->readAll();
                if(!recvBuf.isEmpty())
                {
                    qDebug()<<recvBuf;
                    doucument=QJsonDocument::fromJson(recvBuf,&jsonError);

                    if((!doucument.isNull())&&(jsonError.error==QJsonParseError::NoError))//如果json解析没有错误
                    {

                        if(doucument.isObject())
                        {
                            QJsonObject object =doucument.object();

                            QString devicesType = object.value("type").toString().trimmed();
                            int devicesId = object.value("deviceId").toInt();
                            qDebug()<<devicesType<<"  "<<devicesId<<endl;

                            if(devicesId==1)//livingRoom device
                            {
                                //qDebug()<<"emit livingRoom heart beat:"<<devicesId<<endl;
                                int state = object.value("state").toInt();
                                emit sendLivingRoomHeartBeat(devicesId,state);
                            }

                            if(devicesId==2)//kitchen device
                            {
                                //qDebug()<<"emit kitchen heart beat:"<<devicesId<<endl;
                                int state = object.value("state").toInt();
                                emit sendKitchenHeartBeat(devicesId,state);
                            }

                            if(QString::compare("kitchen",devicesType)==0)
                            {
                                carbonValue = object.value("Carbon").toInt();
                                smokeValue = object.value("Smoke").toInt();                                
                                emit updateMqData(carbonValue,smokeValue);
                            }

                            if(QString::compare("living",devicesType)==0)
                            {
                                temperatureValue = object.value("Temperature").toInt();
                                humidityValue = object.value("Humidity").toInt();
                                emit updateDht11Data(temperatureValue,humidityValue);
                            }

//                            if(temperatureValue>100||temperatureValue<0||humidityValue>100||humidityValue<0||
//                                    carbonValue>100||carbonValue<0||smokeValue>100||smokeValue<0) return;
                            //emit updateSensorData(temperatureValue,humidityValue,carbonValue,smokeValue);
                        }
                    }

                    QString jsonMessage =QString(recvBuf);
                    if(mqttClient!=nullptr)
                    {
                        if(mqttClient->state()==QMqttClient::Connected&&mqttClient!=NULL)
                        {
                            //qDebug()<<"payload:"+jsonMessage<<endl;
                            mqttClient->publish(QMqttTopicName(publishTopic),jsonMessage.toLocal8Bit());
                        }else{
                            reConnectMqtt();
                        }
                    }
                    recvBuf.clear();
                }
        });
     });//串口获取传感器数据结束
    timer->stop();//一次串口数据获取完成
    }
}

void GetSensorDataBySerial::pSerialPort_onErrorOccurred(QSerialPort::SerialPortError e)
{
    if (e == QSerialPort::ResourceError)
    {
           emit noSensorSignal();
            if(pSerialPort!=NULL)
            {
                if(pSerialPort->isOpen())
                {
                    pSerialPort->close();
                    delete pSerialPort;
                }
            }
    }
}

void GetSensorDataBySerial::scanSerialPort()
{
    QList<QSerialPortInfo> serialPortList = QSerialPortInfo::availablePorts();
    if(!serialPortList.isEmpty())
    {
        foreach(QSerialPortInfo serialInfo,QSerialPortInfo::availablePorts()){//遍历串口
            qDebug()<<serialInfo.serialNumber()<<"\n";
            if(serialInfo.serialNumber()==QString::fromLocal8Bit("0001"))//判断是否为usb串口0
            {
                mPortName=serialInfo.portName();
                qDebug()<<serialInfo.portName()<<"\n";
            }
        }

        if(mPortName.isNull()&&mPortName.isEmpty())
        {
            emit noSensorSignal();
            qDebug()<<"mPortName is null"<<"\n";
            QThread::sleep(1);
        }

    }else{
        emit noSensorSignal();
        qDebug()<<"serialInfo is empty"<<"\n";
        QThread::sleep(1);
    }
}

void GetSensorDataBySerial::initSerialPort(QString mPortName)
{
    if(!mPortName.isEmpty()&&!mPortName.isNull())
    {
        pSerialPort=new QSerialPort(this);
        pSerialPort->setPortName(mPortName);
        pSerialPort->setBaudRate(QSerialPort::Baud115200);
        pSerialPort->setParity(QSerialPort::NoParity);
        pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
        pSerialPort->setStopBits(QSerialPort::OneStop);
        pSerialPort->setDataBits(QSerialPort::Data8);
        connect(pSerialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(pSerialPort_onErrorOccurred(QSerialPort::SerialPortError)));
        qDebug()<<"serial init successfully!"<<"\n";
    }else {
        qDebug()<<"scan port failure"<<"\n";
    }
}

GetSensorDataBySerial::~GetSensorDataBySerial()
{
    disconnectMqtt(&mqttClient);
    pSerialPort->close();
    delete pSerialPort;
}

void GetSensorDataBySerial::onLivingRoomLight(QString status)
{
    qDebug()<<"status = "<<status<<endl;
    pSerialPort->write(status.toUtf8().data(),status.size());
}

void GetSensorDataBySerial::onLivingRoomBeep(QString status)
{
    qDebug()<<"status = "<<status<<endl;
    pSerialPort->write(status.toUtf8().data(),status.size());
}


void GetSensorDataBySerial::onkitchenLight(QString status)
{
    qDebug()<<"status = "<<status<<endl;
    pSerialPort->write(status.toUtf8().data(),status.size());
}


void GetSensorDataBySerial::onkitchenFan(QString status)
{
    qDebug()<<"status = "<<status<<endl;
    pSerialPort->write(status.toUtf8().data(),status.size());
}

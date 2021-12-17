#include "getsensordatabyserial.h"
#include "../homecontrol/homecontrol.h"

GetSensorDataBySerial::GetSensorDataBySerial(QObject *parent) : QObject(parent)
{

}

void GetSensorDataBySerial::working()
{
    timer =new QTimer();
    checkPortTimer = new QTimer();
    qDebug() << "current address: " << QThread::currentThread();
    qDebug() << "thread count: " << QThread::idealThreadCount();
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
    connectMqtt();
    //qDebug() <<"emit finished()"<<endl;
    //emit finished();
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
}

void GetSensorDataBySerial::onMqttConnected()
{
    if(mqttClient->state()==QMqttClient::Connected)
    {
        qDebug() << "已连接服务器: "<<mqttClient->hostname();
        mqttClient->subscribe(QMqttTopicFilter(subscribeTopic));
        connect(mqttClient,&QMqttClient::messageReceived,this,&GetSensorDataBySerial::onMqttReceived);
        if(mqttClient!=NULL&&mqttClient->state()==QMqttClient::Connected)
        {
            qDebug() << "正在采集传感器数据... ";
            receiveSerialData();

        }
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
    QTimer* timer = new QTimer();
    disconnectMqtt(&mqttClient);
    connect(timer,&QTimer::timeout,this,[=]{
        connectMqtt();
    });
    timer->start(3000);
    if(mqttClient!=NULL&&mqttClient->state()==QMqttClient::Connected)
    {
        timer->stop();
    }
}

void GetSensorDataBySerial::receiveSerialData()
{

    qDebug()<<pSerialPort;

    if(pSerialPort->open(QSerialPort::ReadWrite))
    {
        //串口获取传感器数据
        qDebug()<<"Open uart successfully!";
        connect(pSerialPort,&QSerialPort::readyRead,this,[=](){
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
                            QString sensorType = object.value("type").toString().trimmed();
                            if(QString::compare("kitchen",sensorType)==0)
                            {
                                carbonValue = object.value("Carbon").toInt();
                                smokeValue = object.value("Smoke").toInt();
                                qDebug()<<carbonValue<<smokeValue<<endl;
                                //emit updateKitchenData(carbonValue,smokeValue);
                            }

                            if(QString::compare("living",sensorType)==0)
                            {
                                temperatureValue = object.value("Temperature").toInt();
                                humidityValue = object.value("Humidity").toInt();
                                qDebug()<<temperatureValue<<humidityValue<<endl;
                                //emit updateLivingData(temperatureValue,humidityValue);
                            }
                            emit updateSensorData(temperatureValue,humidityValue,carbonValue,smokeValue);
                        }
                    }

                    QString jsonMessage =QString(recvBuf);
                    if(mqttClient->state()==QMqttClient::Connected&&mqttClient!=NULL)
                    {
                        //网关显示数据后，上传到云端
                        //发布主题
                        qDebug()<<"payload:"+jsonMessage<<endl;
                        mqttClient->publish(QMqttTopicName(publishTopic),jsonMessage.toLocal8Bit());
                    }else{
                        reConnectMqtt();
                    }
                    recvBuf.clear();
                }
        });
     });//串口获取传感器数据结束
    timer->stop();//一次串口数据获取完成
    }else{
        QThread::sleep(1);
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
    if(pSerialPort!=NULL)
    {
        pSerialPort->close();
        delete pSerialPort;
    }

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


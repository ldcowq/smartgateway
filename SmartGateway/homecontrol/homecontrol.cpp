#include "homecontrol.h"
static int buttonClicked_count=0;
HomeControl::HomeControl(QWidget *parent) : QWidget(parent)
{
    layoutInit();
//    foreach(QSerialPortInfo serialInfo,QSerialPortInfo::availablePorts()){//遍历串口
//        if(serialInfo.portName()==QString::fromLocal8Bit("ttyUSB0"))//判断是否为usb串口0
//        {
//            portName=serialInfo.portName();
//            qDebug()<<serialInfo.portName()<<"\n";
//        }
//    }

//    if(!portName.isEmpty())//有串口可用
//    {
//        pSerialPort=new QSerialPort(this);
//        pSerialPort->setPortName(portName);
//        pSerialPort->setBaudRate(QSerialPort::Baud115200);
//        pSerialPort->setParity(QSerialPort::NoParity);
//        pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
//        pSerialPort->setStopBits(QSerialPort::OneStop);
//        pSerialPort->setDataBits(QSerialPort::Data8);
//        if(pSerialPort->open(QSerialPort::ReadWrite))
//        {
//            qDebug()<<"Open uart successfully!";
//            lightPushButton->setEnabled(true);
//            fansPushButton->setEnabled(true);
//            alarmPushButton->setEnabled(true);
//            connect(lightPushButton,&QPushButton::clicked,this,[=](){
//                if(buttonClicked_count%2==0)
//                {
//                    char buf='1';
//                    pSerialPort->write(&buf);
//                    lightPushButton->setText("关灯");
//                }

//                if(buttonClicked_count%2==1)
//                {
//                    char buf='2';
//                    pSerialPort->write(&buf);
//                    lightPushButton->setText("开灯");
//                }
//                buttonClicked_count++;
//            });

//        }else{
//            QMessageBox::warning(NULL,"warning","SerialPort opening failure!");
//        }
//    }else{
//        QMessageBox::warning(NULL,"warning","No sensor detected!");
//    }

}

void HomeControl::layoutInit()
{
    this->setGeometry(0,0,800,480);
    this->move(200,200);
    this->show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    lightPushButton  = new QPushButton("灯",this);
    lightPushButton->setGeometry(0,0,50,30);
    lightPushButton->setEnabled(false);
    lightPushButton->show();

    fansPushButton= new QPushButton("风扇",this);
    fansPushButton->setGeometry(100,0,50,30);
    fansPushButton->setEnabled(false);
    fansPushButton->show();

    alarmPushButton= new QPushButton("报警器",this);
    alarmPushButton->setGeometry(200,0,50,30);
    alarmPushButton->setEnabled(false);
    alarmPushButton->show();
}

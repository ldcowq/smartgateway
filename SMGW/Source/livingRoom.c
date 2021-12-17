#include "livingRoom.h"

/*****************从DHT11读取一个字节函数******************/        
void  Read_Byte(void)
{
  uint8 i;
  for (i = 0; i < 8; i++)                     //循环8次，读取8bit的数据
  {
    Overtime_counter = 2;                          //读取并等待DHT11发出的12-14us低电平开始信号
    P0DIR &= ~0x10;
    while ((!DHT11_DATA) && Overtime_counter++);
    //Delay_10us(80);                   //26-28us的低电平判断门限
    MicroWait(27);
    bit_value = 0;                          //跳过门限后判断总线是高还是低，高为1，低为0
    if(DHT11_DATA)
    bit_value = 1;
    Overtime_counter=2;                          //等待1bit的电平信号结束，不管是0是1在118us后都变为低电平，否则错误超时
    while (DHT11_DATA && Overtime_counter++);  //当U8FLAG加到255后溢出为0，跳出循环，并后加加为1
    if (Overtime_counter == 1)
      break;                           //超时则跳出for循环        
    comdata <<= 1;                      //左移1位，LSB补0
    comdata |= bit_value;                  //LSB赋值
  }
}

/*****************DHT11读取五个字节函数******************/
/*
功能描述：获取dht11的温湿度
参数说明：
    *temp：返回温度的整数部分
    *humid：返回湿度的整数部分
返回值：
  0：成功读取
  <0：读取失败
*/
int Read_DHT11(unsigned char *temp,unsigned char *humid)
{
    int result=-1;
    uint8 checksum;
    P0DIR |= 0x10;
    DHT11_DATA = 0;                //主机拉低18ms
    MicroWait(18000);
    DHT11_DATA = 1;                //总线由上拉电阻拉高 主机延时20us-40us    
    MicroWait(35);
    DHT11_DATA = 1;                //主机转为输入或者输出高电平，DATA线由上拉电阻拉高，准备判断DHT11的响应信号
    P0DIR &= ~0x10;
    if (!DHT11_DATA)                //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行        
    {
      Overtime_counter = 2;   //判断DHT11发出的80us的低电平响应信号是否结束
      while ((!DHT11_DATA)&&Overtime_counter++);
      Overtime_counter=2;   //判断DHT11是否发出80us的高电平，如发出则进入数据接收状态
      while ((DHT11_DATA)&&Overtime_counter++);
      Read_Byte();                //读取湿度值整数部分的高8bit
      RH_data_H_temp = comdata;
      Read_Byte();                //读取湿度值小数部分的低8bit
      RH_data_L_temp = comdata;
      Read_Byte();                //读取温度值整数部分的高8bit
      T_data_H_temp = comdata;
      Read_Byte();                //读取温度值小数部分的低8bit
      T_data_L_temp = comdata;
      Read_Byte();                //读取校验和的8bit
      checkdata_temp = comdata;
      P0DIR |= 0x10;
      DHT11_DATA = 1;                //读完数据将总线拉高
      checksum = (T_data_H_temp + T_data_L_temp + RH_data_H_temp + RH_data_L_temp);//进行数据校验
      if (checksum == checkdata_temp)
        {
          RH_data_H = RH_data_H_temp;//保存湿度的整数部分
          RH_data_L = RH_data_L_temp;//保存湿度的小数部分
          T_data_H  = T_data_H_temp;//保存温度的整数部分
          T_data_L  = T_data_L_temp;//保存温度的小数部分
          checkdata = checkdata_temp;
          *temp = T_data_H;
          *humid = RH_data_H;
          result=0;
        }
      
    }
    return result;
}

void zb_StartConfirm( uint8 status )
{
  
  if(status==ZSUCCESS)
  {    
    halUARTCfg_t uartcfg;
    uartcfg.baudRate=HAL_UART_BR_115200;
    uartcfg.flowControl=FALSE;
    uartcfg.callBackFunc=NULL;
    HalUARTOpen(HAL_UART_PORT_0,&uartcfg);
    HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
    HalLedSet(HAL_LED_2, HAL_LED_MODE_OFF);
    char buf[]="The livingroomNode is successfully added to the network!\r\n";
    HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf));
    zb_SendDataRequest(0X0,SUBNODE_JOIN_NET_CMD_ID,LEDNUM,ledIdList,0,FALSE,AF_DEFAULT_RADIUS);
    osal_start_timerEx(sapi_TaskID,READ_LIVINGROOM_SENSOR_DATA_EVENT,7000);
    osal_start_timerEx(sapi_TaskID,HEART_BEAT_TIMEOUT_EVENT,5000);
  }
}

void zb_HandleOsalEvent( uint16 event )
{
  if(event&READ_LIVINGROOM_SENSOR_DATA_EVENT){//读取DHT11数据事件
    
    uint8 temphumi[2];
    //char buf[30];
    //unsigned int data = Read_DHT11(temphumi,temphumi+1);
    //sprintf(buf,"data = %d\r\n",data);
    //HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf)); 
    if(Read_DHT11(temphumi,temphumi+1)==0)
    {
      char buffer[50];
      sprintf(buffer,"{\"Temperature\":\"%d\",\"Humidity\":\"%d\"}\r\n",*temphumi,*(temphumi+1));
      HalUARTWrite(HAL_UART_PORT_0,buffer,osal_strlen(buffer));
      
      //把读取到的温湿度值发给协调器
      zb_SendDataRequest(0X0,GET_LIVINGROOM_NODE_DATA_CMD_ID,osal_strlen(temphumi),temphumi,0,FALSE,AF_DEFAULT_RADIUS);
      osal_start_timerEx(sapi_TaskID,READ_LIVINGROOM_SENSOR_DATA_EVENT,7000);
    
    }else{
      HalUARTWrite(HAL_UART_PORT_0,"The DTH11 is faulty",osal_strlen("The DTH11 is faulty")); 
      osal_start_timerEx(sapi_TaskID,READ_LIVINGROOM_SENSOR_DATA_EVENT,7000);
    }
  }
  
  if(event&HEART_BEAT_TIMEOUT_EVENT)
  {
    osal_start_timerEx(sapi_TaskID,HEART_BEAT_TIMEOUT_EVENT,5000);
    zb_SendDataRequest(0X0,HEART_BEAT_CMD_ID,0,NULL,0,FALSE,AF_DEFAULT_RADIUS); 
  }
  
}

void zb_FindDeviceConfirm( uint8 searchType, 
                          uint8 *searchKey, uint8 *result )
{
  
}

/***********
执行时机：发送的数据包被接收方收到时被调用
handle:包的编号；
status:ZSUCCESS表示成功接收
************/
void zb_SendDataConfirm( uint8 handle, uint8 status )
{
  
}

/***********
执行时机：接收到的数据包被调用
************/
void zb_ReceiveDataIndication( uint16 source, uint16 command, 
                              uint16 len, uint8 *pData  )
{
  
}


void zb_AllowBindConfirm( uint16 source )
{
}

void zb_HandleKeys( uint8 shift, uint8 keys )
{
  
}

void zb_BindConfirm( uint16 commandId, uint8 status )
{
}
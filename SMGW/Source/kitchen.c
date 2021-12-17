#include "kitchen.h"

unsigned int readAdc(unsigned char channal)
{
  unsigned int value ; 
  APCFG |= 1 << channal ; 
  ADCIF = 0 ;
 
  ADCCON3 = channal;          
  while ( !ADCIF ) ; 
  
  value = ADCL;
  value |= ((unsigned int) ADCH) << 8 ;
  value>>=2;
  
  return value; 
}


//读取MQ2的浓度
uint8 GetMq2(void){
  char buffer[30];
  unsigned int adcValue=0;
  float percentage=0.0;
  float vol =0.0;
  adcValue = readAdc(0);
  vol = (adcValue*1.0/8191.0)*3.3;
  percentage = ((vol-1.2)*100.0)/2.1;
  sprintf(buffer,"adcValue = %d,vol = %.2f,mq2 = %.2f\r\n",adcValue,vol,percentage);
  HalUARTWrite(0,buffer,osal_strlen(buffer));
  
  if(percentage>=10.0&&percentage<=100.0){
     HalLedSet(HAL_LED_1, HAL_LED_MODE_FLASH);
  }else{
     HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
  }
  return (uint8)percentage;
}

//读取MQ7的浓度
uint8 GetMq7(void){
  char buffer[30];
  unsigned int adcValue=0;
  float percentage=0.0;
  float vol =0.0;
  adcValue = readAdc(1);
  vol = (adcValue*1.0/8191.0)*5.0;
  percentage = ((vol-1.9)*100.0)/5.0;
  sprintf(buffer,"adcValue = %d,vol = %.2f, mq7  = %.2f\r\n",adcValue,vol,percentage);
  HalUARTWrite(0,buffer,osal_strlen(buffer));
  
  if(percentage>=10.0&&percentage<=100.0){
     HalLedSet(HAL_LED_2, HAL_LED_MODE_FLASH);
  }else{
     HalLedSet(HAL_LED_2, HAL_LED_MODE_OFF);
  }
  return (uint8)percentage;
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
    char buf[]="The kitchenNode is successfully added to the network!\r\n";
    HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf));
    zb_SendDataRequest(0X0,SUBNODE_JOIN_NET_CMD_ID,LEDNUM,ledIdList,0,FALSE,AF_DEFAULT_RADIUS);
    osal_start_timerEx(sapi_TaskID,READ_KITCHEN_SENSOR_DATA_EVENT,5000);
    osal_start_timerEx(sapi_TaskID,HEART_BEAT_TIMEOUT_EVENT,5000);
  }
}

void zb_HandleOsalEvent( uint16 event )
{
  if(event & READ_KITCHEN_SENSOR_DATA_EVENT)
  {
   
   uint8 sensorData[2]= {0};
   sensorData[0]=GetMq7();
   sensorData[1]=GetMq2();
   
   
   if(sensorData[0]<0||sensorData[0]>=100||sensorData[1]<0||sensorData[1]>=100){
     osal_start_timerEx(sapi_TaskID,READ_KITCHEN_SENSOR_DATA_EVENT,5000);
     return ;
   }
   
   char buffer[100];
   sprintf(buffer,"Carbon = %d,Smoke = %d\r\n",sensorData[0],sensorData[1]);
   HalUARTWrite(0,buffer,osal_strlen(buffer));       
   zb_SendDataRequest(0X0,GET_KITCHEN_NODE_DATA_CMD_ID,osal_strlen(sensorData),sensorData,0,FALSE,AF_DEFAULT_RADIUS); //读取完mq2数据，接着发一个心跳包    
   osal_start_timerEx(sapi_TaskID,READ_KITCHEN_SENSOR_DATA_EVENT,5000);//每四秒读取一次   
  }
  
  
  if(event&HEART_BEAT_TIMEOUT_EVENT)
  {
   zb_SendDataRequest(0X0,HEART_BEAT_CMD_ID,0,NULL,0,FALSE,AF_DEFAULT_RADIUS); 
   osal_start_timerEx(sapi_TaskID,HEART_BEAT_TIMEOUT_EVENT,5000);  
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

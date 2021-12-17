#include "livingRoom.h"

/*****************��DHT11��ȡһ���ֽں���******************/        
void  Read_Byte(void)
{
  uint8 i;
  for (i = 0; i < 8; i++)                     //ѭ��8�Σ���ȡ8bit������
  {
    Overtime_counter = 2;                          //��ȡ���ȴ�DHT11������12-14us�͵�ƽ��ʼ�ź�
    P0DIR &= ~0x10;
    while ((!DHT11_DATA) && Overtime_counter++);
    //Delay_10us(80);                   //26-28us�ĵ͵�ƽ�ж�����
    MicroWait(27);
    bit_value = 0;                          //�������޺��ж������Ǹ߻��ǵͣ���Ϊ1����Ϊ0
    if(DHT11_DATA)
    bit_value = 1;
    Overtime_counter=2;                          //�ȴ�1bit�ĵ�ƽ�źŽ�����������0��1��118us�󶼱�Ϊ�͵�ƽ���������ʱ
    while (DHT11_DATA && Overtime_counter++);  //��U8FLAG�ӵ�255�����Ϊ0������ѭ��������Ӽ�Ϊ1
    if (Overtime_counter == 1)
      break;                           //��ʱ������forѭ��        
    comdata <<= 1;                      //����1λ��LSB��0
    comdata |= bit_value;                  //LSB��ֵ
  }
}

/*****************DHT11��ȡ����ֽں���******************/
/*
������������ȡdht11����ʪ��
����˵����
    *temp�������¶ȵ���������
    *humid������ʪ�ȵ���������
����ֵ��
  0���ɹ���ȡ
  <0����ȡʧ��
*/
int Read_DHT11(unsigned char *temp,unsigned char *humid)
{
    int result=-1;
    uint8 checksum;
    P0DIR |= 0x10;
    DHT11_DATA = 0;                //��������18ms
    MicroWait(18000);
    DHT11_DATA = 1;                //������������������ ������ʱ20us-40us    
    MicroWait(35);
    DHT11_DATA = 1;                //����תΪ�����������ߵ�ƽ��DATA���������������ߣ�׼���ж�DHT11����Ӧ�ź�
    P0DIR &= ~0x10;
    if (!DHT11_DATA)                //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������        
    {
      Overtime_counter = 2;   //�ж�DHT11������80us�ĵ͵�ƽ��Ӧ�ź��Ƿ����
      while ((!DHT11_DATA)&&Overtime_counter++);
      Overtime_counter=2;   //�ж�DHT11�Ƿ񷢳�80us�ĸߵ�ƽ���緢����������ݽ���״̬
      while ((DHT11_DATA)&&Overtime_counter++);
      Read_Byte();                //��ȡʪ��ֵ�������ֵĸ�8bit
      RH_data_H_temp = comdata;
      Read_Byte();                //��ȡʪ��ֵС�����ֵĵ�8bit
      RH_data_L_temp = comdata;
      Read_Byte();                //��ȡ�¶�ֵ�������ֵĸ�8bit
      T_data_H_temp = comdata;
      Read_Byte();                //��ȡ�¶�ֵС�����ֵĵ�8bit
      T_data_L_temp = comdata;
      Read_Byte();                //��ȡУ��͵�8bit
      checkdata_temp = comdata;
      P0DIR |= 0x10;
      DHT11_DATA = 1;                //�������ݽ���������
      checksum = (T_data_H_temp + T_data_L_temp + RH_data_H_temp + RH_data_L_temp);//��������У��
      if (checksum == checkdata_temp)
        {
          RH_data_H = RH_data_H_temp;//����ʪ�ȵ���������
          RH_data_L = RH_data_L_temp;//����ʪ�ȵ�С������
          T_data_H  = T_data_H_temp;//�����¶ȵ���������
          T_data_L  = T_data_L_temp;//�����¶ȵ�С������
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
  if(event&READ_LIVINGROOM_SENSOR_DATA_EVENT){//��ȡDHT11�����¼�
    
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
      
      //�Ѷ�ȡ������ʪ��ֵ����Э����
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
ִ��ʱ�������͵����ݰ������շ��յ�ʱ������
handle:���ı�ţ�
status:ZSUCCESS��ʾ�ɹ�����
************/
void zb_SendDataConfirm( uint8 handle, uint8 status )
{
  
}

/***********
ִ��ʱ�������յ������ݰ�������
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
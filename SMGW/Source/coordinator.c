#include "coordinator.h"
static struct Sub_Device_Node subDeviceHeader={NULL,0,0,0,0,0};

void *allocSub_Device_Node(uint8 lednum)
{
  return osal_mem_alloc(sizeof(struct Sub_Device_Node)-1+lednum);
}
//Ϊsimple API�����������
const SimpleDescriptionFormat_t zb_SimpleDesc=
{
  ENDPOINT_ID_SMARTHOME,
  PROFILE_ID_SMARTHOME,
  DEVICE_ID_COORDINATOR,
  DEVIDE_VERSION_ID,
  0,
  NUM_IN_CMD_COORINATOR,
  (cId_t*)coordinatorInputCommandList,
  NUM_OUT_CMD_COORINATOR,
  (cId_t*)coordinatorOutputCommandList  
};



//������������������ɹ�ʱ������
void zb_StartConfirm( uint8 status )
{
  halUARTCfg_t uartcfg;
  uartcfg.baudRate=HAL_UART_BR_115200;
  uartcfg.flowControl=FALSE;
  uartcfg.callBackFunc=uart_receive;
  HalUARTOpen(HAL_UART_PORT_0,&uartcfg);
  HalLedSet(HAL_LED_1, HAL_LED_MODE_OFF);
  HalLedSet(HAL_LED_2, HAL_LED_MODE_OFF);
  if(status==ZSUCCESS) 
  {
    char buf[]="ZigBee Net is created successfully!\r\n";
    HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf));
    
  }  
}

//���������û����Զ����¼�
void zb_HandleOsalEvent(uint16 event)
{
  if(event&HEART_BEAT_TIMEOUT_EVENT){
    struct Sub_Device_Node *p=subDeviceHeader.next;
    struct Sub_Device_Node *pre=&subDeviceHeader;   
    while(p!=NULL){//�жϽڵ��Ƿ����
      p->lostHeartCount--;//��������һ
      char buf[20];
      //sprintf(buf,"lostHeartCount=%d\r\n",p->lostHeartCount);
      //HalUARTWrite(0,buf,osal_strlen(buf));
      if(p->lostHeartCount<=0){
         sprintf(buf,"{\"offline\":\"%u\"}",p->shortAddr);
         HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf));
         HalUARTWrite(HAL_UART_PORT_0,"\r\n",2);
         pre->next=p->next;
         p=p->next;
         
         continue;
      }
      pre=p;
      p=p->next;
    }        
  }
  osal_start_timerEx(sapi_TaskID,HEART_BEAT_TIMEOUT_EVENT,1000);
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
ִ��ʱ�������յ����ݰ�ʱ������
************/
void zb_ReceiveDataIndication( uint16 source, uint16 command, uint16 len, uint8 *pData  ){
  char buf[100];
  if(command==SUBNODE_JOIN_NET_CMD_ID){
    struct Sub_Device_Node *p=subDeviceHeader.next;
      while(p!=NULL){
        // if( osal_memcmp(pData,p->ledId,len)==TRUE)
        //   break;
        // else
        // {
          p=p->next;
        //}
      }
      if(p==NULL){//�½ڵ����
        struct Sub_Device_Node *newDevice=(struct Sub_Device_Node *)allocSub_Device_Node(len);
        osal_memcpy(&newDevice->shortAddr,&source,2);
        newDevice->ledNum=len;
        osal_memcpy(&newDevice->nodeType,pData,1); 
        osal_memcpy(&newDevice->ledStatus,pData+1,1); 
        newDevice->next=subDeviceHeader.next;//ͷ��
        subDeviceHeader.next=newDevice;
        p=newDevice;
        sprintf(buf,"nodeType=:%u, ledStatus=:%u\r\n",newDevice->nodeType,newDevice->ledStatus);
        HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf));
        if(HEART_BEAT_FLAG){
          HEART_BEAT_FLAG = 0;
          osal_start_timerEx(sapi_TaskID,HEART_BEAT_TIMEOUT_EVENT,1000);
        }
      }
      // else{
      //   osal_memcpy(p->shortAddr,&source,2);
      // }
      sprintf(buf,"{\"online\":\"%u\"}",(uint16)p->shortAddr);
      HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf));
      //for(i=0;i<p->ledNum;i++)
      //{
     //   sprintf(buf,"%u  ",p->ledId[i]);
      //  HalUARTWrite(0,buf,osal_strlen(buf));
     // }
     HalUARTWrite(HAL_UART_PORT_0,"\r\n",2);

  }else if(command==HEART_BEAT_CMD_ID) {//�յ��ն˽ڵ��������
      struct Sub_Device_Node *p=subDeviceHeader.next;
      while(p!=NULL)
      {
        if( osal_memcmp(&source,&p->shortAddr,2)==TRUE)
          break;
        else{
          p=p->next;
        }
      } 
      if(p!=NULL){
        p->lostHeartCount=HEART_BEAT_MAX_COUNT;//������������ֵ
      }
  }else if(command==GET_KITCHEN_NODE_DATA_CMD_ID){

    sprintf(buf,"{\"type\":\"kitchen\",\"address\":\"%u\",\"Carbon\":%d,\"Smoke\":%d}\r\n",source,pData[0],pData[1]);
    HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf));
    //HalUARTWrite(HAL_UART_PORT_0,"\r\n",2);
  }else if(command==GET_LIVINGROOM_NODE_DATA_CMD_ID){
    sprintf(buf,"{\"type\":\"living\",\"address\":\"%u\",\"Temperature\":%d,\"Humidity\":%d}\r\n",source,pData[0],pData[1]);
    HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf));
    //HalUARTWrite(HAL_UART_PORT_0,"\r\n",2);
  
  }
  
  
}

//�û�����ͨ��zb_FindDeviceRequestͨ���ڵ�������ַ��ȡ�ڵ�������ַʱ�ĵ��� 
void zb_FindDeviceConfirm( uint8 searchType, 
                          uint8 *searchKey, uint8 *result )
{
  
}

void uart_receive(uint8 port,uint8 event){
  //uint16 dstAddr;
  char buf[50];

  if(event& (HAL_UART_RX_FULL|HAL_UART_RX_ABOUT_FULL|HAL_UART_RX_TIMEOUT))
  {
    //struct Sub_Device_Node *p=subDeviceHeader.next;
    osal_memset(buf, 0, sizeof(buf+1));
    HalUARTRead(port,buf,50);
    HalUARTWrite(HAL_UART_PORT_0,buf,osal_strlen(buf));
    
    
    
    
      //while(p!=NULL)
      //{
      //  if( osal_memcmp(&source,p->shortAddr,2)==TRUE)
      //    break;
      //  else{
      //    p=p->next;
      //  }
      //} 
      //if(p!=NULL){
      //  p->lostHeartCount=HEART_BEAT_MAX_COUNT;//������������ֵ
      //}
  }  
}



//�����ڵ�󶨵��ýڵ�ʱ����
void zb_AllowBindConfirm( uint16 source )
{
  
}

//������������Ϣ
void zb_HandleKeys( uint8 shift, uint8 keys )
{
}

void zb_BindConfirm( uint16 commandId, uint8 status )
{
}



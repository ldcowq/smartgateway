#ifndef __LIVINGROOM_H
#define __LIVINGROOM_H

#include "sapi.h"
#include "hal_led.h"
#include"onBoard.h"
#include "hal_uart.h"
#include "OSAL.h"
#include "stdio.h"
#include "smartHome.h"

#define  DHT11_DATA  P0_4

#define LIVINGROOM_TYPE 2
#define LED_STATUS 1
#define LEDNUM  2


#define NUM_IN_CMD_LIVINGROOM_DEVICE 6
#define NUM_OUT_CMD_LIVINGROOM_DEVICE 3 

uint8 ledIdList[LEDNUM]={LIVINGROOM_TYPE,LED1_AND_LED2_CLOSE};

const cId_t livingRoomDeviceInputCommandList[NUM_IN_CMD_LIVINGROOM_DEVICE]=
{  
 CLOSE_LIVING_LED1_CMD_ID,
 CLOSE_LIVING_LED2_CMD_ID,

 OPEN_LIVING_LED1_CMD_ID,
 OPEN_LIVING_LED2_CMD_ID,

 FLASH_LIVING_LED1_CMD_ID, 
 FLASH_LIVING_LED2_CMD_ID 
};
const cId_t livingRoomDeviceOutputCommandList[NUM_OUT_CMD_LIVINGROOM_DEVICE]=
{  
    SUBNODE_JOIN_NET_CMD_ID,
    GET_LIVINGROOM_NODE_DATA_CMD_ID,
    HEART_BEAT_CMD_ID
};
const SimpleDescriptionFormat_t zb_SimpleDesc=
{
  ENDPOINT_ID_SMARTHOME,
  PROFILE_ID_SMARTHOME,
  DEVICE_ID_LEDDEVICE,
  DEVIDE_VERSION_ID,
  0,
  NUM_IN_CMD_LIVINGROOM_DEVICE,
  (cId_t*)livingRoomDeviceInputCommandList,
  NUM_OUT_CMD_LIVINGROOM_DEVICE,
  (cId_t*)livingRoomDeviceOutputCommandList  
};

//*****************ȫ�ֱ����Ķ���******************/
uint8  Overtime_counter;  //�жϵȴ��Ƿ�ʱ�ļ�����������uchar�͵���ֵ��Χ�����Զ���ʱ���ƣ�ʱ���ɳ�ֵ�����������ж��Ƿ�ʱ
uint8  bit_value;          //��DATA�����϶�����λֵ
uint8  T_data_H, T_data_L, RH_data_H, RH_data_L, checkdata;//У������¶ȸ�8λ,�¶ȵ�8λ,ʪ�ȸ�8λ,ʪ�ȵ�8λ,У���8λ
uint8  T_data_H_temp, T_data_L_temp, RH_data_H_temp, RH_data_L_temp, checkdata_temp;//δ��У�������
uint8  comdata;            //��DHT11��ȡ��һ���ֽڵ�����


void Read_Byte(void);
int Read_DHT11(unsigned char *temp,unsigned char *humid);

#endif
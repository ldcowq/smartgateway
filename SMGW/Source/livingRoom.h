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

//*****************全局变量的定义******************/
uint8  Overtime_counter;  //判断等待是否超时的计数器。利用uchar型的数值范围进行自动延时控制（时长由初值决定），并判断是否超时
uint8  bit_value;          //从DATA总线上读到的位值
uint8  T_data_H, T_data_L, RH_data_H, RH_data_L, checkdata;//校验过的温度高8位,温度低8位,湿度高8位,湿度低8位,校验和8位
uint8  T_data_H_temp, T_data_L_temp, RH_data_H_temp, RH_data_L_temp, checkdata_temp;//未经校验的数据
uint8  comdata;            //从DHT11读取的一个字节的数据


void Read_Byte(void);
int Read_DHT11(unsigned char *temp,unsigned char *humid);

#endif
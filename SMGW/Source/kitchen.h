#ifndef __KITCHEN_H
#define __KITCHEN_H

#include "smartHome.h"
#include "sapi.h"
#include "hal_led.h"
#include "onBoard.h"
#include "hal_uart.h"
#include "hal_adc.h"
#include "stdio.h"

#define KITCHEN_TYPE 1
#define LED_STATUS 1
#define LEDNUM  2


#define NUM_IN_CMD_LEDDEVICE 6
#define NUM_OUT_CMD_LEDDEVICE 3 

uint8 ledIdList[LEDNUM]={KITCHEN_TYPE,LED1_AND_LED2_CLOSE};

const cId_t kitchenDeviceInputCommandList[NUM_IN_CMD_LEDDEVICE]=
{
 CLOSE_KITCHEN_LED1_CMD_ID,
 CLOSE_KITCHEN_LED2_CMD_ID,
 OPEN_KITCHEN_LED1_CMD_ID,
 OPEN_KITCHEN_LED2_CMD_ID,
 FLASH_KITCHEN_LED1_CMD_ID,
 FLASH_KITCHEN_LED2_CMD_ID
};
const cId_t kitchenDeviceOutputCommandList[NUM_OUT_CMD_LEDDEVICE]=
{
  SUBNODE_JOIN_NET_CMD_ID,
  GET_KITCHEN_NODE_DATA_CMD_ID,
  HEART_BEAT_CMD_ID
};
const SimpleDescriptionFormat_t zb_SimpleDesc=
{
  ENDPOINT_ID_SMARTHOME,
  PROFILE_ID_SMARTHOME,
  DEVICE_ID_LEDDEVICE,
  DEVIDE_VERSION_ID,
  0,
  NUM_IN_CMD_LEDDEVICE,
  (cId_t*)kitchenDeviceInputCommandList,
  NUM_OUT_CMD_LEDDEVICE,
  (cId_t*)kitchenDeviceOutputCommandList  
};
//void Init_ADC(void);
uint8 GetMq2(void);
uint8 GetMq7(void);
unsigned int readAdc(unsigned char channal);


#endif
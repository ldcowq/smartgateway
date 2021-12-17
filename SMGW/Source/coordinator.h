#ifndef __COORDINATOR_H
#define __COORDINATOR_H

#include "smartHome.h"
#include "sapi.h"
#include "osal.h"
#include "hal_uart.h"
#include "hal_led.h"
#include "stdio.h"

#define NUM_IN_CMD_COORINATOR 4
#define NUM_OUT_CMD_COORINATOR 12


uint8 HEART_BEAT_FLAG = 1;
void *allocSub_Device_Node(uint8 lednum);//给节点分配内存空�?void uart_receive(uint8 port,uint8 event);//协调器串口接收到消息的回调函�?
/****************协调器的输入命令*********************/
const cId_t coordinatorInputCommandList[NUM_IN_CMD_COORINATOR]=
{
  SUBNODE_JOIN_NET_CMD_ID,
  GET_KITCHEN_NODE_DATA_CMD_ID,  
  GET_LIVINGROOM_NODE_DATA_CMD_ID,  
  HEART_BEAT_CMD_ID
};

/****************协调器的输出命令*********************/
const cId_t coordinatorOutputCommandList[NUM_OUT_CMD_COORINATOR]=
{
 CLOSE_KITCHEN_LED1_CMD_ID,
 CLOSE_KITCHEN_LED2_CMD_ID,
 OPEN_KITCHEN_LED1_CMD_ID,
 OPEN_KITCHEN_LED2_CMD_ID,
 FLASH_KITCHEN_LED1_CMD_ID,
 FLASH_KITCHEN_LED2_CMD_ID,
 
 CLOSE_LIVING_LED1_CMD_ID,
 CLOSE_LIVING_LED2_CMD_ID,
 OPEN_LIVING_LED1_CMD_ID,
 OPEN_LIVING_LED2_CMD_ID,
 FLASH_LIVING_LED1_CMD_ID, 
 FLASH_LIVING_LED2_CMD_ID 
};
struct Sub_Device_Node
{
  struct Sub_Device_Node *next;
  uint16 shortAddr;
  uint8 lostHeartCount;
  uint8 ledNum;
  uint8 nodeType;
  uint8 ledStatus;
};

void uart_receive(uint8 port,uint8 event);

#endif
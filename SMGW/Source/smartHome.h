#ifndef __SMARTHOME_H_
#define __SMARTHOME_H_
#define ENDPOINT_ID_SMARTHOME 0X01
#define PROFILE_ID_SMARTHOME 0X501
#define DEVICE_ID_COORDINATOR 0X01
#define DEVICE_ID_LEDDEVICE 0X02
#define DEVIDE_VERSION_ID 0X0

#define SUBNODE_JOIN_NET_CMD_ID  0X1
#define GET_KITCHEN_NODE_DATA_CMD_ID  0X2
#define GET_LIVINGROOM_NODE_DATA_CMD_ID  0X3
#define HEART_BEAT_CMD_ID  0X4
#define HEART_BEAT_MAX_COUNT 10

#define HEART_BEAT_TIMEOUT_EVENT 0X01
#define READ_KITCHEN_SENSOR_DATA_EVENT 0X02
#define READ_LIVINGROOM_SENSOR_DATA_EVENT 0X03

#define CLOSE_KITCHEN_LED1_CMD_ID 0x1
#define CLOSE_KITCHEN_LED2_CMD_ID 0x2

#define OPEN_KITCHEN_LED1_CMD_ID 0x3
#define OPEN_KITCHEN_LED2_CMD_ID 0x4

#define FLASH_KITCHEN_LED1_CMD_ID 0x5
#define FLASH_KITCHEN_LED2_CMD_ID 0x6




#define CLOSE_LIVING_LED1_CMD_ID 0x7
#define CLOSE_LIVING_LED2_CMD_ID 0x8

#define OPEN_LIVING_LED1_CMD_ID 0x9
#define OPEN_LIVING_LED2_CMD_ID 0xa

#define FLASH_LIVING_LED1_CMD_ID 0xb
#define FLASH_LIVING_LED2_CMD_ID 0xc

#endif
# SmartGateway_Base_on_QT

## 一、前言
2022年6月18日的一场毕业典礼，意识到自己真的要离开学校了，真的要和四年的舍友说拜拜了，真的是最后一次在学校打篮球了，马上奔赴人生的下一个战场，多少有点不舍。

想用这篇博客简单记录一下大学四年努力学习的成果，四年的时光里，承认虚度过光阴，但也承认有在认真的努力学习。

一个在大学才拥有自己第一台笔记本电脑的计算机菜鸟，毕业设计能做得有多烂呢？

演示视频：[https://www.bilibili.com/video/BV1Ft4y187zu/](https://www.bilibili.com/video/BV1Ft4y187zu/)

## 二、系统总体架构设计
系统总体架构如下图所示，浅说一下整个系统的结构和通信链路吧，整个系统主要分为三层：

 1. 底层：使用支持ZigBee协议的子设备负责采集和传输传感器的数据，并且负责控制该子设备自身的一下执行器（灯、蜂鸣器），一个协调器负责从ZigBee网络收集两个终端节点采集到的数据，然后协调器通过UART与上层的网关进行通信。
 2. 网络层：该层的核心设备使树莓派网关，给网关配了一块触控屏，外接了两个摄像头，这里的网关不仅仅是完成不同协议间的数据转换，还有更多的与人交互的功能。当然了，网关还得接入路由器。
 3. 应用层：主要是手机APP，实现一些远程控制和查看数据的功能，云端服务器作为一个数据中转和存储的角色。
![在这里插入图片描述](https://img-blog.csdnimg.cn/232c870e24704f52a0e3752e310a3f4f.png)
## 三、硬件接线参考图
![在这里插入图片描述](https://img-blog.csdnimg.cn/445e603e66264e0a85bae5eb3a3e986c.png)
## 四、ZigBee心跳包原理实现
原理描述：心跳包技术是一种用于检测子设备是否在线的常用技术，在本系统中，ZigBee协调器负责构建ZigBee网络，当ZigBee终端节点加入网络成功后，协调器就会给当前的终端节点的心跳值定时减一，而终端节点则会定时发送一个心跳包给协调器，当协调器收到终端节点的心跳包之后，则会把当前终端节点心跳值恢复到最大值，代表终端节点当前是在线的状态，反之就是离线状态。

本系统心跳包功能没有在视频中演示，后面有截图展示。具体效果是，关闭某个ZigBee节点后，在环境与控制模块中，就不能操作该节点的执行器（例如不能开灯）图标旁边也会有离线的字眼提醒。本系统心跳包实现的参考图：
![在这里插入图片描述](https://img-blog.csdnimg.cn/b7b0968f86c643168562f56beeaaba44.png)

```c
核心代码：
void zb_StartConfirm( uint8 status ) //加入ZigBee网络成功时调用
{
  if(status==ZSUCCESS) 
  {    
	  //发送加入网络的请求命令通知协调器
zb_SendDataRequest(0X0,SUBNODE_JOIN_NET_CMD_ID,
osal_strlen(deviceI),deviceID,0,FALSE,AF_DEFAULT_RADIUS);

//发送心跳包
     osal_start_timerEx(sapi_TaskID,HEART_BEAT_TIMEOUT_EVENT,1000);
  }
}


void zb_HandleOsalEvent( uint16 event )//处理用户自定义事件
{
if(event&READ_SENSOR_DATA_EVENT) //处理读取DHT11数据事件
{ 
uint8 temphumi[2];
if(Read_DHT11(temphumi,temphumi+1)==0)
{      
//发送传感器数据包
zb_SendDataRequest(0X0,GET_LIVINGROOM_NODE_DATA_CMD_ID,
osal_strlen(temphumi),temphumi,0,FALSE,AF_DEFAULT_RADIUS);

//定时3s触发心跳包发送事件
osal_start_timerEx(sapi_TaskID,HEART_BEAT_TIMEOUT_EVENT,3000);
		}
}

if(event&HEART_BEAT_TIMEOUT_EVENT)//处理心跳包事件
{    
//发送心跳包
zb_SendDataRequest(0X0,HEART_BEAT_CMD_ID,0,NULL,0,FALSE,AF_DEFAULT_RADIUS); 

//定时3s触发传感器发送事件
osal_start_timerEx(sapi_TaskID,READ_SENSOR_DATA_EVENT,3000);
}
}
```

## 五、传感器数据传输链路
[外链图片转存失败,源站可能有防!在这里插入盗链机制,建描述]议将图片上https://传(imblog.csdnimg.cn/ffbc77bdeGFHV54a05bff4b106bf57a59.png81(https:/`在这里插入代码片`/img-blog.csdnimg.cn/ffbc77bdc3454a05bff4b106bf157a59.png)]
云端服务器中，数据流转的相关细节如下图所示，在Tomcat中部署的Web API是使用Java编写的一个servlet后台程序，如果MQTT代理服务器支出数据直接流转到数据库则可以省略此步骤。
![在这里插入图片描述](https://img-blog.csdnimg.cn/82229f48db4048b78e7187fecdfcef03.png)

## 六、系统测试截图
**1、时钟和天气模块：** 如果使用GEC6818开发板，获取时钟信息需要移植一个NTP服务，可以参考这位大佬的文章：[https://blog.csdn.net/qq_41248872/article/details/83622146](https://blog.csdn.net/qq_41248872/article/details/83622146)
```
ntpclient -s -d -c 1 -i 5 -h 111.230.50.201    //板子获取网络时间
```
天气模块的信息从一开始的手动获取，到后面改为了上电自动获取。源码里有两个免费的API接口，一个可用于定位当前网络IP的归属地，另一个接口则是利用该区域名称获取该地区的天气信息。

![在这里插入图片描述](https://img-blog.csdnimg.cn/d4f42dd1824f4520b340c16ebd56006f.png)

**2、视频监控和播放器模块：** 这里踩过一些坑，本以为QT的QMultiMedia（低版本的QT库没有该模块，需要自己编译移植）模块支持视频服务的，后面查了很多文章发现，仅支持对摄像头模块采集的画面进行截图而已。在指导老师的帮助下，最后采用opencv来获取视频流并显示到屏幕上。此时，使用的是树莓派来开发，安装opencv库都比较简单方便，如果还是用之前的GEC6818开发板，需要自己交叉编译opencv库，并移植上去。

![在这里插入图片描述](https://img-blog.csdnimg.cn/cc8e42bba48e4d56aa9c476c80f8f756.png)

视频播放器模块也是直接使用opencv库来做的，就是简单直接播放一个视频。一般视频都会用一些编解码的框架来处理，这一块实在太难了，只能替代一下，实现功能够了。之前也试过移植一个播放器来播放。

![在这里插入图片描述](https://img-blog.csdnimg.cn/93866fd01d544c85b43670a3d62c413f.png)

**3、音乐播放器模块：** 这里好像是移植了一个mplayer播放器来实现的，只要调用一些接口，就能实现暂停、播放、切割都功能，其实最难得是进度条的开发，包括视频播放器的进度条也一样，需要考虑的情况挺多的，而且还要实现拖动变化，点击变化等操作。

![在这里插入图片描述](https://img-blog.csdnimg.cn/9f610de0cead41048349d3ca5c3091ae.png)

**4、电子相册模块：** 这一个功能就比较简单了，纯逻辑的一个模块，拿到路径中的图片，放到列表里，随意控制即可。

![在这里插入图片描述](https://img-blog.csdnimg.cn/bcc75a1ef1b14df1a018ca70b7620050.png)

**5、环境与控制模块：** 这是整个系统中最难开发的一个功能了，首先从串口拿到数据，实时显示数据，并做成图表来查看数据的走势，然后就是控制部分了。例如，假设现在所有的节点都在线，点击其中一个节点的开灯按钮，网关会通过串口给ZigBee协调器发送开灯指令，这条指令包括了，要发送给哪个节点，操作的是这个节点上的哪个执行器，该执行器的状态要切换成什么，等这些信息。倘若是手机端的远程控制，则网关还要监听MQTT代理服务器发送过来的指令。

![在这里插入图片描述](https://img-blog.csdnimg.cn/02ec7fefc24544a48b333ef05823be33.png)

**6、手机端功能展示：** 远程控制是通过MQTT协议来实现的，和网关上的触控操作是一样的。历史数据下拉页面即可获取到最新的数据，原理是通过http协议访问WebAPI，按理说这种数据应该要做成按日期查询的，奈何安卓太难了。
![在这里插入图片描述](https://img-blog.csdnimg.cn/be2e085185b34458b9a6252c78b1809c.png)

## 七、总结
以上就是我的毕业设计的大概描述，大家也看得出来，我是很简单的描述了几句而已，确实没时间描述太详细，本人也才疏学浅，专业术语懂的也不多，我的作品也没有拿到优，可见，计算机行业有多卷。

如果有人问，大学四年学到的东西对你现在工作有什么帮助呢？
我会说，学了四年的计算机，对现在的工作有帮助的地方就是调试的能力，因为通常代码是写出来了，明明逻辑也没问题，但效果就是和你预期的不一样，另外调试就是一直在熬，挺考验耐心的。

工作之后接触到的技术完全和学校学的东西不一样了，在学校学到的技术和自己自学的技术，所做出来的作品都几乎开源了，而且这个毕业设计也几乎用上了我所学到的所有技术了。

开源也是为了更好奔赴人生的下一个战场，学习某个行业的全新技术，现在总算体会到了，人生的每一个阶段只会越来越难。

最后，感谢所有帮助过我的同学、老师和CSDN上的网友们，谢谢！！

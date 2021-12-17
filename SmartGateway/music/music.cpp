#include "music.h"

Music::Music(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0,0,800,480);
    this->show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    move(200,200);
    layoutInit();

    connect(songListWidget,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *item){
        currentMusic=item;
        myProcess->close();
#ifdef LINUX
        cmd = QString("madplay /mnt/sd/music/%1").arg(item->text());//－quiet不要输出冗余信息
#else
        cmd = QString("D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/music/music/%1").arg(item->text());//－quiet不要输出冗余信息
#endif
        qDebug()<<cmd;
        myProcess->start(cmd);
    });

    connect(songListWidget,&QListWidget::itemClicked,[=](QListWidgetItem *item){
#ifdef LINUX
        cmd = QString("madplay /mnt/sd/music/%1").arg(item->text());//－quiet不要输出冗余信息，-slave就是用后台命令控制
#else
        cmd = QString("D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/music/music/%1").arg(item->text());//－quiet不要输出冗余信息
#endif
        qDebug()<<cmd;
    });
}

void Music::layoutInit()
{
    mainWidget = new QWidget(this);
    mainWidget->setGeometry(0,0,800,480);
    mainWidget->show();
    mainWidget->setObjectName("music");
#ifdef LINUX
        mainWidget->setStyleSheet("#music{border-image:url(/mnt/sd/image/4.jpg)}");
#else
        mainWidget->setStyleSheet("#music{border-image:url(D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/album/pictures/1.jpg)}");//－quiet不要输出冗余信息
#endif


    myProcess = new QProcess(mainWidget);//给进程分配内存

    songListWidget = new QListWidget(mainWidget);
    songListWidget->setGeometry(600,0,200,480);
    songListWidget->show();
    songListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭水平滚动条
    songListWidget->setFrameShape(QListWidget::NoFrame);//去除边框
    songListWidget->setStyleSheet("background-color:transparent");// 透明背景
#ifdef LINUX
        fileList = FileTools::getFileNames("/mnt/sd/music/",&musicCount);
#else
        fileList = FileTools::getFileNames("D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/music/music/",&musicCount);
#endif

    if(fileList.isEmpty()){
        qDebug()<<"路径不存在！";
        return ;
    }
    //遍历文件列表，添加到列表显示窗口
    for(int i=0;i<fileList.size();i++)
    {
        qDebug()<<fileList.at(i)<<endl;
        songListWidget->addItem(fileList.at(i));
    }

    playMusicPushButton = new  QPushButton("播放",mainWidget);
    playMusicPushButton->setGeometry(100,440,50,30);
    playMusicPushButton->show();
    connect(playMusicPushButton,&QPushButton::clicked,mainWidget,[=](){
        //system("killall -STOP mpalyer");
        if(myProcess->state()==QProcess::Running)//如果播放器在运行，则从头开始播放
        {
            myProcess->write("pause\n");
            playMusicPushButton->setText("播放");
        }else
        {
            myProcess->close();
            currentMusic = songListWidget->item(0);//如果用户没有选择播放那一首，默认播放第一首
            if(cmd.isNull()){
            //cmd = QString("madplay /mnt/sd/music/%1").arg(currentItem->text());
#ifdef LINUX
        cmd = QString("madplay /mnt/sd/music/%1").arg(currentMusic->text());//－quiet不要输出冗余信息
#else
        cmd = QString("madplay D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/music/music/%1").arg(currentMusic->text());//－quiet不要输出冗余信息
#endif
            }
            myProcess->start(cmd);
            playMusicPushButton->setText("暂停");
        }
    });

    lastMusicPushButton= new  QPushButton("上一首",mainWidget);
    lastMusicPushButton->setGeometry(200,440,50,30);
    lastMusicPushButton->show();
    connect(lastMusicPushButton,&QPushButton::clicked,mainWidget,[=](){
        myProcess->close();
        int nextItemIndex = songListWidget->row(currentMusic);//获取当前播放或者选中列表的歌曲行号
        if(nextItemIndex==0) nextItemIndex=songListWidget->count();//判断是否已经是第一首
        nextItemIndex--;//第一首的上一首是最后一首
        currentMusic = songListWidget->item(nextItemIndex);//根据索引获取上一首的音乐
        currentMusic->setSelected(true);//选中
#ifdef LINUX
        cmd = QString("madplay /mnt/sd/music/%1").arg(currentMusic->text());//－quiet不要输出冗余信息
#else
        cmd = QString("madplay D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/music/music/%1").arg(currentMusic->text());//－quiet不要输出冗余信息
#endif

        qDebug()<<songListWidget->count()<<nextItemIndex;
        myProcess->start(cmd);//播放
    });

    nextMusicPushButton= new  QPushButton("下一首",mainWidget);
    nextMusicPushButton->setGeometry(300,440,50,30);
    nextMusicPushButton->show();
    connect(nextMusicPushButton,&QPushButton::clicked,mainWidget,[=](){
        myProcess->close();
        int nextItemIndex = songListWidget->row(currentMusic);
        nextItemIndex++;
        if(nextItemIndex==songListWidget->count()) nextItemIndex=0;
        currentMusic = songListWidget->item(nextItemIndex);//根据索引获取下一个item
        currentMusic->setSelected(true);
#ifdef LINUX
        cmd = QString("madplay /mnt/sd/music/%1").arg(currentMusic->text());//－quiet不要输出冗余信息
#else
        cmd = QString("madplay D:/developer_tool_install/qt5.9.1/qtProjects/SmartGateway/music/music/%1").arg(currentMusic->text());//－quiet不要输出冗余信息
#endif

        qDebug()<<songListWidget->count()<<nextItemIndex;
        myProcess->start(cmd);
    });

    exitPushButton= new  QPushButton("退出",mainWidget);
    exitPushButton->setGeometry(500,440,50,30);
    exitPushButton->show();
    connect(exitPushButton,&QPushButton::clicked,mainWidget,[=](){
        myProcess->close();
        this->close();
    });

    volumePushButton= new QPushButton(mainWidget);//音量按钮


}

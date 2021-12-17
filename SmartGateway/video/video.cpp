#include "video.h"
//#include <QMediaPlayer>
//#include <QMediaPlaylist>
//#include <QVideoWidget>
Video::Video(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0,0,800,480);
    this->show();
    move(200,200);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    layoutInit();
    //    mediaPlayer = new QMediaPlayer(mainWidget);
    //    mediaPlayerList = new QMediaPlaylist(mainWidget);
    //    videoWidget = new QVideoWidget(label);
    //    videoWidget->resize(label->size());

    //    //设置播放器的播放队列
    //    mediaPlayer->setPlaylist(mediaPlayerList);
    //    //设置播放器的显示窗口
    //    mediaPlayer->setVideoOutput(videoWidget);

    connect(playList,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *item){
        currentItem=item;
        myProcess->close();
        cmd = QString("mplayer -zoom -x 600 -y 450 -slave -quiet /mnt/sd/video/%1").arg(item->text());
        //cmd = QString("mplayer -zoom -x 600 -y 450 -slave -quiet /home/ldc/daily/video/%1").arg(item->text());//－quiet不要输出冗余信息
        qDebug()<<cmd;
        myProcess->start(cmd);
    });

    connect(playList,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        cmd = QString("mplayer -zoom -x 600 -y 450 -slave -quiet /mnt/sd/video/%1").arg(item->text());
        //cmd = QString("mplayer -zoom -x 600 -y 450 -slave -quiet /home/ldc/daily/video/%1").arg(item->text());//－quiet不要输出冗余信息，-slave就是用后台命令控制
        qDebug()<<cmd;
    });

}
void Video::layoutInit()
{

    mainWidget = new QWidget(this);
    mainWidget->show();
    mainWidget->setObjectName("mainWidget");
    mainWidget->setGeometry(0,0,800,480);
    mainWidget->setFixedSize(800,480);
    mainWidget->setStyleSheet("#mainWidget{border-image:url(/home/ldc/daily/image/4.jpg)}");
    //mainWidget->setStyleSheet("#mainWidget{border-image:url(/home/ldc/daily/image/4.jpg)}");

    myProcess = new QProcess(mainWidget);//给进程分配内存

    playList = new QListWidget(mainWidget);
    playList->setGeometry(600,0,200,480);
    playList->show();
    playList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭水平滚动条
    playList->setFrameShape(QListWidget::NoFrame);//去除边框
    playList->setStyleSheet("background-color:transparent");// 透明背景
    //fileList = FileTools::getFileNames("/home/ldc/daily/video/",&videoCount);//获取制定目录下的所有视频绝对路径
    fileList = FileTools::getFileNames("/mnt/sd/video/",&videoCount);//获取制定目录下的所有视频绝对路径
    //遍历文件列表
    //    foreach (QString const & str, fileList) {
    //        QUrl url(str);
    //        mediaPlayerList->addMedia(url);
    //    }
    //遍历文件列表,并显示到列表窗口
    for(int i=0;i<fileList.size();i++)
    {
        qDebug()<<fileList.at(i)<<endl;
        playList->addItem(fileList.at(i));

        //        QUrl url("file:"+fileList.at(i));
        //        mediaPlayerList->addMedia(url);
    }

    playPushButton = new  QPushButton("播放",mainWidget);
    playPushButton->setGeometry(100,440,50,30);
    playPushButton->show();
    connect(playPushButton,&QPushButton::clicked,mainWidget,[=](){
        //system("killall -STOP mpalyer");
        if(myProcess->state()==QProcess::Running)//如果播放器在运行，则从头开始播放
        {
            myProcess->write("pause\n");
            playPushButton->setText("播放");
        }else
        {
            myProcess->close();
            currentItem = playList->item(0);//如果用户没有选择播放那一个视频，默认播放第一个
            if(cmd.isNull())
            cmd = QString("mplayer -zoom -x 600 -y 450 -slave -quiet -wid %1 /mnt/sd/video/%2 ").arg(QString::number(this->winId())).arg(currentItem->text());
            //cmd = QString("mplayer -geometry 0:0 -zoom -x 600 -y 450 -slave -quiet /home/ldc/daily/video/%1").arg(currentItem->text());//－quiet不要输出冗余信息
            myProcess->start(cmd);
            playPushButton->setText("暂停");
        }
    });

    nextPushButton= new  QPushButton("下一个",mainWidget);
    nextPushButton->setGeometry(300,440,50,30);
    nextPushButton->show();
    connect(nextPushButton,&QPushButton::clicked,mainWidget,[=](){
        myProcess->close();
        int nextItemIndex = playList->row(currentItem);
        nextItemIndex++;
        if(nextItemIndex==playList->count()) nextItemIndex=0;

        currentItem = playList->item(nextItemIndex);//根据索引获取下一个item
        currentItem->setSelected(true);
        cmd = QString("mplayer -zoom -x 600 -y 450 -slave -quiet /mnt/sd/video/%1").arg(currentItem->text());
        //cmd = QString("mplayer -zoom -x 600 -y 450 -slave -quiet /home/ldc/daily/video/%1").arg(currentItem->text());//－quiet不要输出冗余信息
        qDebug()<<playList->count()<<nextItemIndex;
        myProcess->start(cmd);
    });

    lastPushButton= new  QPushButton("上一个",mainWidget);
    lastPushButton->setGeometry(400,440,50,30);
    lastPushButton->show();
    connect(lastPushButton,&QPushButton::clicked,mainWidget,[=](){
        myProcess->close();
        int nextItemIndex = playList->row(currentItem);
        if(nextItemIndex==0) nextItemIndex=playList->count();
        nextItemIndex--;
        currentItem = playList->item(nextItemIndex);//根据索引获取下一个item
        currentItem->setSelected(true);
        cmd = QString("mplayer -zoom -x 600 -y 450 -slave -quiet /mnt/sd/video/%1").arg(currentItem->text());
        //cmd = QString("mplayer -geometry 0:0 -zoom -x 600 -y 450 -slave -quiet /home/ldc/daily/video/%1").arg(currentItem->text());//－quiet不要输出冗余信息
        qDebug()<<playList->count()<<nextItemIndex;
        myProcess->start(cmd);
    });


    exitPushButton= new  QPushButton("退出",mainWidget);
    exitPushButton->setGeometry(500,440,50,30);
    exitPushButton->show();
    connect(exitPushButton,&QPushButton::clicked,mainWidget,[=](){
        myProcess->close();
        this->close();
    });

}

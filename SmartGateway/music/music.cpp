#include "music.h"

Music::Music(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0,0,800,480);
    this->show();
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    move(200,200);
    layoutInit();
    myProcess = new QProcess(mainWidget);//给进程分配内存

    songListWidget = new QListWidget(mainWidget);
    songListWidget->setGeometry(600,0,200,480);
    songListWidget->show();
    songListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭水平滚动条
    //songListWidget->setFrameShape(QListWidget::NoFrame);//去除边框
    songListWidget->setStyleSheet("background-color:transparent;border:1px solid black;color:white");// 透明背景
    fileList = FileTools::getFileNames("/home/pi/workdir/smgw_media/music/",&musicCount);
    //遍历文件列表，添加到列表显示窗口
    for(int i=0;i<fileList.size();i++)
    {
        qDebug()<<fileList.at(i)<<endl;
        songListWidget->addItem(fileList.at(i));
    }
    songListWidget->item(0)->setSelected(true);
    currentMusic = songListWidget->item(0);//select first item by default
    processBarTimer = new QTimer();

    connect(songListWidget,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *item){
        currentMusic=item;
        myProcess->close();
        cmd = QString("/home/pi/workdir/smgw_media/music/%1").arg(item->text());
        qDebug()<<cmd;
        playMusic(cmd);
        playFlag = true;
        processBarSlider->setEnabled(true);
        musicName->setText(item->text());
        playMusicPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                      "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");

    });

    //get mplayer info

    connect(myProcess,&QProcess::readyReadStandardOutput,this,[=](){

        while (myProcess->canReadLine()) {
            QString percent_pos = myProcess->readLine();
            if(percent_pos.indexOf("=")>=0&&percent_pos.indexOf("\n")<25)
            {
                QString pos = percent_pos.mid(percent_pos.indexOf("=")+1,percent_pos.indexOf("\n")-1);
                qDebug()<<pos<<"  "<<percent_pos.indexOf("=")<<"  "<<percent_pos.indexOf("\n");
                current_pos = pos.toInt();
                processBarSlider->setValue(current_pos);
            }else{
                processBarSlider->setValue(current_pos);
            }
        }
    });

    //progress bar notify mplayer to modify progress
    connect(processBarSlider,&CustomSlider::customSliderClick,this,[=](){
        if(myProcess->state()==QProcess::Running)
        {
            qDebug()<<processBarSlider->value()<<endl;
            myProcess->write(QString("seek "+QString::number(processBarSlider->value())+" 1\n").toUtf8());
        }else {
            return ;
        }

    });

    connect(processBarSlider,&CustomSlider::sliderMoved,this,[=](){
        processBarTimer->stop();
    });

    connect(processBarSlider,&CustomSlider::sliderReleased,this,[=](){
        if(myProcess->state()==QProcess::Running)
        {
            qDebug()<<processBarSlider->value()<<endl;
            myProcess->write(QString("seek "+QString::number(processBarSlider->value())+" 1\n").toUtf8());
            processBarTimer->start(1000);
        }else {
            return ;
        }
    });

    connect(processBarTimer,&QTimer::timeout,processBarSlider,[=]{
        myProcess->write("get_percent_pos\n");
    });

}

Music::~Music()
{
    myProcess->write("stop\n");
    myProcess->kill();
    delete myProcess;
}

void Music::layoutInit()
{
    mainWidget = new QWidget(this);
    mainWidget->setGeometry(0,0,800,480);
    mainWidget->show();
    mainWidget->setObjectName("music");
    //mainWidget->setStyleSheet("#music{border-image:url(/mnt/sd/image/4.jpg)}");
    mainWidget->setStyleSheet("background-color:#3b3b3b");

    m_roundImageWidget = new RoundImageWidget(mainWidget);
    m_roundImageWidget->setGeometry(200, 100, 200, 200);
    m_roundImageWidget->startRotateAnimation();
    m_roundImageWidget->show();


    playMusicPushButton = new  QPushButton(mainWidget);
    playMusicPushButton->setGeometry(75,430,32,32);
    playMusicPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPause.png"");}"
                                  "QPushButton:hover{border-image:url("":/video/videoIcon/videoPause_hover.png"");}");
    playMusicPushButton->show();
    connect(playMusicPushButton,&QPushButton::clicked,mainWidget,[=](){
        qDebug()<<myProcess->state()<<endl;
        if(myProcess->state()==QProcess::Running)//如果播放器在运行，则从头开始播放
        {
            myProcess->write("pause\n");

            playFlag = !playFlag;
            if(playFlag==false)
            {
                processBarTimer->stop();
                playMusicPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPause.png"");}"
                                              "QPushButton:hover{border-image:url("":/video/videoIcon/videoPause_hover.png"");}");
            }else {
                processBarTimer->start(1000);
                playMusicPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                              "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");
            }

        }else
        {
            myProcess->close();
            cmd = QString("/home/pi/workdir/smgw_media/music/%1").arg(currentMusic->text());
            musicName->setText(currentMusic->text());
            playMusic(cmd);
            processBarSlider->setEnabled(true);
            processBarTimer->start(1000);
            playMusicPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                          "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");
        }
    });

    lastMusicPushButton= new  QPushButton(mainWidget);
    lastMusicPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPrevious.png"");}"
                                  "QPushButton:hover{border-image:url("":/video/videoIcon/videoPrevious_hover.png"");}");
    lastMusicPushButton->setGeometry(20,430,32,32);
    lastMusicPushButton->show();
    connect(lastMusicPushButton,&QPushButton::clicked,mainWidget,[=](){
        myProcess->close();
        int nextItemIndex = songListWidget->row(currentMusic);//获取当前播放或者选中列表的歌曲行号
        if(nextItemIndex==0) nextItemIndex=songListWidget->count();//判断是否已经是第一首
        nextItemIndex--;//第一首的上一首是最后一首
        currentMusic = songListWidget->item(nextItemIndex);//根据索引获取上一首的音乐
        currentMusic->setSelected(true);//选中
        musicName->setText(currentMusic->text());

        playFlag = true;
        cmd = QString("/home/pi/workdir/smgw_media/music/%1").arg(currentMusic->text());
        playMusic(cmd);
        playMusicPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                      "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");
    });

    nextMusicPushButton= new  QPushButton(mainWidget);
    nextMusicPushButton->setGeometry(130,430,32,32);
    nextMusicPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoNext.png"");}"
                                  "QPushButton:hover{border-image:url("":/video/videoIcon/videoNext_hover.png"");}");
    nextMusicPushButton->show();
    connect(nextMusicPushButton,&QPushButton::clicked,mainWidget,[=](){
        myProcess->close();
        int nextItemIndex = songListWidget->row(currentMusic);
        nextItemIndex++;
        if(nextItemIndex==songListWidget->count()) nextItemIndex=0;
        currentMusic = songListWidget->item(nextItemIndex);//根据索引获取下一个item
        currentMusic->setSelected(true);
        musicName->setText(currentMusic->text());

        playFlag = true;
        cmd = QString("/home/pi/workdir/smgw_media/music/%1").arg(currentMusic->text());
        playMusic(cmd);
        playMusicPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                      "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");
    });

    processBarSlider = new CustomSlider(mainWidget);
    processBarSlider->setGeometry(180,450,350,10);
    processBarSlider->show();
    //processBarSlider->setStyleSheet("QSlider{}");
    processBarSlider->setEnabled(false);
    processBarSlider->setRange(0,100);
    processBarSlider->setOrientation(Qt::Horizontal);

    musicName = new QLabel("unknow",mainWidget);
    musicName->setGeometry(180,410,350,40);
    musicName->setStyleSheet("QLabel{font-size:20px;color:white};"
                             "QLabel{border:1px solid}");
    musicName->show();

    exitPushButton= new  QPushButton(mainWidget);
    exitPushButton->setGeometry(550,430,32,32);
    exitPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoExit.png"");}"
                                  "QPushButton:hover{border-image:url("":/video/videoIcon/videoExit_hover.png"");}");
    exitPushButton->show();
    connect(exitPushButton,&QPushButton::clicked,mainWidget,[=](){
        this->close();
    });

//    volumePushButton= new QPushButton(mainWidget);//音量按钮
//    volumePushButton= new  QPushButton(mainWidget);
//    volumePushButton->setGeometry(500,440,32,32);
//    volumePushButton->show();
//    connect(volumePushButton,&QPushButton::clicked,mainWidget,[=](){
//        myProcess->write("get_time_length\n");
//        myProcess->write("get_percent_pos\n");
//        myProcess->write("get_time_pos\n");
//    });


}
void Music::playMusic(QString file)
{
    QStringList args;
    args<<"-slave";
    args<<"-quiet";
    args<<"-wid"<<QString::number(mainWidget->winId());
    args<<"-zoom";
    args<<"x11";
    args<<file;
    myProcess->start("mplayer",args);
    processBarTimer->start(1000);
}

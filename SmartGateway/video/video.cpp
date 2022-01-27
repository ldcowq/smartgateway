#include "video.h"
Video::Video(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0,0,800,480);
    this->show();
    move(200,200);
    layoutInit();
    this->setAttribute(Qt::WA_DeleteOnClose,true);


    mediaPlayer = new QMediaPlayer(mainWidget);
    mediaPlayerList = new QMediaPlaylist(mainWidget);
    videoWidget = new QVideoWidget(mainWidget);
    videoWidget->setStyleSheet("background-color:#000000");
    videoWidget->setGeometry(0,0,650,420);
    videoWidget->show();

    //设置播放器的播放队列
    mediaPlayer->setPlaylist(mediaPlayerList);
    //设置播放器的显示窗口
    mediaPlayer->setVideoOutput(videoWidget);
    mediaPlayer->setVolume(100);
    //mediaPlayer->setMuted(false);
    mediaPlayer->pause();

    //获取制定目录下的所有视频绝对路径
    fileList = FileTools::getFileNames("/home/pi/workdir/smgw_media/Monitor_videos/",&videoCount);
    //遍历文件列表,并显示到列表窗口
    for(int i=0;i<fileList.size();i++)
    {
        //qDebug()<<fileList.at(i)<<endl;
        playList->addItem(fileList.at(i));
        mediaPlayerList->addMedia(QUrl::fromLocalFile("/home/pi/workdir/smgw_media/Monitor_videos/"+fileList.at(i)));
    }
    playList->item(0)->setSelected(true);//always select first one by default
    mediaPlayerList->setPlaybackMode(QMediaPlaylist::Loop);
    currentItem = playList->item(0);

    connect(playList,&QListWidget::itemClicked,this,[=](QListWidgetItem *item){
       currentItem = item;
    });

    //double click to play video
    connect(playList,&QListWidget::itemDoubleClicked,this,[=](QListWidgetItem *item){
        sliderTimer->stop();
        currentItem=item;
        playPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                      "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");
        customSlider->setEnabled(true);
        sliderTimer->start(50);
        connect(sliderTimer,&QTimer::timeout,this,[=]{
           qint64 playerPos = mediaPlayer->position();//video lengths(ms)
           customSlider->setValue(playerPos);
        });

        int selectIndex = playList->row(item);//get index from playlist
        //int selectIndex = playList->currentRow();//get index from playlist
        QMediaContent selectMedia = mediaPlayerList->media(selectIndex);//find the file through the index
        mediaPlayer->setMedia(selectMedia);
        //mediaPlayer->setMedia(QUrl::fromLocalFile("/home/pi/workdir/smgw_media/Monitor_videos/twlw.mp4"));
        mediaPlayer->setVolume(100);
        mediaPlayer->play();
    });

    //when loading the video,get the lengths of the viedo and set the slider range
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,[=](){
        customSlider->setRange(0,mediaPlayer->duration());
    });

    //progress bar notify video to modify progress
    connect(customSlider,&CustomSlider::customSliderClick,this,[=](){
        mediaPlayer->setPosition(customSlider->value());
    });

    //move the progress bar and notify video to modify progress
    connect(customSlider,&CustomSlider::sliderMoved,this,[=](){
        sliderTimer->stop();
        mediaPlayer->setPosition(customSlider->value());
    });

    connect(customSlider,&CustomSlider::sliderReleased,this,[=](){
        sliderTimer->start();
    });
}

Video::~Video()
{
    delete mediaPlayer;
    delete mediaPlayerList;
    delete videoWidget;
}

void Video::layoutInit()
{
    mainWidget = new QWidget(this);
    mainWidget->show();
    mainWidget->setObjectName("mainWidget");
    mainWidget->setGeometry(0,0,800,480);
    mainWidget->setFixedSize(800,480);
    //mainWidget->setStyleSheet("#mainWidget{border-image:url(/home/pi/workdir/smgw_media/photos/4.jpg)}");
    mainWidget->setStyleSheet("background-color:#3b3b3b");


    playList = new QListWidget(mainWidget);
    playList->setGeometry(650,0,150,480);
    playList->show();
    playList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭水平滚动条
    //playList->setFrameShape(QListWidget::NoFrame);//去除边框
    //playList->setViewMode(QListView::ListMode);
    playList->setStyleSheet("background-color:transparent;border:1px solid black;color:white");// 透明背景

    lastPushButton= new  QPushButton(mainWidget);
    lastPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPrevious.png"");}"
                                  "QPushButton:hover{border-image:url("":/video/videoIcon/videoPrevious_hover.png"");}");
    lastPushButton->setGeometry(250,440,32,32);
    lastPushButton->show();
    connect(lastPushButton,&QPushButton::clicked,mainWidget,[=](){
        int lastVideoIndex = playList->row(currentItem);//获取当前播放或者选中列表的歌曲行号
        if(lastVideoIndex==0) lastVideoIndex=playList->count();//判断是否已经是第一首
        lastVideoIndex--;//第一首的上一首是最后一首
        currentItem = playList->item(lastVideoIndex);
        currentItem->setSelected(true);//set item selected

        sliderTimer->stop();
        playPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                      "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");
        customSlider->setEnabled(true);
        connect(sliderTimer,&QTimer::timeout,this,[=]{
           qint64 playerPos = mediaPlayer->position();//video lengths(ms)
           customSlider->setValue(playerPos);
        });
        sliderTimer->start(50);
        QMediaContent selectMedia = mediaPlayerList->media(lastVideoIndex);//find the file through the index
        mediaPlayer->setMedia(selectMedia);
        mediaPlayer->setVolume(100);
        mediaPlayer->play();
    });

    playPushButton = new  QPushButton(mainWidget);
    playPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPause.png"");}"
                                  "QPushButton:hover{border-image:url("":/video/videoIcon/videoPause_hover.png"");}");
    playPushButton->setGeometry(310,440,32,32);
    playPushButton->show();
    connect(playPushButton,&QPushButton::clicked,mainWidget,[=](){
        if(mediaPlayer->state()==QMediaPlayer::PlayingState)
        {
            mediaPlayer->pause();
            sliderTimer->stop();
            playPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPause.png"");}"
                                          "QPushButton:hover{border-image:url("":/video/videoIcon/videoPause_hover.png"");}");
        }else if(mediaPlayer->state()==QMediaPlayer::PausedState)
        {
            playPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                          "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");
            mediaPlayer->play();
            sliderTimer->start();
        }else if (mediaPlayer->state()==QMediaPlayer::StoppedState) {
            int selectIndex = playList->currentRow();//get index from playlist
            sliderTimer->stop();
            playPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                          "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");
            customSlider->setEnabled(true);
            connect(sliderTimer,&QTimer::timeout,this,[=]{
               qint64 playerPos = mediaPlayer->position();//video lengths(ms)
               customSlider->setValue(playerPos);
            });
            sliderTimer->start(50);
            QMediaContent selectMedia = mediaPlayerList->media(selectIndex);//find the file through the index
            mediaPlayer->setMedia(selectMedia);
            mediaPlayer->setVolume(100);
            mediaPlayer->play();
        }
    });

    nextPushButton= new  QPushButton(mainWidget);
    nextPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoNext.png"");}"
                                  "QPushButton:hover{border-image:url("":/video/videoIcon/videoNext_hover.png"");}");
    nextPushButton->setGeometry(370,440,32,32);
    nextPushButton->show();
    connect(nextPushButton,&QPushButton::clicked,mainWidget,[=](){

        int nextVideoIndex = playList->row(currentItem);//获取当前播放或者选中列表的歌曲行号

        nextVideoIndex++;
        if(nextVideoIndex==playList->count()) nextVideoIndex=0;//判断是否已经是第一首
        //第一首的上一首是最后一首
        currentItem = playList->item(nextVideoIndex);
        currentItem->setSelected(true);//set item selected

        sliderTimer->stop();
        playPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoPlay.png"");}"
                                      "QPushButton:hover{border-image:url("":/video/videoIcon/videoPlay_hover.png"");}");
        customSlider->setEnabled(true);
        connect(sliderTimer,&QTimer::timeout,this,[=]{
           qint64 playerPos = mediaPlayer->position();//video lengths(ms)
           customSlider->setValue(playerPos);
        });
        sliderTimer->start(50);

        QMediaContent selectMedia = mediaPlayerList->media(nextVideoIndex);//find the file through the index
        mediaPlayer->setMedia(selectMedia);
        mediaPlayer->setVolume(100);
        mediaPlayer->play();
    });

    customSlider = new CustomSlider(mainWidget);
    customSlider->setGeometry(0,420,650,10);
    customSlider->show();
    //customSlider->setStyleSheet("QSlider{}");
    customSlider->setEnabled(false);
    customSlider->setOrientation(Qt::Horizontal);

    exitPushButton= new  QPushButton(mainWidget);
    exitPushButton->setGeometry(600,440,32,32);
    exitPushButton->setStyleSheet("QPushButton{border-image:url("":/video/videoIcon/videoExit.png"");}"
                                  "QPushButton:hover{border-image:url("":/video/videoIcon/videoExit_hover.png"");}");
    exitPushButton->show();
    connect(exitPushButton,&QPushButton::clicked,mainWidget,[=](){
        this->close();
    });

    sliderTimer = new QTimer();
}

#include "album.h"
Album::Album(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0,0,800,480);
    this->show();
    this->move(200,200);
    this->setAttribute(Qt::WA_DeleteOnClose,true);//设置关闭窗口自动释放资源
    layoutInit();
}


void Album::layoutInit()
{
    fileList = FileTools::getFileAbsolutePath("/home/pi/workdir/smgw_media/photos",&imageCount);
    qDebug() << fileList<<endl;
    lastPageIndex = imageCount-1;//最后一张图片的索引=总图片数－１
    nextPageIndex = currentImageIndex+1;

    showPic = new QLabel(this);//创建一个标签用于显示图片
    showPic->setGeometry(0,0,800,440);
    showPic->setFixedSize(800,440);
    showPic->show();
    showPic->setStyleSheet("background-color:black");
    //showPic->setScaledContents(true);//设置自适应，放大缩小功能将不能使用

    pixmap.load(fileList.at(currentImageIndex));
    pixmap = pixmap.scaled(showPic->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);//根据标签设置自适应
    showPic->setPixmap(pixmap);
    showPic->setAlignment(Qt::AlignCenter);


    lastPagePushButton = new QPushButton("上一张",this);
    lastPagePushButton->setGeometry(300,440,70,40);
    lastPagePushButton->show();
    connect(lastPagePushButton,&QPushButton::clicked,this,[=](){
        rotateAngle = 0;//旋转角度重置为0
        currentImageIndex = lastPageIndex;
        pixmap.load(fileList.at(currentImageIndex));
        pixmap = pixmap.scaled(showPic->size(),Qt::KeepAspectRatio);
        showPic->setPixmap(pixmap);
        if(nextPageIndex==0)nextPageIndex = abs(nextPageIndex-(imageCount-1))+1;
        if(lastPageIndex==0)lastPageIndex = abs(lastPageIndex-(imageCount-1))+1;
        lastPageIndex--;
        nextPageIndex--;
    });

    nextPagePushButton = new QPushButton("下一张",this);
    nextPagePushButton->setGeometry(400,440,70,40);
    nextPagePushButton->show();
    connect(nextPagePushButton,&QPushButton::clicked,this,[=](){
        rotateAngle = 0;
        currentImageIndex = nextPageIndex;
        pixmap.load(fileList.at(currentImageIndex));
        pixmap = pixmap.scaled(showPic->size(),Qt::KeepAspectRatio);
        showPic->setPixmap(pixmap);
        if(nextPageIndex==(imageCount-1))nextPageIndex = abs(nextPageIndex-(imageCount-1))-1;
        if(lastPageIndex==(imageCount-1))lastPageIndex = abs(lastPageIndex-(imageCount-1))-1;
        nextPageIndex++;
        lastPageIndex++;
    });

    zoomInPushButton = new QPushButton("放大",this);
    zoomInPushButton->setGeometry(100,440,70,40);
    zoomInPushButton->show();
    connect(zoomInPushButton,&QPushButton::clicked,this,[=](){
        zoomValue = zoomValue+0.2f;
        if(zoomValue>2.0f) zoomValue = 2.0f;
        pixmap.load(fileList.at(currentImageIndex));
        pixmap = pixmap.scaled(zoomValue*showPic->width(),zoomValue*showPic->height(),Qt::KeepAspectRatio);
        showPic->setPixmap(pixmap);
    });

    zoomOutPushButton = new QPushButton("缩小",this);
    zoomOutPushButton->setGeometry(200,440,70,40);
    zoomOutPushButton->show();
    connect(zoomOutPushButton,&QPushButton::clicked,this,[=](){
        zoomValue = zoomValue-0.2f;
        if(zoomValue<0.2f) zoomValue = 0.2f;
        pixmap.load(fileList.at(currentImageIndex));
        pixmap = pixmap.scaled(zoomValue*showPic->width(),zoomValue*showPic->height(),Qt::KeepAspectRatio);
        showPic->setPixmap(pixmap);
    });

    rotateRightPushButton = new QPushButton("右转",this);
    rotateRightPushButton->setGeometry(500,440,70,40);
    rotateRightPushButton->show();
    connect(rotateRightPushButton,&QPushButton::clicked,this,[=](){
        rotateAngle = rotateAngle + 90;
        pixmap.load(fileList.at(currentImageIndex));
        QMatrix matrix;
        matrix.rotate(rotateAngle);
        pixmap = pixmap.transformed(matrix,Qt::FastTransformation);
        pixmap = pixmap.scaled(zoomValue*showPic->width(),zoomValue*showPic->height(),Qt::KeepAspectRatio);
        showPic->setPixmap(pixmap);

    });

    rotateLeftPushButton = new QPushButton("左转",this);
    rotateLeftPushButton->setGeometry(600,440,70,40);
    rotateLeftPushButton->show();
    connect(rotateLeftPushButton,&QPushButton::clicked,this,[=](){
        rotateAngle = rotateAngle - 90;
        pixmap.load(fileList.at(currentImageIndex));
        QMatrix matrix;
        matrix.rotate(rotateAngle);
        pixmap = pixmap.transformed(matrix,Qt::FastTransformation);//旋转图片
        pixmap = pixmap.scaled(zoomValue*showPic->width(),zoomValue*showPic->height(),Qt::KeepAspectRatio);//旋转后的宽高，根据放大倍数自适应显示
        showPic->setPixmap(pixmap);
    });

    exitPushButton = new QPushButton("退出",this);
    exitPushButton->setGeometry(730,440,70,40);
    exitPushButton->show();
    connect(exitPushButton,&QPushButton::clicked,this,[=](){
        this->close();
    });

}





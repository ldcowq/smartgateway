#include "slidepage.h"
#include <QDebug>
#include <QPropertyAnimation>

SlidePage::SlidePage(QWidget *parent):QWidget(parent),pageIndex(0),pageCount(0),draggingFlag(false)//初始化值
{
    this->setMinimumSize(570, 480);//设置屏幕大小
    this->setAttribute(Qt::WA_TranslucentBackground, true);//设置主窗体的属性为背景透明

    mainWidget = new QWidget();//创建主显示控件，用于在滚动区域显示
    mainWidget->setStyleSheet("background:transparent");//设置背景透明

    scrollArea = new QScrollArea(this);//创建滑动区域
    scrollArea->setAlignment(Qt::AlignCenter);//设置滚动区域小部件的对齐方式为水平垂直居中
    scrollArea->setWidget(mainWidget);//滚动区域添加主显示控件
    scrollArea->setStyleSheet("background:transparent");//设置背景透明

    /*********************关闭滚动条显示*************************/
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar{background-color:white;height:15px; margin:1px １px 1px １px;border-radius:5px;}"//设置滚动条颜色
                                                     "QScrollBar::sub-line:horizontal{border:none;}"
                                                     "QScrollBar::add-line:horizontal{border:none;}"
                                                     "QScrollBar::handle{background-color:rgba(61,65,81,120);border-radius:5px;}"
                                                     "QScrollBar::handle:hover{background:rgb(61,65,81);}");//滚动条滑块区域样式

    /* 滚屏对象 */
    scroller = QScroller::scroller(scrollArea);//创建滚屏对象,使用scrollArea滚动区域来初始化
    QScroller::ScrollerGestureType gesture = QScroller::LeftMouseButtonGesture;//创建滚屏手势，仅在鼠标左键事件时触发
    scroller->grabGesture(scrollArea->viewport(), gesture);//设置滚屏手势，scrollArea->viewport()设置滚动条跟着手势动

    /* 获取属性 */
    QScrollerProperties properties = scroller->scrollerProperties();//QScrollerProperties滑动器参数类

    /* 设置滑动的时间，值越大，时间越短 */
    properties.setScrollMetric(QScrollerProperties::SnapTime, 0.5);

    /* 设置滑动速度 */
    properties.setScrollMetric(QScrollerProperties::MinimumVelocity, 1);
    scroller->setScrollerProperties(properties);

    /* 主显示控件布局 */
    hBoxLayout = new QHBoxLayout();
    hBoxLayout->setContentsMargins(0, 0, 0, 0);
    hBoxLayout->setSpacing(0);
    mainWidget->setLayout(hBoxLayout);

    /* 定时器，用于判断用户是否是拖动屏幕，区分滑动，超过300ms表示拖动 */
    timer = new QTimer(this);
    connect(scrollArea->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(hScrollBarValueChanged(int)));
    connect(scroller, SIGNAL(stateChanged(QScroller::State)), this, SLOT(onStateChanged(QScroller::State)));
    connect(timer, &QTimer::timeout, this,&SlidePage::onTimerTimeOut);
}

SlidePage::~SlidePage()
{
}

void SlidePage::addPage(QWidget *w)
{
    /* 布局里添加页面 */
    hBoxLayout->addWidget(w);
    /* 页数加一 */
    pageCount++;
}

void SlidePage::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    scrollArea->resize(this->size());
    /* mainWidget需要比scrollArea小 */
    mainWidget->resize(this->width() * pageCount, this->height() - 20);
    if (pageCount == 0) qDebug()<<"当前页面总数为0，请使用addPage()方法添加页面再使用！"<<endl;
}

void SlidePage::hScrollBarValueChanged(int)
{
    /* 滑动时判断当前页的下标 */
    pageIndex= scrollArea->horizontalScrollBar()->value() / this->width();
    pageIndex = scrollArea->horizontalScrollBar()->value()>= (pageIndex * this->width() + this->width() * 0.5) ? pageIndex + 1 : pageIndex;

}

void SlidePage::onStateChanged(QScroller::State state)
{
    static int pressedValue = 0;
    static int releasedValue = 0;
    static int currentPageIndex = 0;

    /* 如果页面数为0，返回，不做任何操作 */
    if (pageCount == 0)
        return;

    /* 松开 */
    if (state == QScroller::Inactive) {
        /* 停止定时器，防止检测到界面是缓慢拖动状态 */
        timer->stop();
        /* 记录松开时的坐标 */
        releasedValue = QCursor::pos().x();

        if (pressedValue == releasedValue)
            return;

        /* 判断按下与松开的距离，首先先判断是不是拖动状态，如果是拖动状态，pageIndex不会变化 */
        if (!draggingFlag) {
            if (pressedValue - releasedValue > 20 && currentPageIndex == pageIndex)
                pageIndex++;
            else
                pageIndex--;
        }

        /* 页面下标判断 */
        if (pageIndex == -1)
            pageIndex = 0;

        if (pageIndex >= pageCount)
            pageIndex = pageCount - 1;

        /* 动画 */
        QPropertyAnimation *animation = new QPropertyAnimation(scrollArea->horizontalScrollBar(), "value");
        animation->setDuration(200);
        animation->setStartValue(scrollArea->horizontalScrollBar()->value());
        animation->setEasingCurve(QEasingCurve::OutCurve);
        animation->setEndValue(pageIndex * this->width());
        animation->start();

        /* 重新赋值*/
        pressedValue = 0;
        releasedValue = 0;
        draggingFlag = false;
    }

    /* 按下 */
    if (state == QScroller::Pressed) {
        pressedValue = QCursor::pos().x();
        currentPageIndex = scrollArea->horizontalScrollBar()->value() / this->width();
        /* 按下如果超过300ms，表示用户在拖动 */
        timer->start(300);
    }
}

void SlidePage::onTimerTimeOut()
{
    /* 拖动标志位 */
    draggingFlag = true;
    timer->stop();
}

int SlidePage::getPageCount()
{
    return pageCount;
}

int SlidePage::getCurrentPageIndex()
{
    return pageIndex;
}


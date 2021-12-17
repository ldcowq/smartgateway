#include "switchbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QRgb>
SwitchButton::SwitchButton(QWidget *parent) : QWidget(parent)//显式调用父类构造函数
{
    //默认属性：
    isChecked = false;//不被选中
    backgroundColor = Qt::gray;//背景颜色
    //checkedColor = (243,152,0); //选中颜色
    checkedColor.setRgb(243,152,0);
    //disabledColor = (190, 190, 190);
    disabledColor.setRgb(190,190,190);
    thumbColor= Qt::gray;  //灰色
    radius=15;//圆角
    sw_height=16;  //高度
    margin=3;//边距



    /* 鼠标滑过光标形状 - 手型 */
    setCursor(Qt::PointingHandCursor);

    /* 连接信号槽 */
    connect(&timer, SIGNAL(timeout()),this, SLOT(onTimeout()));
}

/* 绘制开关 */
void SwitchButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setPen(Qt::NoPen);//设置画笔
    painter.setRenderHint(QPainter::Antialiasing);//开启反走样功能，消除锯齿

    QPainterPath path;
    QColor background;
    QColor thumbColor;
    qreal dOpacity;//透明度

    //先判断开关的状态，根据状态设置属性

    /* 可用状态 */
    if (isEnabled()) {
        /* 打开状态 */
        if (isChecked) {
            background = checkedColor;
            thumbColor = checkedColor;
            dOpacity = 0.600;
            /* 关闭状态 */
        } else {
            background = backgroundColor;
            thumbColor = thumbColor;
            dOpacity = 0.800;
        }
        /* 不可用状态 */
    } else {
        background = backgroundColor;
        dOpacity = 0.260;
        thumbColor = disabledColor;
    }
    /* 绘制大椭圆 */
    painter.setBrush(background);//设置刷子颜色
    painter.setOpacity(dOpacity);//设置透明度
    double width_ = width()- 2* margin;
    double height_ =height() -2* margin;
    path.addRoundedRect(QRectF(margin,margin, width_,height_),radius, radius);
    painter.drawPath(path.simplified());

    /* 绘制小椭圆 */
    painter.setBrush(thumbColor);
    painter.setOpacity(1.0);
    painter.drawEllipse(QRectF(x - (sw_height / 2),y - (sw_height / 2),height(),height()));
}

/* 鼠标按下事件 */
void SwitchButton::mousePressEvent(QMouseEvent *event)
{
    if (isEnabled()) {
        if (event->buttons() & Qt::LeftButton) {//如果鼠标左键处于按下状态，则结果为真
            event->accept();//接受
        } else {
            event->ignore();//忽略
        }
    }
}

/* 鼠标释放事件 - 切换开关状态、发射toggled()信号 */
void SwitchButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (isEnabled()) {
        if ((event->type() == QMouseEvent::MouseButtonRelease)
                && (event->button() == Qt::LeftButton)) {
            event->accept();
            isChecked = !isChecked;
            emit toggled(isChecked);//发送开关切换信号,参数为开关的状态
            timer.start(10);//延时10个毫秒，过渡状态
        } else {
            event->ignore();
        }
    }
}

/* 大小改变事件 */
void SwitchButton::resizeEvent(QResizeEvent *event)
{
    x = sw_height / 2;
    y = sw_height / 2;
    QWidget::resizeEvent(event);
}

/* 默认大小 */
QSize SwitchButton::sizeHint()
{
    return minimumSizeHint();
}

/* 最小大小 */
QSize SwitchButton::minimumSizeHint()
{
    return QSize(2 * (sw_height + margin),sw_height + 2 * margin);
}

/* 切换状态 - 滑动 */
void SwitchButton::onTimeout()
{
    if (isChecked) {
        x += 1;
        if (x >= width() - sw_height - sw_height / 2 ) {
            timer.stop();
            x -= 1;
        }
    } else {
        x -= 1;
        if (x <= sw_height / 2) {
            timer.stop();
            x += 1;
        }
    }
    update();
}

/* 返回开关状态 - 打开：true 关闭：false */
bool SwitchButton::isOpen()
{
    return isChecked;
}

/* 设置开关状态 */
void SwitchButton::setToggle(bool checked)
{
    isChecked = checked;
    timer.start(10);
}

/* 设置背景颜色 */
void SwitchButton::setBackgroundColor(QColor color)
{
    backgroundColor = color;
}

/* 设置选中颜色 */
void SwitchButton::setCheckedColor(QColor color)
{
    checkedColor = color;
}

/* 设置不可用颜色 */
void SwitchButton::setDisbaledColor(QColor color)
{
    disabledColor = color;
}

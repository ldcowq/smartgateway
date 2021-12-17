#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>
#include<QTimer>

class SwitchButton : public QWidget
{
    Q_OBJECT
private:
    /*开关状态 是否选中 */
    bool isChecked;

    /* 背景颜色 */
    QColor backgroundColor;

    /* 选中颜色 */
    QColor checkedColor;

    /* 不可用颜色 */
    QColor disabledColor;

    /* 拇指颜色 */
    QColor thumbColor;

    /* 圆角 */
    qreal radius;

    /* x点坐标 */
    qreal x;

    /* y点坐标 */
    qreal y;

    /* 组件高度 */
    qint16 sw_height;

    /* 外边距 */
    qint16 margin;

    /* 定时器 */
    QTimer timer;


public:
    explicit SwitchButton(QWidget *parent = 0);
    /* 返回开关状态 - 打开：true 关闭：false */
    bool isOpen();

    /* 设置开关状态 */
    void setToggle(bool checked);

    /* 设置背景颜色 */
    void setBackgroundColor(QColor color);

    /* 设置选中颜色 */
    void setCheckedColor(QColor color);

    /* 设置不可用颜色 */
    void setDisbaledColor(QColor color);

    /* 绘制开关 */
    void paintEvent(QPaintEvent *event);

    /* 鼠标按下事件 */
    void mousePressEvent(QMouseEvent *event);

    /* 鼠标释放事件 - 切换开关状态、发射toggled()信号 */
    void mouseReleaseEvent(QMouseEvent *event);

    /* 大小改变事件 */
    void resizeEvent(QResizeEvent *event);


    /* 缺省大小 返回一个推荐大小的值*/
    QSize sizeHint();
    QSize minimumSizeHint();
signals:
    /* 状态改变时，发射信号 */
    void toggled(bool checked);
public slots:
    /* 状态切换时，用于产生滑动效果 */
    void onTimeout();

};

#endif // SWITCHBUTTON_H

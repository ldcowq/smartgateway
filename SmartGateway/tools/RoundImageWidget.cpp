#include "RoundImageWidget.h"

#include <QTimer>
#include <QPainter>
#include <QDebug>

RoundImageWidget::RoundImageWidget(QWidget *parent) : QWidget(parent)
{
    m_rotateAngle = 0.0;

    QString backgroundImageName("/home/pi/workdir/smgw_media/photos/5.jpg");
    bool isLoadOk = m_backgroundImage.load(backgroundImageName);
    if (!isLoadOk) {
        qDebug()<< "load" << backgroundImageName << "failed !";
    }
}

void RoundImageWidget::startRotateAnimation()
{
    if (nullptr ==  m_timer) {

        // 通过定时器去旋转图片，可根据自身需求去设定旋转速度
        int speed = 50;
        qreal angle = 1.0;

        m_timer = new QTimer(this);
        m_timer->setInterval(speed);

        connect(m_timer, &QTimer::timeout, [=]() {
            m_rotateAngle += angle;
            if (m_rotateAngle > 360.0) {
                m_rotateAngle = angle;
            }
            repaint();
        });
    }

    m_timer->start();
}

void RoundImageWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if(!m_backgroundImage.isNull()){

       // 中心点
       int centerPosW = width() >> 1;
       int centerPosH = height() >> 1;

       QPainter painter(this);
       painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
       // 把自身截取为圆形
       QPainterPath path;
       int round = qMin(width(), height());
       path.addEllipse(0, 0, round, round);
       painter.setClipPath(path);

       // 设置中心点为起点
       painter.translate(centerPosW, centerPosH);
       // 开始旋转
       painter.rotate(m_rotateAngle);
       // 恢复起点位置，即左上角(0，0)
       painter.translate(-centerPosW, -centerPosH);

       // 绘制图片
       painter.drawPixmap(-1, -1, width()+2, height()+2, m_backgroundImage);
    }
}

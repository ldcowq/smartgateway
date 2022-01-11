#include "customslider.h"

CustomSlider::CustomSlider(QWidget *parent):QSlider (parent)
{
    this->setParent(parent);//embed slider in mainWidget
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
}

void CustomSlider::mousePressEvent(QMouseEvent *event)
{
    QSlider::mousePressEvent(event);
    double pos = event->pos().x()/(double)width();
    setValue(pos*(maximum()-minimum())+minimum());
    emit customSliderClick();
}

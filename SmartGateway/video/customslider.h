#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H
#include <QSlider>
#include <QMouseEvent>
class CustomSlider : public QSlider
{
    Q_OBJECT
public:
    CustomSlider(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void customSliderClick();
};

#endif // CUSTOMSLIDER_H

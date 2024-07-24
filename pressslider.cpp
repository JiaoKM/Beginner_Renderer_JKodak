#include "pressslider.h"
#include <QMouseEvent>
#include <QDebug>

pressSlider::pressSlider(QWidget *parent):QSlider (parent)
{

}

pressSlider::~pressSlider()
{

}

void pressSlider::mousePressEvent(QMouseEvent *ev)
{
    int currentX = ev->pos().x();
    double per = currentX *1.0 /this->width();
    int value = per*(this->maximum() - this->minimum()) + this->minimum();

    //qDebug() << value;

    this->setValue(value);
    QSlider::mousePressEvent(ev);
}

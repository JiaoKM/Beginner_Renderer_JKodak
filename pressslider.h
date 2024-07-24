#ifndef PRESSSLIDER_H
#define PRESSSLIDER_H

#include <QObject>
#include <QSlider>

class pressSlider : public QSlider
{
public:
    pressSlider(QWidget *parent = nullptr);
    ~pressSlider();
    void mousePressEvent(QMouseEvent *ev);
};

#endif // PRESSSLIDER_H

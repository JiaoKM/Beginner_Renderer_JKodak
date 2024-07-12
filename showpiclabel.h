#ifndef SHOWPICLABEL_H
#define SHOWPICLABEL_H

#include <QLabel>
#include <QImage>
#include <QColor>
#include <QPixmap>


class ShowPicLabel
{
public:
    ShowPicLabel(QLabel *showLabel);
    ~ShowPicLabel();

private:
    QImage *showImage;
    QLabel *showLabel;
    int width;
    int height;

    void Clear();
};

#endif // SHOWPICLABEL_H

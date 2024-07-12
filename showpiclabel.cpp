#include "showpiclabel.h"

ShowPicLabel::ShowPicLabel(QLabel *showLabel)
{
    this->showLabel = showLabel;
    this->width = showLabel->width();
    this->height = showLabel->height();
    this->Clear();
    this->showLabel->setPixmap(QPixmap::fromImage(*this->showImage));
}

ShowPicLabel::~ShowPicLabel()
{

}

void ShowPicLabel::Clear()
{
    this->showImage = new QImage(this->width, this->height, QImage::Format_ARGB32);
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->showImage->setPixel(i, j, qRgb(0, 0, 0));
        }
    }
}

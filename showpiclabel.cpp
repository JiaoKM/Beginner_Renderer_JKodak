#include "showpiclabel.h"

ShowPicLabel::ShowPicLabel(QLabel *showLabel)
{
    this->showLabel = showLabel;
    this->width = showLabel->width();
    this->height = showLabel->height();
    this->showImage = new QImage(this->width, this->height, QImage::Format_ARGB32);
    this->Clear();
    this->UpdatePic();
}

ShowPicLabel::~ShowPicLabel()
{
    delete this->showImage;
}

void ShowPicLabel::Clear()
{
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->SetPixel(i, j, qRgba(0, 0, 0, 255));
        }
    }
}

void ShowPicLabel::SetPixel(int i, int j, QRgb color)
{
    this->showImage->setPixel(i, this->height - j - 1, color);
}

void ShowPicLabel::UpdatePic()
{
    this->showLabel->setPixmap(QPixmap::fromImage(*this->showImage));
}

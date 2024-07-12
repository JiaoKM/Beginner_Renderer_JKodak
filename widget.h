#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include "showpiclabel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_ModelSelect_clicked();

private:
    Ui::Widget *ui;
    ShowPicLabel *showPicLabel;
};
#endif // WIDGET_H

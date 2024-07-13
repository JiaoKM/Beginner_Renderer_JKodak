#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include "showpiclabel.h"
#include "renderer.h"
#include "model.h"

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

    void on_RenderButton_clicked();

private:
    Ui::Widget *ui;
    ShowPicLabel *showPicLabel;
    Model *model;
    renderer *JRender;

    QString readyStatus = "Ready to load";
    QString loadSuccess = "Load your model successfully!";
    QString loadFail = "Loading your model failed.";
    QString renderSuccess = "Render your model successfully!";
};
#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QImage>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include "showpiclabel.h"
#include "geometry.h"
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

    void on_horizontalControl_valueChanged(int value);

    void on_verticalControl_valueChanged(int value);

    void on_ClearButton_clicked();

    void on_posXedit_textChanged();

    void on_posYedit_textChanged();

    void on_posZedit_textChanged();

private:
    Ui::Widget *ui;
    ShowPicLabel *showPicLabel;
    Model *model;
    renderer *JRender;

    QString readyStatus = "Ready to load";
    QString loadSuccess = "Load your model successfully!";
    QString loadFail = "Loading your model failed.";
    QString renderSuccess = "Render your model successfully!";

    float light_pos_x;
    float light_pos_y;
    float light_pos_z;
    Vec3f light_pos;
};
#endif // WIDGET_H

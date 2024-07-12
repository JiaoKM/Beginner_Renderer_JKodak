#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->showPicLabel = new ShowPicLabel(ui->ShowLabel);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_ModelSelect_clicked()
{
    QString modelFilePath;
    modelFilePath = QFileDialog::getOpenFileName(this, tr("Select your model"), "", tr("*.obj"));

    if (!modelFilePath.isEmpty()) {

    }
}

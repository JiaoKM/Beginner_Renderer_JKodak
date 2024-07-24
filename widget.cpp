#include "widget.h"
#include "ui_widget.h"

#define PI 3.14159265

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->showPicLabel = new ShowPicLabel(ui->ShowLabel);
    ui->ConsoleText->setText(this->readyStatus);
    this->JRender = new renderer(this->showPicLabel->width, this->showPicLabel->height);
    ui->RenderButton->setDisabled(true);
    ui->verticalControl->setDisabled(true);
    ui->horizontalControl->setDisabled(true);
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
        this->model = new Model(modelFilePath);
        if (this->model->load_flag) {
            ui->ConsoleText->setText(this->loadSuccess);
            ui->RenderButton->setDisabled(false);
        }
        else ui->ConsoleText->setText(this->loadFail);
    }
    else {
        ui->ConsoleText->setText(this->loadFail);
    }
}

void Widget::on_RenderButton_clicked()
{
    this->showPicLabel->Clear();
    this->JRender->reset_zBuffer();
    bool render_flag = this->JRender->render(this->showPicLabel, this->model);
    this->showPicLabel->UpdatePic();
    if (render_flag) {
        ui->ConsoleText->setText(this->renderSuccess);
    }
    ui->ModelSelect->setDisabled(true);
    ui->RenderButton->setDisabled(true);
    ui->verticalControl->setDisabled(false);
    ui->horizontalControl->setDisabled(false);
}

void Widget::on_horizontalControl_valueChanged(int value)
{
    float phi = (value + 1) / 100.0 * 2 * PI;
    this->showPicLabel->Clear();
    this->JRender->reset_zBuffer();
    this->JRender->camera->phi = phi;
    this->JRender->camera->calc_pos();
    this->JRender->render(this->showPicLabel, this->model);
    this->showPicLabel->UpdatePic();
}

void Widget::on_verticalControl_valueChanged(int value)
{
    float theta = PI / 4.0 + (value + 1) / 100.0 * PI / 2.0;
    this->showPicLabel->Clear();
    this->JRender->reset_zBuffer();
    this->JRender->camera->theta = theta;
    this->JRender->camera->calc_pos();
    this->JRender->render(this->showPicLabel, this->model);
    this->showPicLabel->UpdatePic();
}

void Widget::on_ClearButton_clicked()
{
    this->showPicLabel->Clear();
    this->JRender->reset_zBuffer();
    this->showPicLabel->UpdatePic();
    ui->ModelSelect->setDisabled(false);
    ui->RenderButton->setDisabled(true);
    ui->verticalControl->setDisabled(true);
    ui->horizontalControl->setDisabled(true);
    ui->ConsoleText->setText(this->readyStatus);
    delete this->model;
}

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->showPicLabel = new ShowPicLabel(ui->ShowLabel);
    ui->ConsoleText->setText(this->readyStatus);
    this->JRender = new renderer(this->showPicLabel->width, this->showPicLabel->height);
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
        if (this->model->load_flag) ui->ConsoleText->setText(this->loadSuccess);
        else ui->ConsoleText->setText(this->loadFail);
    }
    else {
        ui->ConsoleText->setText(this->loadFail);
    }
}

void Widget::on_RenderButton_clicked()
{
    this->showPicLabel->Clear();
    bool render_flag = this->JRender->render(this->showPicLabel, this->model);
    if (render_flag) {
        ui->ConsoleText->setText(this->renderSuccess);
    }
}

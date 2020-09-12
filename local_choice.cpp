#include "local_choice.h"
#include "ui_local_choice.h"

local_choice::local_choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::local_choice)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

local_choice::~local_choice()
{
    delete ui;
}

void local_choice::on_pushButton_clicked() {
    emit choice(1);
    accept();
}

void local_choice::on_pushButton_2_clicked() {
    emit choice(2);
    accept();
}


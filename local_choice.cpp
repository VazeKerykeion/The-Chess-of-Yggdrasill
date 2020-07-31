#include "local_choice.h"
#include "ui_local_choice.h"

local_choice::local_choice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::local_choice)
{
    ui->setupUi(this);
}

local_choice::~local_choice()
{
    delete ui;
}

void local_choice::on_pushbotton_click(){
    emit choice(1);
    accept();
}
void local_choice::on_pushbotton_2_click(){
    emit choice(2);
    accept();
}


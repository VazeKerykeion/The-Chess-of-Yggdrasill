#include "connection.h"
#include "ui_connection.h"

connection::connection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::connection)
{
    ui->setupUi(this);
}

connection::~connection()
{
    delete ui;
}
void connection::on_pushButton_3_clicked(){
    emit showmain();
    this->close();
}
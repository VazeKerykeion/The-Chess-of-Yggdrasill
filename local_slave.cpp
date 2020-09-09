#include "local_slave.h"
#include "ui_local_slave.h"
#include <QMessageBox>

local_slave::local_slave(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::local_slave) {
    wait = 1;
    ui->setupUi(this);
}

void local_slave::get_socket(QTcpSocket *t) {
    tcpSocket = t;
    connect(tcpSocket, &QTcpSocket::readyRead, this, &local_slave::read_data);
}

void local_slave::read_data() {
    QString data = tcpSocket->readAll();
    if (wait == 1) {
        //QMessageBox::information(NULL,"提示",data);
        if (data == "rerps") {
            ui->rock->setEnabled(true);
            ui->paper->setEnabled(true);
            ui->scissors->setEnabled(true);
            //QMessageBox::information(NULL,"提示","平局，重新猜拳");
        } else if (data == "first") {
            order = -1;
            ui->textEdit->setText("先手");
            ui->rock->setVisible(false);
            ui->paper->setVisible(false);
            ui->scissors->setVisible(false);
            wait = 2;
        } else if (data == "second") {
            order = 1;
            ui->textEdit->setText("后手");
            ui->rock->setVisible(false);
            ui->paper->setVisible(false);
            ui->scissors->setVisible(false);
            wait = 2;
        } else {
            QMessageBox::information(NULL, "提示", "客机有点问题");
        }
    }
}

void local_slave::on_rock_clicked() {
    tcpSocket->write("rock");
    ui->rock->setEnabled(false);
    ui->paper->setEnabled(false);
    ui->scissors->setEnabled(false);

}

void local_slave::on_scissors_clicked() {
    tcpSocket->write("scissors");
    ui->rock->setEnabled(false);
    ui->paper->setEnabled(false);
    ui->scissors->setEnabled(false);

}

void local_slave::on_paper_clicked() {
    tcpSocket->write("paper");
    ui->rock->setEnabled(false);
    ui->paper->setEnabled(false);
    ui->scissors->setEnabled(false);

}

local_slave::~local_slave() {
    delete ui;
}

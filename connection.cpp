#include "connection.h"
#include "ui_connection.h"
#include <QMessageBox>
#include <QtNetwork>

connection::connection(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::connection) {
    ui->setupUi(this);
}

connection::~connection() {
    delete ui;
}

void connection::on_pushButton_3_clicked() {
    emit showmain();
    this->close();
    delete this;
}

void connection::on_pushButton_2_clicked() {
    if (con_mode == 1) {

        tcpSocket = new QTcpSocket();
        tcpSocket->connectToHost(ui->textEdit_2->toPlainText(), 9888);
        if (tcpSocket->waitForConnected(1000)) {
            QMessageBox::information(NULL, "提示", "该主机可用");
            tcpSocket->write("game start");
            localSlave = new local_slave(this);
            connect(this, &connection::send_socket, localSlave, &local_slave::get_socket);
            emit send_socket(tcpSocket);
            localSlave->show();
            this->hide();
        } else {
            QMessageBox::information(NULL, "提示", "连接失败");
            tcpSocket->disconnectFromHost();
        }
        //

    }
}

void connection::change_mode(int a) {
    con_mode = a;
    if (con_mode == 1) {
        ui->textEdit->setEnabled(false);
        ui->textEdit_3->setEnabled(false);
        ui->textEdit_4->setEnabled(false);
    }
}
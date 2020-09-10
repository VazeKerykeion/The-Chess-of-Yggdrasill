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
        tcpSocket->connectToHost(ui->IPaddr->text(), 9888);
        if (tcpSocket->waitForConnected(1000)) {
            QMessageBox::information(NULL, "提示", "该主机可用");
            tcpSocket->write("game start");
            localSlave = new local_slave(this);
            connect(this, &connection::send_socket, localSlave, &local_slave::get_socket);
            connect(localSlave, &local_slave::showmain, this, &connection::show);
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
        ui->player_name->setEnabled(false);
        ui->port->setEnabled(false);
        ui->password->setEnabled(false);
    }
}
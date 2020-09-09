#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMainWindow>
#include <QtNetwork>
#include "local_slave.h"

namespace Ui {
    class connection;
}

class connection : public QMainWindow {
Q_OBJECT
signals:

    void showmain();

    void send_socket(QTcpSocket *t);

public:
    explicit connection(QWidget *parent = nullptr);

    ~connection();

public slots:

    void change_mode(int a);

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::connection *ui;
    int con_mode;
    QTcpSocket *tcpSocket;
    local_slave *localSlave;
    //QUdpSocket udpSocket;


};

#endif // CONNECTION_H

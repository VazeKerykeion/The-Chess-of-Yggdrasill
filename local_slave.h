#ifndef LOCAL_SLAVE_H
#define LOCAL_SLAVE_H

#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
    class local_slave;
}

class local_slave : public QMainWindow {
Q_OBJECT

public:
    explicit local_slave(QWidget *parent = nullptr);

    ~local_slave();

public slots:

    void get_socket(QTcpSocket *t);

    void read_data();

    void on_rock_clicked();

    void on_scissors_clicked();

    void on_paper_clicked();

private:
    Ui::local_slave *ui;
    QTcpSocket *tcpSocket;
    int wait;
    int order;
};

#endif // LOCAL_SLAVE_H

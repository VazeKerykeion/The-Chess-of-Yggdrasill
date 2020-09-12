#ifndef local_master_H
#define local_master_H

#include "chessBoard.h"
#include "cell_label.h"
#include <QMainWindow>
#include <QtNetwork>

namespace Ui {
    class local_master;
}

class local_master : public QMainWindow {
Q_OBJECT

public:
    explicit local_master(QWidget *parent = nullptr);

    ~local_master();

signals:

    void showmain();

private slots:

    void new_client();

    void fresh();

    void read_data();

    void on_chess1_clicked();

    void on_chess2_clicked();

    void on_chess3_clicked();

    void cells_clicked(int i, int j);

private:
    QVector<QVector<cell_label *>> cells;

    void refresh_text();

    void first_second();

    void refresh_board(chessboard *chessBoard);

    void initialize(int order);

    int turns;
    Ui::local_master *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    chessboard *chessBoard;
    QString *picname;
    int wait;
    int count_rps;
    int master_rps;
    int slave_rps;
    int order;
    int *num_chess;
    int chesstype;
};

#endif // local_master_H

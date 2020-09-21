#ifndef LOCAL_SLAVE_H
#define LOCAL_SLAVE_H

#include <QMainWindow>
#include <QtNetwork>
#include "chessBoard.h"
#include "cell_label.h"

namespace Ui {
    class local_slave;
}

class local_slave : public QMainWindow {
Q_OBJECT

public:
    explicit local_slave(QWidget *parent = nullptr);

    ~local_slave();

signals:

    void showmain();

public slots:

    void get_socket(QTcpSocket *t);

    void read_data();

    void fresh();

    void on_chess1_clicked();

    void on_chess2_clicked();

    void on_chess3_clicked();

    void cells_clicked(int i, int j);

private:
    QVector<QVector<cell_label *>> cells;
    QParallelAnimationGroup *animationGroup;
    stack<pair<point, char>> movedChess;

    void action(int order);

    void initialize(int order);

    void refresh_text();

    void refresh_board(chessboard *chessBoard);

    Ui::local_slave *ui;
    QTcpSocket *tcpSocket;
    chessboard *chessBoard;
    QString *picname;
    int turns;
    int wait;
    int order;
    int *num_chess;
    int chesstype;
};

#endif // LOCAL_SLAVE_H

#ifndef SINGLE_PLAY_H
#define SINGLE_PLAY_H

#include "chessBoard.h"
#include <QMainWindow>
#include "cell_label.h"
namespace Ui {
class single_play;
}

class single_play : public QMainWindow {
Q_OBJECT

public:
    explicit single_play(QWidget *parent = nullptr);

    void refresh_board(chessboard *chessBoard);

    ~single_play();

signals:

    void showmain();

private slots:

    void on_gary1_clicked();

    void on_gary2_clicked();

    void on_gary3_clicked();

    void on_green1_clicked();

    void on_green2_clicked();

    void on_green3_clicked();

    void fresh();

    void cells_clicked(int i, int j);


private:
    Ui::single_play *ui;
    chessboard *chessBoard;
    QVector<QVector<cell_label *>> cells;

    void refresh_text();

    void initialize();

    void step(int x, int y, int chesstype);

    void pause();

    int turns;
    int *num_chess;
    int chesstype_gray;
    int chesstype_green;
    int camp;
};

#endif // SINGLE_PLAY_H

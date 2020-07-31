#ifndef SINGLE_PLAY_H
#define SINGLE_PLAY_H

#include "chessBoard.h"
#include <QMainWindow>
#include "cell_label.h"
namespace Ui {
class single_play;
}

class single_play : public QMainWindow
{
    Q_OBJECT

public:
    explicit single_play(QWidget *parent = nullptr);
    void refresh_board(chessboard * chessBoard);
    ~single_play();
signals:
    void showmain();
private:
    Ui::single_play *ui;
    chessboard * chessBoard;
    QVector<QVector<cell_label*>> cells;
    void refresh_text();
    void step(int x,int y,int chesstype);
    int * num_chess;
    int chesstype_gray;
    int chesstype_green;
    int camp;
};

#endif // SINGLE_PLAY_H

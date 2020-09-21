#include "single_play.h"
#include "ui_single_play.h"
#include "chessBoard.h"
#include "cell_label.h"
#include <QPixmap>
#include <QVector>
#include <QDebug>
#include <QMessageBox>

single_play::single_play(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::single_play) {
    ui->setupUi(this);
    connect(ui->actionback, &QAction::triggered, [=]() {
        emit showmain();
        this->close();
        delete this;
    });
    //this->setStyleSheet("#single_play {background-color: rgb(255, 255, 255)}");
    //ui->label->setPixmap(QPixmap(":/pic/chessboard.png"));
    this->setFixedSize(this->size());
    animationGroup = new QParallelAnimationGroup(this);
    initialize();
}

void single_play::refresh_text() {
    ui->num_gary1->setText(QString::number(num_chess[2]));
    ui->num_gary2->setText(QString::number(num_chess[1]));
    ui->num_gary3->setText(QString::number(num_chess[0]));
    ui->num_green1->setText(QString::number(num_chess[4]));
    ui->num_green2->setText(QString::number(num_chess[5]));
    ui->num_green3->setText(QString::number(num_chess[6]));
}

void single_play::refresh_board(chessboard *chessBoard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (chessBoard->board[i][j].chessType) {
                case 1:
                    cells[i][j]->setPixmap(QPixmap(":/pic/chess_1.png").scaled(40, 40));
                    break;
                case 2:
                    cells[i][j]->setPixmap(QPixmap(":/pic/chess_2.png").scaled(40, 40));
                    break;
                case 3:
                    cells[i][j]->setPixmap(QPixmap(":/pic/chess_3.png").scaled(40, 40));
                    break;
                case -1:
                    cells[i][j]->setPixmap(QPixmap(":/pic/chess_-1.png").scaled(40, 40));
                    break;
                case -2:
                    cells[i][j]->setPixmap(QPixmap(":/pic/chess_-2.png").scaled(40, 40));
                    break;
                case -3:
                    cells[i][j]->setPixmap(QPixmap(":/pic/chess_-3.png").scaled(40, 40));
                    break;
                default:
                    cells[i][j]->setPixmap(QPixmap("").scaled(40, 40));
                    break;
            }
            cells[i][j]->move(81 + 40 * j, 64 + 40 * i);
            cells[i][j]->raise();
        }
    }
}

void single_play::initialize() {
    chessBoard = new chessboard();
    turns = 0;
    QVector<QVector<cell_label *>> t(8, QVector<cell_label *>(8));
    cells = t;
    QVector<QVector<QLabel *>> board(8, QVector<QLabel *>(8));

    num_chess = new int[7]{1, 1, 30, 0, 30, 1, 1};
    chesstype_gray = -1;
    chesstype_green = 1;
    camp = -1;

    ui->gary1->setIconSize(QSize(40, 40));
    ui->gary2->setIconSize(QSize(40, 40));
    ui->gary3->setIconSize(QSize(40, 40));
    ui->green1->setIconSize(QSize(40, 40));
    ui->green2->setIconSize(QSize(40, 40));
    ui->green3->setIconSize(QSize(40, 40));

    ui->gary1->setIcon(QPixmap(":/pic/chess_-1.png"));
    ui->gary2->setIcon(QPixmap(":/pic/chess_-2.png"));
    ui->gary3->setIcon(QPixmap(":/pic/chess_-3.png"));
    ui->green1->setIcon(QPixmap(":/pic/chess_1.png"));
    ui->green2->setIcon(QPixmap(":/pic/chess_2.png"));
    ui->green3->setIcon(QPixmap(":/pic/chess_3.png"));
    refresh_text();
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            if(chessBoard->board[i][j].root == 1) {
                QLabel *temp = new QLabel(this);
                temp->setFixedSize(40, 40);
                //temp->setStyleSheet("border:1px solid black");
                temp->setScaledContents(true);
                temp->setPixmap(QPixmap(":/pic/root_1.png").scaled(40, 40));
                temp->move(81 + 40 * j, 64 + 40 * i);
            } else if (chessBoard->board[i][j].root == -1) {
                QLabel *temp = new QLabel(this);
                temp->setFixedSize(40, 40);
                //temp->setStyleSheet("border:1px solid black");
                temp->setScaledContents(true);
                temp->setPixmap(QPixmap(":/pic/root_-1.png").scaled(40, 40));
                temp->move(81 + 40 * j, 64 + 40 * i);
            }

            board[i][j] = new QLabel(this);
            board[i][j]->setVisible(true);
            board[i][j]->setFixedSize(40, 40);
            board[i][j]->setScaledContents(true);
            board[i][j]->move(81 + 40 * j, 64 + 40 * i);
            board[i][j]->setStyleSheet("border:1px solid black");

            cells[i][j] = new cell_label(this);
            cells[i][j]->set_point(i, j);
            cells[i][j]->setVisible(true);
            cells[i][j]->setFixedSize(40, 40);
            cells[i][j]->setScaledContents(true);
            cells[i][j]->move(81 + 40 * j, 64 + 40 * i);
            //cells[i][j]->setStyleSheet("border:1px solid black");
            board[i][j]->stackUnder(cells[i][j]);
            if (chessBoard->board[i][j].chessType == 1) {
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_1.png").scaled(40, 40));
            } else if (chessBoard->board[i][j].chessType == -1) {
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_-1.png").scaled(40, 40));
            }


            connect(cells[i][j], &cell_label::clicked, this, &single_play::cells_clicked);
            //connect(cells[i][j], &cell_label::fresh, this, &single_play::fresh);
        }
    }
}

void single_play::fresh() {
    refresh_board(chessBoard);
}

void single_play::cells_clicked(int i, int j) {
    bool res = false;
    if (camp == -1 && num_chess[chesstype_gray + 3] > 0) {
        res = chessBoard->step(i, j, chesstype_gray);
        if (res) {
            num_chess[chesstype_gray + 3]--;
            chesstype_gray = -1;
        }

    } else if (camp == 1 && num_chess[chesstype_green + 3] > 0) {
        res = chessBoard->step(i, j, chesstype_green);
        if (res) {
            num_chess[chesstype_green + 3]--;
            chesstype_green = 1;
        }
    }
    if (res) {
        movedChess = chessBoard->get_movedChess();
        //refresh_board(chessBoard);
        switch (chessBoard->board[i][j].chessType) {
            case 1:
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_1.png").scaled(40, 40));
                break;
            case 2:
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_2.png").scaled(40, 40));
                break;
            case 3:
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_3.png").scaled(40, 40));
                break;
            case -1:
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_-1.png").scaled(40, 40));
                break;
            case -2:
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_-2.png").scaled(40, 40));
                break;
            case -3:
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_-3.png").scaled(40, 40));
                break;
            default:
                cells[i][j]->setPixmap(QPixmap("").scaled(40, 40));
                break;
        }


        turns++;
        if (turns < 2) camp = -1;
        else if (turns >= 2 && turns < 4) camp = 1;
        else camp = -camp;
        /*



        */
        chessBoard->offset(num_chess);
        action();
        //Sleep(1000);
        //refresh_board(chessBoard);
        refresh_text();
        int reward = chessBoard->judge();
        if (reward == 1) {
            QString s = QString("青方胜利");
            QMessageBox::information(NULL, "", s);
            this->close();
            emit showmain();
        } else if (reward == -1) {
            QString s = QString("灰方胜利");
            QMessageBox::information(NULL, "", s);
            this->close();
            emit showmain();
        }

    }


}

void single_play::action() {
    animationGroup->clear();
    while (!movedChess.empty()) {
        pair<point, char> t = movedChess.top();
        if (t.second == ' ') {
            movedChess.pop();
            continue;
        }
        QPropertyAnimation *t_anima;
        cell_label *movedLabel;
        switch (t.second) {
            case 'w':
                movedLabel = cells[t.first.x + 1][t.first.y];
                t_anima = new QPropertyAnimation(movedLabel, "pos");
                t_anima->setDuration(500);
                t_anima->setStartValue(QPoint(movedLabel->x(), movedLabel->y()));
                t_anima->setEndValue(QPoint(movedLabel->x(), movedLabel->y() - 40));
                break;
            case 's':
                movedLabel = cells[t.first.x - 1][t.first.y];
                t_anima = new QPropertyAnimation(movedLabel, "pos");
                t_anima->setDuration(500);
                t_anima->setStartValue(QPoint(movedLabel->x(), movedLabel->y()));
                t_anima->setEndValue(QPoint(movedLabel->x(), movedLabel->y() + 40));
                break;
            case 'a':
                movedLabel = cells[t.first.x][t.first.y + 1];
                t_anima = new QPropertyAnimation(movedLabel, "pos");
                t_anima->setDuration(500);
                t_anima->setStartValue(QPoint(movedLabel->x(), movedLabel->y()));
                t_anima->setEndValue(QPoint(movedLabel->x() - 40, movedLabel->y()));
                break;
            case 'd':
                movedLabel = cells[t.first.x][t.first.y - 1];
                t_anima = new QPropertyAnimation(movedLabel, "pos");
                t_anima->setDuration(500);
                t_anima->setStartValue(QPoint(movedLabel->x(), movedLabel->y()));
                t_anima->setEndValue(QPoint(movedLabel->x() + 40, movedLabel->y()));
                break;
            default:
                break;
        }

        //QString s=QString("%1,%2").arg(x).arg(y);
        //QMessageBox::information(NULL,"",s);

        t_anima->setEasingCurve(QEasingCurve::InOutQuad);
        //t_anima->start();
        animationGroup->addAnimation(t_anima);
        movedChess.pop();
    }

    animationGroup->start();
    connect(animationGroup, &QPropertyAnimation::finished, this, &single_play::fresh);
    //delete animationGroup;
}

void single_play::on_gary1_clicked() {
    chesstype_gray = -1;
}

void single_play::on_gary2_clicked() {
    if (num_chess[1]) chesstype_gray = -2;
}

void single_play::on_gary3_clicked() {
    if (num_chess[0]) chesstype_gray = -3;
}

void single_play::on_green1_clicked() {
    chesstype_green = 1;
}

void single_play::on_green2_clicked() {
    if (num_chess[5]) chesstype_green = 2;
}

void single_play::on_green3_clicked() {
    if (num_chess[6]) chesstype_green = 3;
}

single_play::~single_play() {
    delete chessBoard;
    delete ui;
}

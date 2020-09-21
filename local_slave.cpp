#include "local_slave.h"
#include "ui_local_slave.h"
#include <QMessageBox>

local_slave::local_slave(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::local_slave) {
    wait = 1;
    ui->setupUi(this);
    connect(ui->actionback, &QAction::triggered, [=]() {
        emit showmain();
        this->close();
        delete this;
    });
    ui->num_chess1->setVisible(false);
    ui->num_chess2->setVisible(false);
    ui->num_chess3->setVisible(false);
    ui->label_2->setText("");
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    picname = new QString[7]{":/pic/chess_-3.png", ":/pic/chess_-2.png", ":/pic/chess_-1.png", "", ":/pic/chess_1.png",
                             ":/pic/chess_2.png", ":/pic/chess_3.png"};
    this->setFixedSize(this->size());
    animationGroup = new QParallelAnimationGroup(this);

}

void local_slave::get_socket(QTcpSocket *t) {
    tcpSocket = t;
    connect(tcpSocket, &QTcpSocket::readyRead, this, &local_slave::read_data);
}

void local_slave::read_data() {
    QString data = tcpSocket->readAll();
    if (wait == 1) {
        //QMessageBox::information(NULL,"提示",data);
        if (data == "rerps" || data == "first" || data == "second") {
            ui->chess1->setEnabled(true);
            ui->chess3->setEnabled(true);
            ui->chess2->setEnabled(true);
            if (data != "rerps") {
                if (data == "first")
                    order = -1;
                else if (data == "second")
                    order = 1;

                ui->chess1->setText("");
                ui->chess3->setText("");
                ui->chess2->setText("");
                ui->num_chess1->setVisible(true);
                ui->num_chess2->setVisible(true);
                ui->num_chess3->setVisible(true);
                ui->label_3->setVisible(true);
                ui->label_4->setVisible(true);
                chesstype = 1;
                ui->label_4->setPixmap(QPixmap(picname[chesstype * order + 3]));
                if (order == -1) {
                    wait = 2;
                    ui->label_2->setText("你的回合");
                } else {
                    wait = 3;
                    ui->label_2->setText("对手回合");
                }
                initialize(order);
            }
        } else {
            QMessageBox::information(NULL, "提示", "客机有点问题");
        }
    } else if (wait == 3) {
        if (data == "continue") wait = 2;
        else {
            QStringList list = data.split(',');
            int x = list[0].toInt();
            int y = list[1].toInt();
            int type = list[2].toInt();
            int con = list[3].toInt();

            chessBoard->step(x, y, type);
            cells[x][y]->setPixmap(QPixmap(picname[chessBoard->board[x][y].chessType + 3]).scaled(40, 40));
            movedChess = chessBoard->get_movedChess();
            num_chess[type + 3]--;
            turns++;
            chessBoard->offset(num_chess);
            action(order);
            //refresh_board(chessBoard);
            refresh_text();
            int reward = chessBoard->judge();
            if (reward == 1) {
                QString s = QString("青方胜利");
                QMessageBox::information(NULL, "", s);
                this->close();
                emit showmain();
                delete this;
            } else if (reward == -1) {
                QString s = QString("灰方胜利");
                QMessageBox::information(NULL, "", s);
                this->close();
                emit showmain();
                delete this;
            }
            if (!con) tcpSocket->write("continue");
            else {
                wait = 2;
                ui->label_2->setText("你的回合");
            }

        }
    }
}

void local_slave::initialize(int order) {
    chessBoard = new chessboard();
    turns = 0;
    QVector<QVector<cell_label *>> t(8, QVector<cell_label *>(8));
    cells = t;
    QVector<QVector<QLabel *>> board(8, QVector<QLabel *>(8));
    num_chess = new int[7]{1, 1, 30, 0, 30, 1, 1};
    chesstype = 1;


    ui->chess1->setIconSize(QSize(40, 40));
    ui->chess2->setIconSize(QSize(40, 40));
    ui->chess3->setIconSize(QSize(40, 40));
    if (order == -1) {
        ui->chess1->setIcon(QPixmap(picname[2]));
        ui->chess2->setIcon(QPixmap(picname[1]));
        ui->chess3->setIcon(QPixmap(picname[0]));
    } else {
        ui->chess1->setIcon(QPixmap(picname[4]));
        ui->chess2->setIcon(QPixmap(picname[5]));
        ui->chess3->setIcon(QPixmap(picname[6]));
    }
    refresh_text();
    int c = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessBoard->board[i][j].root == 1) {
                QLabel *temp = new QLabel(this);
                temp->setFixedSize(40, 40);
                temp->setVisible(true);
                temp->setStyleSheet("border:1px solid black");
                temp->setScaledContents(true);
                temp->setPixmap(QPixmap(":/pic/root_1.png").scaled(40, 40));
                if (order == 1) temp->move(20 + 40 * j, 64 + 40 * i);
                else temp->move(300 - 40 * j, 344 - 40 * i);
                c++;
            } else if (chessBoard->board[i][j].root == -1) {
                QLabel *temp = new QLabel(this);
                temp->setFixedSize(40, 40);
                temp->setVisible(true);
                temp->setStyleSheet("border:1px solid black");
                temp->setScaledContents(true);
                temp->setPixmap(QPixmap(":/pic/root_-1.png").scaled(40, 40));
                if (order == 1) temp->move(20 + 40 * j, 64 + 40 * i);
                else temp->move(300 - 40 * j, 344 - 40 * i);
            }

            board[i][j] = new QLabel(this);
            board[i][j]->setVisible(true);
            board[i][j]->setFixedSize(40, 40);
            board[i][j]->setScaledContents(true);
            board[i][j]->move(20 + 40 * j, 64 + 40 * i);
            board[i][j]->setStyleSheet("border:1px solid black");

            cells[i][j] = new cell_label(this);
            cells[i][j]->set_point(i, j);
            cells[i][j]->setVisible(true);
            cells[i][j]->setFixedSize(40, 40);
            cells[i][j]->setScaledContents(true);
            board[i][j]->stackUnder(cells[i][j]);
            //cells[i][j]->setStyleSheet("border:1px solid black");


            cells[i][j]->setPixmap(QPixmap(picname[chessBoard->board[i][j].chessType + 3]).scaled(40, 40));


            connect(cells[i][j], &cell_label::clicked, this, &local_slave::cells_clicked);
            //connect(cells[i][j], &cell_label::fresh, this, &local_slave::fresh);

        }
    }

    if (order == 1) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cells[i][j]->move(20 + 40 * j, 64 + 40 * i);
            }
        }
    } else {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cells[i][j]->move(300 - 40 * j, 344 - 40 * i);
            }
        }
    }
}

void local_slave::cells_clicked(int i, int j) {
    QMessageBox::information(NULL, "", "点到了");
    if (wait == 2) {
        QMessageBox::information(NULL, "", "回合正常");
        bool res = false;
        if (num_chess[chesstype * order + 3] > 0) {
            QMessageBox::information(NULL, "", "进入了棋盘");
            res = chessBoard->step(i, j, chesstype * order);
            if (res) {
                QMessageBox::information(NULL, "", "落子成功");
                //refresh_board(chessBoard);
                movedChess = chessBoard->get_movedChess();
                num_chess[chesstype * order + 3]--;
                cells[i][j]->setPixmap(QPixmap(picname[chessBoard->board[i][j].chessType + 3]).scaled(40, 40));
                turns++;
                QString data = QString("%1,%2,%3,").arg(i).arg(j).arg(chesstype * order);

                int s;
                if (order == -1) s = 1;
                else s = 3;
                if (turns < s) data += '0';
                else data += '1';
                tcpSocket->write(data.toUtf8());
                ui->label_2->setText("对手回合");
                chesstype = 1;
                ui->label_4->setPixmap(QPixmap(picname[chesstype * order + 3]));
                wait = 3;

                chessBoard->offset(num_chess);

                //refresh_board(chessBoard);
                refresh_text();
                int reward = chessBoard->judge();
                if (reward == 1) {
                    QString s = QString("青方胜利");
                    QMessageBox::information(NULL, "", s);
                    this->close();
                    emit showmain();
                    delete this;
                } else if (reward == -1) {
                    QString s = QString("灰方胜利");
                    QMessageBox::information(NULL, "", s);
                    this->close();
                    emit showmain();
                    delete this;
                }
            }
        }
    }
}

void local_slave::refresh_board(chessboard *chessBoard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cells[i][j]->setPixmap(QPixmap(picname[chessBoard->board[i][j].chessType + 3]).scaled(40, 40));

            if (order == 1) cells[i][j]->move(20 + 40 * j, 64 + 40 * i);
            else cells[i][j]->move(300 - 40 * j, 344 - 40 * i);
            cells[i][j]->raise();
        }
    }
}

void local_slave::refresh_text() {
    ui->num_chess1->setText(QString::number(num_chess[1 * order + 3]));
    ui->num_chess2->setText(QString::number(num_chess[2 * order + 3]));
    ui->num_chess3->setText(QString::number(num_chess[3 * order + 3]));
}

void local_slave::on_chess1_clicked() {
    if (wait == 1) {
        tcpSocket->write("rock");
        ui->chess1->setEnabled(false);
        ui->chess3->setEnabled(false);
        ui->chess2->setEnabled(false);
    } else {
        chesstype = 1;
        ui->label_4->setPixmap(QPixmap(picname[chesstype * order + 3]));
    }
}

void local_slave::on_chess2_clicked() {
    if (wait == 1) {
        tcpSocket->write("scissors");
        ui->chess1->setEnabled(false);
        ui->chess3->setEnabled(false);
        ui->chess2->setEnabled(false);
    } else {
        chesstype = 2;
        ui->label_4->setPixmap(QPixmap(picname[chesstype * order + 3]));
    }
}

void local_slave::on_chess3_clicked() {
    if (wait == 1) {
        tcpSocket->write("paper");
        ui->chess1->setEnabled(false);
        ui->chess3->setEnabled(false);
        ui->chess2->setEnabled(false);
    } else {
        chesstype = 3;
        ui->label_4->setPixmap(QPixmap(picname[chesstype * order + 3]));
    }
}

void local_slave::action(int order) {
    animationGroup->clear();
    while (!movedChess.empty()) {
        pair<point, char> t = movedChess.top();
        if (t.second == ' ') {
            movedChess.pop();
            continue;
        }
        QPropertyAnimation *t_anima;
        cell_label *movedLabel;
        if (order == 1) {
            switch (t.second) {
                case 'w':
                    t.second = 's';
                    break;
                case 's':
                    t.second = 'w';
                    break;
                case 'a':
                    t.second = 'd';
                    break;
                case 'd':
                    t.second = 'a';
                    break;
            }
        }
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
    connect(animationGroup, &QPropertyAnimation::finished, this, &local_slave::fresh);
    //delete animationGroup;
}

void local_slave::fresh() {
    refresh_board(chessBoard);
}

local_slave::~local_slave() {
    delete ui;
}

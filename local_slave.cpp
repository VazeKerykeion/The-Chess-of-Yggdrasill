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
            num_chess[type + 3]--;
            turns++;
            chessBoard->offset(num_chess);
            refresh_board(chessBoard);
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
                if (order == 1) temp->move(20 + 41 * j, 64 + 41 * i);
                else temp->move(307 - 41 * j, 351 - 41 * i);
                c++;
            } else if (chessBoard->board[i][j].root == -1) {
                QLabel *temp = new QLabel(this);
                temp->setFixedSize(40, 40);
                temp->setVisible(true);
                temp->setStyleSheet("border:1px solid black");
                temp->setScaledContents(true);
                temp->setPixmap(QPixmap(":/pic/root_-1.png").scaled(40, 40));
                if (order == 1) temp->move(20 + 41 * j, 64 + 41 * i);
                else temp->move(307 - 41 * j, 351 - 41 * i);
            }

            cell_label *cell = new cell_label(this);
            cells[i][j] = cell;
            cells[i][j]->set_point(i, j);
            cells[i][j]->setVisible(true);
            cells[i][j]->setFixedSize(40, 40);
            cells[i][j]->setScaledContents(true);

            cells[i][j]->setStyleSheet("border:1px solid black");


            cells[i][j]->setPixmap(QPixmap(picname[chessBoard->board[i][j].chessType + 3]).scaled(40, 40));


            connect(cells[i][j], &cell_label::clicked, this, &local_slave::cells_clicked);

        }
    }

    if (order == 1) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cells[i][j]->move(20 + 41 * j, 64 + 41 * i);
            }
        }
    } else {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                cells[i][j]->move(307 - 41 * j, 351 - 41 * i);
            }
        }
    }
}

void local_slave::cells_clicked(int i, int j) {
    if (wait == 2) {
        bool res = false;
        if (num_chess[chesstype * order + 3] > 0) {
            res = chessBoard->step(i, j, chesstype * order);
            if (res) {
                refresh_board(chessBoard);
                num_chess[chesstype * order + 3]--;
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

void local_slave::fresh() {
    refresh_board(chessBoard);
}

local_slave::~local_slave() {
    delete ui;
}

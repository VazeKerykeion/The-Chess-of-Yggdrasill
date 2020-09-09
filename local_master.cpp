#include "local_master.h"
#include "ui_local_master.h"
#include "chessBoard.h"
#include "cell_label.h"
#include <QMessageBox>

local_master::local_master(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::local_master) {
    ui->setupUi(this);
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &local_master::new_client);
    tcpServer->listen(QHostAddress::Any, 9888);
    wait = 0;
    ui->chess1->setVisible(false);
    ui->chess3->setVisible(false);
    ui->chess2->setVisible(false);
    count_rps = 0;
    master_rps = 0;
    slave_rps = 0;

}

void local_master::new_client() {
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, &QTcpSocket::readyRead, this, &local_master::read_data);
}

void local_master::read_data() {
    QString data = tcpSocket->readAll();
    if (wait) {
        if (wait == 1) {
            //QMessageBox::information(NULL,"提示",data);
            if (data == "chess1") slave_rps = 1;
            else if (data == "chess2") slave_rps = 2;
            else if (data == "chess3") slave_rps = 3;
            count_rps++;
            if (count_rps == 2) {
                first_second();
            }
        }
    } else {
        if (data == "game start") {
            wait = 1;
            ui->label->setVisible(false);
            ui->chess1->setVisible(true);
            ui->chess3->setVisible(true);
            ui->chess2->setVisible(true);
        }
    }
}

void local_master::on_chess1_clicked() {
    if (wait == 1) {
        count_rps++;
        master_rps = 1;
        ui->chess1->setEnabled(false);
        ui->chess3->setEnabled(false);
        ui->chess2->setEnabled(false);
        if (count_rps == 2) {
            first_second();
        }
    }
}

void local_master::on_chess2_clicked() {
    if (wait == 1) {
        count_rps++;
        master_rps = 2;
        ui->chess1->setEnabled(false);
        ui->chess3->setEnabled(false);
        ui->chess2->setEnabled(false);
        if (count_rps == 2) {
            first_second();
        }
    }
}

void local_master::on_chess3_clicked() {
    if (wait == 1) {
        count_rps++;
        master_rps = 3;
        ui->chess1->setEnabled(false);
        ui->chess3->setEnabled(false);
        ui->chess2->setEnabled(false);
        if (count_rps == 2) {
            first_second();
        }
    }
}

void local_master::first_second() {

    if (master_rps == slave_rps) {
        master_rps = 0;
        slave_rps = 0;
        count_rps = 0;
        ui->chess1->setEnabled(true);
        ui->chess3->setEnabled(true);
        ui->chess2->setEnabled(true);
        tcpSocket->write("rerps");
        //QMessageBox::information(NULL,"提示","平局，重新猜拳");
    } else if (master_rps == 0 || slave_rps == 0) {
        QMessageBox::information(NULL, "提示", "有点问题");
    } else {
        if ((master_rps == 1 && slave_rps == 2) || (master_rps == 2 && slave_rps == 3) ||
            (master_rps == 3 && slave_rps == 1)) {
            order = -1;
            ui->textEdit->setText("先手");
            tcpSocket->write("second");
            //QMessageBox::information(NULL,"提示","胜利，先手");
        } else if ((master_rps == 3 && slave_rps == 2) || (master_rps == 1 && slave_rps == 3) ||
                   (master_rps == 2 && slave_rps == 1)) {
            order = 1;
            ui->textEdit->setText("后手");
            tcpSocket->write("first");
        }
        //QMessageBox::information(NULL,"提示","失败，后手");

        ui->chess1->setText("");
        ui->chess3->setText("");
        ui->chess2->setText("");
        wait = 2;
        initialize(order);

    }
}

void local_master::initialize(int order) {
    chessBoard = new chessboard();
    turns = 0;
    QVector<QVector<cell_label *>> t(8, QVector<cell_label *>(8));
    cells = t;

    num_chess = new int[3]{30, 1, 1};
    chesstype = order;

    //camp = -1;

    ui->chess1->setIconSize(QSize(40, 40));
    ui->chess2->setIconSize(QSize(40, 40));
    ui->chess3->setIconSize(QSize(40, 40));
    if (order == -1) {
        ui->chess1->setIcon(QPixmap(":/pic/chess_-1.png"));
        ui->chess2->setIcon(QPixmap(":/pic/chess_-2.png"));
        ui->chess3->setIcon(QPixmap(":/pic/chess_-3.png"));
    } else {
        ui->chess1->setIcon(QPixmap(":/pic/chess_1.png"));
        ui->chess2->setIcon(QPixmap(":/pic/chess_2.png"));
        ui->chess3->setIcon(QPixmap(":/pic/chess_3.png"));
    }
    /*
    refresh_text();
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            if(chessBoard->board[i][j].root == 1) {
                QLabel *temp = new QLabel(this);
                temp->setFixedSize(40, 40);
                temp->setStyleSheet("border:1px solid black");
                temp->setScaledContents(true);
                temp->setPixmap(QPixmap(":/pic/root_1.png").scaled(40, 40));
                temp->move(81 + 41 * j, 64 + 41 * i);
            } else if (chessBoard->board[i][j].root == -1) {
                QLabel *temp = new QLabel(this);
                temp->setFixedSize(40, 40);
                temp->setStyleSheet("border:1px solid black");
                temp->setScaledContents(true);
                temp->setPixmap(QPixmap(":/pic/root_-1.png").scaled(40, 40));
                temp->move(81 + 41 * j, 64 + 41 * i);
            }

            cell_label *cell = new cell_label(this);
            cells[i][j] = cell;
            cells[i][j]->setVisible(true);
            cells[i][j]->setFixedSize(40, 40);
            cells[i][j]->setScaledContents(true);
            cells[i][j]->move(81 + 41 * j, 64 + 41 * i);
            cells[i][j]->setStyleSheet("border:1px solid black");

            if (chessBoard->board[i][j].chessType == 1) {
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_1.png").scaled(40, 40));
            } else if (chessBoard->board[i][j].chessType == -1) {
                cells[i][j]->setPixmap(QPixmap(":/pic/chess_-1.png").scaled(40, 40));
            }


            connect(cells[i][j], &cell_label::clicked, [=] {
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
                    turns++;
                    if (turns < 2) camp = -1;
                    else if (turns >= 2 && turns < 4) camp = 1;
                    else camp = -camp;

                    chessBoard->offset(num_chess);
                    //Sleep(1000);
                    refresh_board(chessBoard);
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

            });
        }
    }
    */
}

void local_master::refresh_text() {
    ui->num_chess1->setText(QString::number(num_chess[0]));
    ui->num_chess2->setText(QString::number(num_chess[1]));
    ui->num_chess3->setText(QString::number(num_chess[2]));
}

local_master::~local_master() {
    delete ui;
}


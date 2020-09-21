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
    connect(ui->actionback, &QAction::triggered, [=]() {
        emit showmain();
        this->close();
        delete this;
    });
    tcpServer->listen(QHostAddress::Any, 9888);
    wait = 0;
    ui->chess1->setVisible(false);
    ui->chess3->setVisible(false);
    ui->chess2->setVisible(false);
    ui->num_chess1->setVisible(false);
    ui->num_chess2->setVisible(false);
    ui->num_chess3->setVisible(false);
    ui->label_2->setText("");
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    picname = new QString[7]{":/pic/chess_-3.png", ":/pic/chess_-2.png", ":/pic/chess_-1.png", "", ":/pic/chess_1.png",
                             ":/pic/chess_2.png", ":/pic/chess_3.png"};
    count_rps = 0;
    master_rps = 0;
    slave_rps = 0;
    this->setFixedSize(this->size());
    animationGroup = new QParallelAnimationGroup(this);

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
            if (data == "rock") slave_rps = 1;
            else if (data == "scissors") slave_rps = 2;
            else if (data == "paper") slave_rps = 3;
            count_rps++;
            if (count_rps == 2) {
                first_second();
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
                movedChess = chessBoard->get_movedChess();
                num_chess[type + 3]--;
                turns++;
                cells[x][y]->setPixmap(QPixmap(picname[chessBoard->board[x][y].chessType + 3]).scaled(40, 40));
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
            tcpSocket->write("second");
            //QMessageBox::information(NULL,"提示","胜利，先手");
        } else if ((master_rps == 3 && slave_rps == 2) || (master_rps == 1 && slave_rps == 3) ||
                   (master_rps == 2 && slave_rps == 1)) {
            order = 1;
            tcpSocket->write("first");
        }
        //QMessageBox::information(NULL,"提示","失败，后手");

        ui->chess1->setText("");
        ui->chess3->setText("");
        ui->chess2->setText("");
        ui->chess1->setEnabled(true);
        ui->chess3->setEnabled(true);
        ui->chess2->setEnabled(true);
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
}

void local_master::initialize(int order) {
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
    for(int i = 0 ; i < 8 ; i++){
        for(int j = 0 ; j < 8 ; j++){
            if(chessBoard->board[i][j].root == 1) {
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

            //cells[i][j]->setStyleSheet("border:1px solid black");
            cells[i][j]->setPixmap(QPixmap(picname[chessBoard->board[i][j].chessType + 3]).scaled(40, 40));
            board[i][j]->lower();

            connect(cells[i][j], &cell_label::clicked, this, &local_master::cells_clicked);
            //connect(cells[i][j], &cell_label::fresh, this, &local_master::fresh);
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

void local_master::cells_clicked(int i, int j) {

    if (wait == 2) {
        bool res = false;
        if (num_chess[chesstype * order + 3] > 0) {
            res = chessBoard->step(i, j, chesstype * order);
            if (res) {
                movedChess = chessBoard->get_movedChess();
                num_chess[chesstype * order + 3]--;
                cells[i][j]->setPixmap(QPixmap(picname[chessBoard->board[i][j].chessType + 3]).scaled(40, 40));
                //refresh_board(chessBoard);
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
                //if(movedChess.size()>1) QMessageBox::information(NULL,"","播放动画");
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
            }
        }
    }
}

void local_master::refresh_board(chessboard *chessBoard) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cells[i][j]->setPixmap(QPixmap(picname[chessBoard->board[i][j].chessType + 3]).scaled(40, 40));
            if (order == 1) cells[i][j]->move(20 + 40 * j, 64 + 40 * i);
            else cells[i][j]->move(300 - 40 * j, 344 - 40 * i);
            cells[i][j]->raise();
        }
    }
}

void local_master::refresh_text() {
    ui->num_chess1->setText(QString::number(num_chess[1 * order + 3]));
    ui->num_chess2->setText(QString::number(num_chess[2 * order + 3]));
    ui->num_chess3->setText(QString::number(num_chess[3 * order + 3]));
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
    } else {
        chesstype = 1;
        ui->label_4->setPixmap(QPixmap(picname[chesstype * order + 3]));
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
    } else {
        chesstype = 2;
        ui->label_4->setPixmap(QPixmap(picname[chesstype * order + 3]));

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
    } else {
        chesstype = 3;
        ui->label_4->setPixmap(QPixmap(picname[chesstype * order + 3]));
    }
}

void local_master::action(int order) {
    animationGroup->clear();
    while (!movedChess.empty()) {
        pair<point, char> t = movedChess.top();
        if (t.second == ' ') {
            movedChess.pop();
            continue;
        }
        QPropertyAnimation *t_anima;
        cell_label *movedLabel;

        int dir = 40 * order;
        switch (t.second) {
            case 'w':
                movedLabel = cells[t.first.x + 1][t.first.y];
                t_anima = new QPropertyAnimation(movedLabel, "pos");
                t_anima->setDuration(500);
                t_anima->setStartValue(QPoint(movedLabel->x(), movedLabel->y()));
                t_anima->setEndValue(QPoint(movedLabel->x(), movedLabel->y() - dir));
                break;
            case 's':
                movedLabel = cells[t.first.x - 1][t.first.y];
                t_anima = new QPropertyAnimation(movedLabel, "pos");
                t_anima->setDuration(500);
                t_anima->setStartValue(QPoint(movedLabel->x(), movedLabel->y()));
                t_anima->setEndValue(QPoint(movedLabel->x(), movedLabel->y() + dir));
                break;
            case 'a':
                movedLabel = cells[t.first.x][t.first.y + 1];
                t_anima = new QPropertyAnimation(movedLabel, "pos");
                t_anima->setDuration(500);
                t_anima->setStartValue(QPoint(movedLabel->x(), movedLabel->y()));
                t_anima->setEndValue(QPoint(movedLabel->x() - dir, movedLabel->y()));
                break;
            case 'd':
                movedLabel = cells[t.first.x][t.first.y - 1];
                t_anima = new QPropertyAnimation(movedLabel, "pos");
                t_anima->setDuration(500);
                t_anima->setStartValue(QPoint(movedLabel->x(), movedLabel->y()));
                t_anima->setEndValue(QPoint(movedLabel->x() + dir, movedLabel->y()));
                break;
            default:
                break;
        }

        t_anima->setEasingCurve(QEasingCurve::InOutQuad);
        //t_anima->start();
        animationGroup->addAnimation(t_anima);
        movedChess.pop();
    }

    animationGroup->start();
    connect(animationGroup, &QPropertyAnimation::finished, this, &local_master::fresh);
    //delete animationGroup;
}

void local_master::fresh() {
    refresh_board(chessBoard);
}

local_master::~local_master() {
    delete ui;
}


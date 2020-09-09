#include "mainwindow.h"
#include "local_choice.h"
#include "single_play.h"
#include <ui_mainwindow.h>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle(tr("世界树棋"));
    ui->doubleplayer->setText(tr("本地游戏"));
    ui->localonline->setText(tr("局域网联机"));
    ui->online->setText(tr("服务器联机"));
    model = 0;


}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    bool result=pix.load(":/pic/1.jpg");
    if(!result) QMessageBox::warning(this, "Waring","加载错误",QMessageBox::Yes);
    //else QMessageBox::warning(this, "Waring","加载成功",QMessageBox::Yes);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    return;
}
*/

void MainWindow::rec(int a){
    model=a;
}

void MainWindow::on_doubleplayer_clicked() {
    single = new single_play();
    connect(single, &single_play::showmain, this, &MainWindow::show);
    single->show();
    this->hide();
}

void MainWindow::on_localonline_clicked() {
    l1 = new local_choice();
    connect(l1, &local_choice::choice, this, &MainWindow::rec);
    l1->exec();

    if (model == 1) {

        localMaster = new local_master();
        localMaster->show();
        this->hide();

    } else if (model == 2) {

        con = new connection();
        connect(this, &MainWindow::con_mode, con, &connection::change_mode);
        connect(con, &connection::showmain, this, &MainWindow::show);
        emit con_mode(1);
        con->show();
        this->hide();

    }
    //this->show();
}

void MainWindow::on_online_clicked() {
    con = new connection();
    connect(this, &MainWindow::con_mode, con, &connection::change_mode);
    connect(con, &connection::showmain, this, &MainWindow::show);
    con->show();
    this->hide();
}


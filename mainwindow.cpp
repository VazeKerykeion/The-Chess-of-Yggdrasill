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
    connect(&l1, &local_choice::choice, this, &MainWindow::rec);
    connect(&con, &connection::showmain, this, &MainWindow::show);
    connect(&single, &single_play::showmain, this, &MainWindow::show);
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
    single.show();
    this->hide();
}

void MainWindow::on_localonline_clicked(){
    l1.exec();
    if(model==1){

    }else{

    }
    //this->show();
}

void MainWindow::on_online_clicked() {
    con.show();
    this->hide();
}


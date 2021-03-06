#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "local_choice.h"
#include "connection.h"
#include "single_play.h"
#include "local_master.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    //void paintEvent(QPaintEvent *);
private slots:

    void on_localonline_clicked();

    void on_online_clicked();

    void on_doubleplayer_clicked();

    void rec(int a);

signals:

    void con_mode(int a);

private:
    Ui::MainWindow *ui;
    local_choice *l1;
    connection *con;
    single_play *single;
    local_master *localMaster;
    int model;

};

#endif // MAINWINDOW_H

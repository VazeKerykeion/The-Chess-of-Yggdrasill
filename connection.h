#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMainWindow>

namespace Ui {
class connection;
}

class connection : public QMainWindow
{
    Q_OBJECT
signals:
    void showmain();
public:
    explicit connection(QWidget *parent = nullptr);
    ~connection();

private slots:
    void on_pushButton_3_clicked();
private:
    Ui::connection *ui;

};

#endif // CONNECTION_H

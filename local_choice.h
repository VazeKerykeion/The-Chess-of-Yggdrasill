#ifndef LOCAL_CHOICE_H
#define LOCAL_CHOICE_H

#include <QDialog>

namespace Ui {
class local_choice;
}

class local_choice : public QDialog
{
    Q_OBJECT
signals:

    void showmain();

    void choice(int a);

public:
    explicit local_choice(QWidget *parent = nullptr);

    ~local_choice();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::local_choice *ui;
};

#endif // LOCAL_CHOICE_H

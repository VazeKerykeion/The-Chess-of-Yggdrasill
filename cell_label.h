//
// Created by 10031 on 2020/7/25.
//

#ifndef HELLO_CELL_LABEL_H
#define HELLO_CELL_LABEL_H
#include <QLabel>

class cell_label : public QLabel {
Q_OBJECT
public:
    cell_label(QWidget *parent = 0);

    void set_point(int x, int y);

protected:
    void mouseReleaseEvent(QMouseEvent *ev);

signals:

    void clicked(int i, int j);

private:
    int i;
    int j;

public slots:

};


#endif //HELLO_CELL_LABEL_H

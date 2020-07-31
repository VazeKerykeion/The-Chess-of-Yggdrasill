//
// Created by 10031 on 2020/7/25.
//

#ifndef HELLO_CELL_LABEL_H
#define HELLO_CELL_LABEL_H
#include <QLabel>

class cell_label :public QLabel{
    Q_OBJECT
public:
    cell_label(QWidget * parent = 0);
protected:
    void mouseReleaseEvent(QMouseEvent * ev);
signals:
    void clicked();


public slots:

};


#endif //HELLO_CELL_LABEL_H

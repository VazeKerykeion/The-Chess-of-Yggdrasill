//
// Created by 10031 on 2020/7/25.
//
#include <QMouseEvent>
#include "cell_label.h"

cell_label::cell_label(QWidget *parent) :QLabel(parent){

}

void cell_label::mouseReleaseEvent(QMouseEvent * ev) {
    if(ev->button() == Qt::LeftButton)
    {
        Q_UNUSED(ev)
        emit clicked();
    }
}

/********************************************************************************
** Form generated from reading UI file 'local_choice.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCAL_CHOICE_H
#define UI_LOCAL_CHOICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_local_choice
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QDialog *local_choice)
    {
        if (local_choice->objectName().isEmpty())
            local_choice->setObjectName(QString::fromUtf8("local_choice"));
        local_choice->resize(344, 157);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        local_choice->setPalette(palette);
        local_choice->setAutoFillBackground(false);
        pushButton = new QPushButton(local_choice);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 100, 75, 23));
        pushButton_2 = new QPushButton(local_choice);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 100, 75, 23));
        label = new QLabel(local_choice);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 10, 231, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("8514oem"));
        font.setPointSize(20);
        label->setFont(font);

        retranslateUi(local_choice);

        QMetaObject::connectSlotsByName(local_choice);
    } // setupUi

    void retranslateUi(QDialog *local_choice)
    {
        local_choice->setWindowTitle(QCoreApplication::translate("local_choice", "\346\217\220\347\244\272", nullptr));
        pushButton->setText(QCoreApplication::translate("local_choice", "\346\210\220\344\270\272\346\210\277\344\270\273", nullptr));
        pushButton_2->setText(QCoreApplication::translate("local_choice", "\345\212\240\345\205\245\346\270\270\346\210\217", nullptr));
        label->setText(QCoreApplication::translate("local_choice", "\351\200\211\346\213\251\346\210\220\344\270\272\346\210\277\344\270\273\346\210\226\345\212\240\345\205\245\346\270\270\346\210\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class local_choice: public Ui_local_choice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCAL_CHOICE_H

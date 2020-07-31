/********************************************************************************
** Form generated from reading UI file 'connection.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTION_H
#define UI_CONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_connection
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextEdit *textEdit;
    QLabel *label_2;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QLabel *label_3;
    QTextEdit *textEdit_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QMainWindow *connection)
    {
        if (connection->objectName().isEmpty())
            connection->setObjectName(QString::fromUtf8("connection"));
        connection->resize(456, 297);
        centralwidget = new QWidget(connection);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 50, 60, 25));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(110, 50, 201, 25));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 100, 60, 25));
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(110, 100, 141, 25));
        textEdit_3 = new QTextEdit(centralwidget);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setGeometry(QRect(260, 100, 51, 25));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 150, 60, 25));
        textEdit_4 = new QTextEdit(centralwidget);
        textEdit_4->setObjectName(QString::fromUtf8("textEdit_4"));
        textEdit_4->setGeometry(QRect(110, 150, 201, 25));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(330, 100, 75, 23));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 220, 75, 23));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(220, 220, 75, 23));
        connection->setCentralWidget(centralwidget);

        retranslateUi(connection);

        QMetaObject::connectSlotsByName(connection);
    } // setupUi

    void retranslateUi(QMainWindow *connection)
    {
        connection->setWindowTitle(QCoreApplication::translate("connection", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("connection", "\347\216\251\345\256\266\345\220\215\347\247\260", nullptr));
        label_2->setText(QCoreApplication::translate("connection", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", nullptr));
        label_3->setText(QCoreApplication::translate("connection", "\350\201\224\346\234\272\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("connection", "\350\277\236\346\216\245\346\265\213\350\257\225", nullptr));
        pushButton_2->setText(QCoreApplication::translate("connection", "\345\212\240\345\205\245\346\270\270\346\210\217", nullptr));
        pushButton_3->setText(QCoreApplication::translate("connection", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class connection: public Ui_connection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTION_H

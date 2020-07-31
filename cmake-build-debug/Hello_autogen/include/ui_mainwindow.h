/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *doubleplayer;
    QPushButton *localonline;
    QPushButton *online;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(286, 445);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        doubleplayer = new QPushButton(centralWidget);
        doubleplayer->setObjectName(QString::fromUtf8("doubleplayer"));
        doubleplayer->setGeometry(QRect(90, 80, 100, 50));
        localonline = new QPushButton(centralWidget);
        localonline->setObjectName(QString::fromUtf8("localonline"));
        localonline->setGeometry(QRect(90, 180, 100, 50));
        online = new QPushButton(centralWidget);
        online->setObjectName(QString::fromUtf8("online"));
        online->setGeometry(QRect(90, 280, 100, 50));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\270\226\347\225\214\346\240\221\346\243\213", nullptr));
        doubleplayer->setText(QCoreApplication::translate("MainWindow", "\346\234\254\345\234\260\346\270\270\346\210\217", nullptr));
        localonline->setText(QCoreApplication::translate("MainWindow", "\345\261\200\345\237\237\347\275\221\350\201\224\346\234\272", nullptr));
        online->setText(QCoreApplication::translate("MainWindow", "\344\272\222\350\201\224\347\275\221\350\201\224\346\234\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

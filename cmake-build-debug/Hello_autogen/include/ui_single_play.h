/********************************************************************************
** Form generated from reading UI file 'single_play.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLE_PLAY_H
#define UI_SINGLE_PLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_single_play
{
public:
    QAction *actionback;
    QAction *actionquit;
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *gary1;
    QPushButton *gary2;
    QLabel *num_gary1;
    QLabel *num_gary2;
    QPushButton *gary3;
    QLabel *num_gary3;
    QPushButton *green1;
    QLabel *num_green1;
    QPushButton *green2;
    QLabel *num_green2;
    QPushButton *green3;
    QLabel *num_green3;
    QMenuBar *menubar;
    QMenu *menuquit;

    void setupUi(QMainWindow *single_play)
    {
        if (single_play->objectName().isEmpty())
            single_play->setObjectName(QString::fromUtf8("single_play"));
        single_play->resize(511, 600);
        single_play->setStyleSheet(QString::fromUtf8(""));
        actionback = new QAction(single_play);
        actionback->setObjectName(QString::fromUtf8("actionback"));
        actionquit = new QAction(single_play);
        actionquit->setObjectName(QString::fromUtf8("actionquit"));
        centralwidget = new QWidget(single_play);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 40, 331, 331));
        label->setStyleSheet(QString::fromUtf8(""));
        gary1 = new QPushButton(centralwidget);
        gary1->setObjectName(QString::fromUtf8("gary1"));
        gary1->setGeometry(QRect(20, 500, 40, 40));
        gary2 = new QPushButton(centralwidget);
        gary2->setObjectName(QString::fromUtf8("gary2"));
        gary2->setGeometry(QRect(100, 500, 40, 40));
        num_gary1 = new QLabel(centralwidget);
        num_gary1->setObjectName(QString::fromUtf8("num_gary1"));
        num_gary1->setGeometry(QRect(60, 500, 40, 40));
        num_gary1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        num_gary2 = new QLabel(centralwidget);
        num_gary2->setObjectName(QString::fromUtf8("num_gary2"));
        num_gary2->setGeometry(QRect(140, 500, 40, 40));
        num_gary2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gary3 = new QPushButton(centralwidget);
        gary3->setObjectName(QString::fromUtf8("gary3"));
        gary3->setGeometry(QRect(180, 500, 40, 40));
        num_gary3 = new QLabel(centralwidget);
        num_gary3->setObjectName(QString::fromUtf8("num_gary3"));
        num_gary3->setGeometry(QRect(220, 500, 40, 40));
        num_gary3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        green1 = new QPushButton(centralwidget);
        green1->setObjectName(QString::fromUtf8("green1"));
        green1->setGeometry(QRect(260, 500, 40, 40));
        num_green1 = new QLabel(centralwidget);
        num_green1->setObjectName(QString::fromUtf8("num_green1"));
        num_green1->setGeometry(QRect(300, 500, 40, 40));
        num_green1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        green2 = new QPushButton(centralwidget);
        green2->setObjectName(QString::fromUtf8("green2"));
        green2->setGeometry(QRect(340, 500, 40, 40));
        num_green2 = new QLabel(centralwidget);
        num_green2->setObjectName(QString::fromUtf8("num_green2"));
        num_green2->setGeometry(QRect(380, 500, 40, 40));
        num_green2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        green3 = new QPushButton(centralwidget);
        green3->setObjectName(QString::fromUtf8("green3"));
        green3->setGeometry(QRect(420, 500, 40, 40));
        num_green3 = new QLabel(centralwidget);
        num_green3->setObjectName(QString::fromUtf8("num_green3"));
        num_green3->setGeometry(QRect(460, 500, 40, 40));
        num_green3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        single_play->setCentralWidget(centralwidget);
        menubar = new QMenuBar(single_play);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 511, 23));
        menuquit = new QMenu(menubar);
        menuquit->setObjectName(QString::fromUtf8("menuquit"));
        single_play->setMenuBar(menubar);

        menubar->addAction(menuquit->menuAction());
        menuquit->addAction(actionback);
        menuquit->addAction(actionquit);

        retranslateUi(single_play);
        QObject::connect(actionquit, SIGNAL(triggered()), single_play, SLOT(close()));

        QMetaObject::connectSlotsByName(single_play);
    } // setupUi

    void retranslateUi(QMainWindow *single_play)
    {
        single_play->setWindowTitle(QCoreApplication::translate("single_play", "MainWindow", nullptr));
        actionback->setText(QCoreApplication::translate("single_play", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
        actionquit->setText(QCoreApplication::translate("single_play", "\351\200\200\345\207\272", nullptr));
        label->setText(QString());
        gary1->setText(QString());
        gary2->setText(QString());
        num_gary1->setText(QString());
        num_gary2->setText(QString());
        gary3->setText(QString());
        num_gary3->setText(QString());
        green1->setText(QString());
        num_green1->setText(QString());
        green2->setText(QString());
        num_green2->setText(QString());
        green3->setText(QString());
        num_green3->setText(QString());
        menuquit->setTitle(QCoreApplication::translate("single_play", "\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class single_play: public Ui_single_play {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLE_PLAY_H

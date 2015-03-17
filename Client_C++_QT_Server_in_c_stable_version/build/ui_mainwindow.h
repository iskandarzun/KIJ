/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QToolButton *menuLoginButton;
    QToolButton *menuSignupButton;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *serverAddress;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(375, 257);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        menuLoginButton = new QToolButton(centralWidget);
        menuLoginButton->setObjectName(QStringLiteral("menuLoginButton"));
        menuLoginButton->setGeometry(QRect(40, 140, 131, 51));
        menuSignupButton = new QToolButton(centralWidget);
        menuSignupButton->setObjectName(QStringLiteral("menuSignupButton"));
        menuSignupButton->setGeometry(QRect(200, 140, 131, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 20, 261, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 80, 101, 16));
        serverAddress = new QLineEdit(centralWidget);
        serverAddress->setObjectName(QStringLiteral("serverAddress"));
        serverAddress->setGeometry(QRect(140, 80, 181, 21));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 375, 22));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Selamat Datang di WeChat!", 0));
        menuLoginButton->setText(QApplication::translate("MainWindow", "LOGIN", 0));
        menuSignupButton->setText(QApplication::translate("MainWindow", "DAFTAR", 0));
        label->setText(QApplication::translate("MainWindow", "SELAMAT DATANG DI PROGRAM WECHAT", 0));
        label_2->setText(QApplication::translate("MainWindow", "Alamat Server :", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

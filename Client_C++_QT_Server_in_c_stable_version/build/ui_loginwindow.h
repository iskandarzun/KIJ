/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

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
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *usernameLogin;
    QLineEdit *passwordLogin;
    QToolButton *backButton;
    QToolButton *loginButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QStringLiteral("LoginWindow"));
        LoginWindow->resize(383, 240);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 321, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 70, 71, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 100, 71, 16));
        usernameLogin = new QLineEdit(centralwidget);
        usernameLogin->setObjectName(QStringLiteral("usernameLogin"));
        usernameLogin->setGeometry(QRect(120, 70, 201, 21));
        passwordLogin = new QLineEdit(centralwidget);
        passwordLogin->setObjectName(QStringLiteral("passwordLogin"));
        passwordLogin->setGeometry(QRect(120, 100, 201, 21));
        passwordLogin->setEchoMode(QLineEdit::Password);
        backButton = new QToolButton(centralwidget);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(40, 150, 131, 41));
        loginButton = new QToolButton(centralwidget);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(210, 150, 131, 41));
        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 383, 22));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        LoginWindow->setStatusBar(statusbar);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "Login", 0));
        label->setText(QApplication::translate("LoginWindow", "Silahkan Masukkan Username dan Password anda!", 0));
        label_2->setText(QApplication::translate("LoginWindow", "Username :", 0));
        label_3->setText(QApplication::translate("LoginWindow", "Password  :", 0));
        backButton->setText(QApplication::translate("LoginWindow", "KEMBALI", 0));
        loginButton->setText(QApplication::translate("LoginWindow", "LOGIN", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

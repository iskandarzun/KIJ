/********************************************************************************
** Form generated from reading UI file 'signupwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPWINDOW_H
#define UI_SIGNUPWINDOW_H

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

class Ui_SignupWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *signupUsername;
    QLineEdit *signupPassword;
    QLineEdit *signupConfirmPassword;
    QToolButton *signupButton;
    QToolButton *backButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SignupWindow)
    {
        if (SignupWindow->objectName().isEmpty())
            SignupWindow->setObjectName(QStringLiteral("SignupWindow"));
        SignupWindow->resize(429, 267);
        centralwidget = new QWidget(SignupWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 20, 221, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 80, 71, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(120, 40, 191, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(70, 110, 71, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 140, 121, 16));
        signupUsername = new QLineEdit(centralwidget);
        signupUsername->setObjectName(QStringLiteral("signupUsername"));
        signupUsername->setGeometry(QRect(160, 80, 221, 21));
        signupPassword = new QLineEdit(centralwidget);
        signupPassword->setObjectName(QStringLiteral("signupPassword"));
        signupPassword->setGeometry(QRect(160, 110, 221, 21));
        signupPassword->setEchoMode(QLineEdit::Password);
        signupConfirmPassword = new QLineEdit(centralwidget);
        signupConfirmPassword->setObjectName(QStringLiteral("signupConfirmPassword"));
        signupConfirmPassword->setGeometry(QRect(160, 140, 221, 21));
        signupConfirmPassword->setEchoMode(QLineEdit::Password);
        signupButton = new QToolButton(centralwidget);
        signupButton->setObjectName(QStringLiteral("signupButton"));
        signupButton->setGeometry(QRect(240, 180, 131, 41));
        backButton = new QToolButton(centralwidget);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(60, 180, 131, 41));
        SignupWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SignupWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 429, 22));
        SignupWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SignupWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SignupWindow->setStatusBar(statusbar);

        retranslateUi(SignupWindow);

        QMetaObject::connectSlotsByName(SignupWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SignupWindow)
    {
        SignupWindow->setWindowTitle(QApplication::translate("SignupWindow", "Daftar Akun", 0));
        label->setText(QApplication::translate("SignupWindow", "Silahkan Masukkan data akun anda", 0));
        label_2->setText(QApplication::translate("SignupWindow", "Username :", 0));
        label_3->setText(QApplication::translate("SignupWindow", "(Rahasiakan password anda!!)", 0));
        label_4->setText(QApplication::translate("SignupWindow", "Password  :", 0));
        label_5->setText(QApplication::translate("SignupWindow", "Confirm Password :", 0));
        signupButton->setText(QApplication::translate("SignupWindow", "DAFTAR", 0));
        backButton->setText(QApplication::translate("SignupWindow", "KEMBALI", 0));
    } // retranslateUi

};

namespace Ui {
    class SignupWindow: public Ui_SignupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPWINDOW_H

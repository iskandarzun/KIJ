/********************************************************************************
** Form generated from reading UI file 'menuwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWINDOW_H
#define UI_MENUWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *connectWindow;
    QLineEdit *serverAddress;
    QLabel *label;
    QLabel *label_2;
    QToolButton *chooseSignupButton;
    QToolButton *chooseLoginButton;
    QLabel *serverError;
    QWidget *loginWindow;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *usernameLogin;
    QLineEdit *passwordLogin;
    QToolButton *loginButton;
    QToolButton *backButtonOnLogin;
    QLabel *passwordLoginError;
    QLabel *userLoginError;
    QWidget *signupWindow;
    QLineEdit *usernameSignup;
    QLineEdit *passwordSignup;
    QLineEdit *confirmPasswordSignup;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QToolButton *signupButton;
    QToolButton *backButtonOnSignup;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *passwordSignupError;
    QLabel *userSignupError;
    QWidget *ChatWindow;
    QListWidget *listUserWidget;
    QLabel *label_11;
    QTextEdit *chatTextEdit;
    QLineEdit *chatMessage;
    QLabel *label_12;
    QLabel *label_13;
    QToolButton *sendButton;
    QToolButton *logoutButton;
    QLabel *loggedUser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MenuWindow)
    {
        if (MenuWindow->objectName().isEmpty())
            MenuWindow->setObjectName(QStringLiteral("MenuWindow"));
        MenuWindow->resize(551, 311);
        centralWidget = new QWidget(MenuWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 551, 251));
        connectWindow = new QWidget();
        connectWindow->setObjectName(QStringLiteral("connectWindow"));
        serverAddress = new QLineEdit(connectWindow);
        serverAddress->setObjectName(QStringLiteral("serverAddress"));
        serverAddress->setGeometry(QRect(230, 110, 201, 21));
        label = new QLabel(connectWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 110, 101, 16));
        label_2 = new QLabel(connectWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(160, 60, 231, 16));
        chooseSignupButton = new QToolButton(connectWindow);
        chooseSignupButton->setObjectName(QStringLiteral("chooseSignupButton"));
        chooseSignupButton->setGeometry(QRect(310, 160, 101, 41));
        chooseLoginButton = new QToolButton(connectWindow);
        chooseLoginButton->setObjectName(QStringLiteral("chooseLoginButton"));
        chooseLoginButton->setGeometry(QRect(140, 160, 101, 41));
        serverError = new QLabel(connectWindow);
        serverError->setObjectName(QStringLiteral("serverError"));
        serverError->setGeometry(QRect(230, 90, 311, 16));
        stackedWidget->addWidget(connectWindow);
        loginWindow = new QWidget();
        loginWindow->setObjectName(QStringLiteral("loginWindow"));
        label_8 = new QLabel(loginWindow);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(150, 40, 261, 16));
        label_9 = new QLabel(loginWindow);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(120, 90, 71, 16));
        label_10 = new QLabel(loginWindow);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(120, 140, 71, 16));
        usernameLogin = new QLineEdit(loginWindow);
        usernameLogin->setObjectName(QStringLiteral("usernameLogin"));
        usernameLogin->setGeometry(QRect(210, 90, 221, 21));
        passwordLogin = new QLineEdit(loginWindow);
        passwordLogin->setObjectName(QStringLiteral("passwordLogin"));
        passwordLogin->setGeometry(QRect(210, 140, 221, 21));
        passwordLogin->setEchoMode(QLineEdit::Password);
        loginButton = new QToolButton(loginWindow);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(320, 190, 101, 41));
        backButtonOnLogin = new QToolButton(loginWindow);
        backButtonOnLogin->setObjectName(QStringLiteral("backButtonOnLogin"));
        backButtonOnLogin->setGeometry(QRect(130, 190, 101, 41));
        passwordLoginError = new QLabel(loginWindow);
        passwordLoginError->setObjectName(QStringLiteral("passwordLoginError"));
        passwordLoginError->setGeometry(QRect(120, 120, 411, 16));
        userLoginError = new QLabel(loginWindow);
        userLoginError->setObjectName(QStringLiteral("userLoginError"));
        userLoginError->setGeometry(QRect(120, 70, 411, 16));
        stackedWidget->addWidget(loginWindow);
        signupWindow = new QWidget();
        signupWindow->setObjectName(QStringLiteral("signupWindow"));
        usernameSignup = new QLineEdit(signupWindow);
        usernameSignup->setObjectName(QStringLiteral("usernameSignup"));
        usernameSignup->setGeometry(QRect(220, 80, 231, 21));
        passwordSignup = new QLineEdit(signupWindow);
        passwordSignup->setObjectName(QStringLiteral("passwordSignup"));
        passwordSignup->setGeometry(QRect(220, 130, 231, 21));
        passwordSignup->setEchoMode(QLineEdit::Password);
        confirmPasswordSignup = new QLineEdit(signupWindow);
        confirmPasswordSignup->setObjectName(QStringLiteral("confirmPasswordSignup"));
        confirmPasswordSignup->setGeometry(QRect(220, 170, 231, 21));
        confirmPasswordSignup->setEchoMode(QLineEdit::Password);
        label_3 = new QLabel(signupWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(130, 80, 71, 16));
        label_4 = new QLabel(signupWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 130, 71, 16));
        label_5 = new QLabel(signupWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(80, 170, 131, 16));
        signupButton = new QToolButton(signupWindow);
        signupButton->setObjectName(QStringLiteral("signupButton"));
        signupButton->setGeometry(QRect(340, 210, 101, 41));
        backButtonOnSignup = new QToolButton(signupWindow);
        backButtonOnSignup->setObjectName(QStringLiteral("backButtonOnSignup"));
        backButtonOnSignup->setGeometry(QRect(120, 210, 101, 41));
        label_6 = new QLabel(signupWindow);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 10, 531, 20));
        label_7 = new QLabel(signupWindow);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(180, 40, 181, 16));
        passwordSignupError = new QLabel(signupWindow);
        passwordSignupError->setObjectName(QStringLiteral("passwordSignupError"));
        passwordSignupError->setGeometry(QRect(130, 110, 411, 16));
        userSignupError = new QLabel(signupWindow);
        userSignupError->setObjectName(QStringLiteral("userSignupError"));
        userSignupError->setGeometry(QRect(130, 60, 411, 16));
        stackedWidget->addWidget(signupWindow);
        ChatWindow = new QWidget();
        ChatWindow->setObjectName(QStringLiteral("ChatWindow"));
        listUserWidget = new QListWidget(ChatWindow);
        listUserWidget->setObjectName(QStringLiteral("listUserWidget"));
        listUserWidget->setGeometry(QRect(20, 50, 131, 201));
        label_11 = new QLabel(ChatWindow);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 30, 91, 16));
        chatTextEdit = new QTextEdit(ChatWindow);
        chatTextEdit->setObjectName(QStringLiteral("chatTextEdit"));
        chatTextEdit->setGeometry(QRect(170, 50, 301, 161));
        chatMessage = new QLineEdit(ChatWindow);
        chatMessage->setObjectName(QStringLiteral("chatMessage"));
        chatMessage->setGeometry(QRect(210, 230, 241, 21));
        label_12 = new QLabel(ChatWindow);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(170, 30, 91, 16));
        label_13 = new QLabel(ChatWindow);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(170, 230, 41, 16));
        sendButton = new QToolButton(ChatWindow);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(460, 230, 81, 21));
        logoutButton = new QToolButton(ChatWindow);
        logoutButton->setObjectName(QStringLiteral("logoutButton"));
        logoutButton->setGeometry(QRect(480, 50, 61, 41));
        loggedUser = new QLabel(ChatWindow);
        loggedUser->setObjectName(QStringLiteral("loggedUser"));
        loggedUser->setGeometry(QRect(10, 0, 511, 16));
        stackedWidget->addWidget(ChatWindow);
        MenuWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MenuWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 551, 22));
        MenuWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MenuWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MenuWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MenuWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MenuWindow->setStatusBar(statusBar);

        retranslateUi(MenuWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MenuWindow)
    {
        MenuWindow->setWindowTitle(QApplication::translate("MenuWindow", "MenuWindow", 0));
        label->setText(QApplication::translate("MenuWindow", "Server Address :", 0));
        label_2->setText(QApplication::translate("MenuWindow", "Masukkan Alamat Server yang dituju", 0));
        chooseSignupButton->setText(QApplication::translate("MenuWindow", "DAFTAR", 0));
        chooseLoginButton->setText(QApplication::translate("MenuWindow", "LOGIN", 0));
        serverError->setText(QApplication::translate("MenuWindow", "<error server>", 0));
        label_8->setText(QApplication::translate("MenuWindow", "Masukkan Username dan Password anda!", 0));
        label_9->setText(QApplication::translate("MenuWindow", "Username :", 0));
        label_10->setText(QApplication::translate("MenuWindow", "Password  :", 0));
        loginButton->setText(QApplication::translate("MenuWindow", "LOGIN", 0));
        backButtonOnLogin->setText(QApplication::translate("MenuWindow", "KEMBALI", 0));
        passwordLoginError->setText(QApplication::translate("MenuWindow", "<error pass>", 0));
        userLoginError->setText(QApplication::translate("MenuWindow", "<error user>", 0));
        label_3->setText(QApplication::translate("MenuWindow", "Username :", 0));
        label_4->setText(QApplication::translate("MenuWindow", "Password  : ", 0));
        label_5->setText(QApplication::translate("MenuWindow", "Confirm Password :", 0));
        signupButton->setText(QApplication::translate("MenuWindow", "DAFTAR", 0));
        backButtonOnSignup->setText(QApplication::translate("MenuWindow", "KEMBALI", 0));
        label_6->setText(QApplication::translate("MenuWindow", "Masukkan data akun, panjang username dan password harus lebih dari 3 Karakter!", 0));
        label_7->setText(QApplication::translate("MenuWindow", "(Rahasiakan password anda!)", 0));
        passwordSignupError->setText(QApplication::translate("MenuWindow", "<error pass>", 0));
        userSignupError->setText(QApplication::translate("MenuWindow", "<error user>", 0));
        label_11->setText(QApplication::translate("MenuWindow", "Online Users :", 0));
        label_12->setText(QApplication::translate("MenuWindow", "Chat Window :", 0));
        label_13->setText(QApplication::translate("MenuWindow", "Chat :", 0));
        sendButton->setText(QApplication::translate("MenuWindow", "SEND", 0));
        logoutButton->setText(QApplication::translate("MenuWindow", "LOGOUT", 0));
        loggedUser->setText(QApplication::translate("MenuWindow", "Login sebagai :", 0));
    } // retranslateUi

};

namespace Ui {
    class MenuWindow: public Ui_MenuWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWINDOW_H

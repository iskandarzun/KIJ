/********************************************************************************
** Form generated from reading UI file 'listuserwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTUSERWINDOW_H
#define UI_LISTUSERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListUserWindow
{
public:
    QWidget *centralwidget;
    QListWidget *listUserWidget;
    QLabel *activeUser;
    QLabel *label;
    QToolButton *startChatButton;
    QToolButton *logoutButton;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ListUserWindow)
    {
        if (ListUserWindow->objectName().isEmpty())
            ListUserWindow->setObjectName(QStringLiteral("ListUserWindow"));
        ListUserWindow->resize(314, 418);
        centralwidget = new QWidget(ListUserWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        listUserWidget = new QListWidget(centralwidget);
        listUserWidget->setObjectName(QStringLiteral("listUserWidget"));
        listUserWidget->setGeometry(QRect(10, 70, 161, 291));
        activeUser = new QLabel(centralwidget);
        activeUser->setObjectName(QStringLiteral("activeUser"));
        activeUser->setGeometry(QRect(20, 10, 261, 20));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 50, 91, 16));
        startChatButton = new QToolButton(centralwidget);
        startChatButton->setObjectName(QStringLiteral("startChatButton"));
        startChatButton->setGeometry(QRect(190, 220, 101, 51));
        logoutButton = new QToolButton(centralwidget);
        logoutButton->setObjectName(QStringLiteral("logoutButton"));
        logoutButton->setGeometry(QRect(190, 290, 101, 51));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(190, 70, 61, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(190, 90, 61, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 110, 121, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(190, 130, 101, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(190, 150, 62, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(190, 170, 101, 16));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(190, 190, 41, 16));
        ListUserWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ListUserWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 314, 22));
        ListUserWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ListUserWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ListUserWindow->setStatusBar(statusbar);

        retranslateUi(ListUserWindow);

        QMetaObject::connectSlotsByName(ListUserWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ListUserWindow)
    {
        ListUserWindow->setWindowTitle(QApplication::translate("ListUserWindow", "List User", 0));
        activeUser->setText(QApplication::translate("ListUserWindow", "Selamat Datang <user disini> !", 0));
        label->setText(QApplication::translate("ListUserWindow", "Online Users :", 0));
        startChatButton->setText(QApplication::translate("ListUserWindow", "START CHAT", 0));
        logoutButton->setText(QApplication::translate("ListUserWindow", "LOGOUT", 0));
        label_2->setText(QApplication::translate("ListUserWindow", "Pilih user  ", 0));
        label_3->setText(QApplication::translate("ListUserWindow", "kemudian", 0));
        label_4->setText(QApplication::translate("ListUserWindow", "Tekan \"Start Chat\"", 0));
        label_5->setText(QApplication::translate("ListUserWindow", "untuk memulai", 0));
        label_6->setText(QApplication::translate("ListUserWindow", "atau pilih", 0));
        label_7->setText(QApplication::translate("ListUserWindow", "\"Logout\" untuk", 0));
        label_8->setText(QApplication::translate("ListUserWindow", "keluar", 0));
    } // retranslateUi

};

namespace Ui {
    class ListUserWindow: public Ui_ListUserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTUSERWINDOW_H

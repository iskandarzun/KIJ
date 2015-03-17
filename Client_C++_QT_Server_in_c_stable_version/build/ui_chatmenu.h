/********************************************************************************
** Form generated from reading UI file 'chatmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATMENU_H
#define UI_CHATMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatMenu
{
public:
    QWidget *centralwidget;
    QListView *listView;
    QLabel *anotherUser;
    QLabel *label_2;
    QTextEdit *messageSend;
    QToolButton *sendButton;
    QToolButton *outButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChatMenu)
    {
        if (ChatMenu->objectName().isEmpty())
            ChatMenu->setObjectName(QStringLiteral("ChatMenu"));
        ChatMenu->resize(516, 352);
        ChatMenu->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(ChatMenu);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(20, 40, 381, 181));
        anotherUser = new QLabel(centralwidget);
        anotherUser->setObjectName(QStringLiteral("anotherUser"));
        anotherUser->setGeometry(QRect(20, 20, 371, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 230, 62, 16));
        messageSend = new QTextEdit(centralwidget);
        messageSend->setObjectName(QStringLiteral("messageSend"));
        messageSend->setGeometry(QRect(20, 250, 381, 41));
        sendButton = new QToolButton(centralwidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(420, 250, 81, 41));
        outButton = new QToolButton(centralwidget);
        outButton->setObjectName(QStringLiteral("outButton"));
        outButton->setGeometry(QRect(420, 50, 81, 41));
        ChatMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChatMenu);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 516, 22));
        ChatMenu->setMenuBar(menubar);
        statusbar = new QStatusBar(ChatMenu);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ChatMenu->setStatusBar(statusbar);

        retranslateUi(ChatMenu);

        QMetaObject::connectSlotsByName(ChatMenu);
    } // setupUi

    void retranslateUi(QMainWindow *ChatMenu)
    {
        ChatMenu->setWindowTitle(QApplication::translate("ChatMenu", "Chat Menu", 0));
        anotherUser->setText(QApplication::translate("ChatMenu", "Percakapan dengan <USER> :", 0));
        label_2->setText(QApplication::translate("ChatMenu", "Pesan :", 0));
        sendButton->setText(QApplication::translate("ChatMenu", "KIRIM", 0));
        outButton->setText(QApplication::translate("ChatMenu", "KELUAR", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatMenu: public Ui_ChatMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATMENU_H

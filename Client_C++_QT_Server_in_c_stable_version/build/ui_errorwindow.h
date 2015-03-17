/********************************************************************************
** Form generated from reading UI file 'errorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORWINDOW_H
#define UI_ERRORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErrorWindow
{
public:
    QWidget *centralwidget;
    QLabel *errorMessage;
    QToolButton *backButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ErrorWindow)
    {
        if (ErrorWindow->objectName().isEmpty())
            ErrorWindow->setObjectName(QStringLiteral("ErrorWindow"));
        ErrorWindow->resize(340, 150);
        centralwidget = new QWidget(ErrorWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        errorMessage = new QLabel(centralwidget);
        errorMessage->setObjectName(QStringLiteral("errorMessage"));
        errorMessage->setGeometry(QRect(30, 30, 131, 16));
        backButton = new QToolButton(centralwidget);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(100, 60, 131, 41));
        ErrorWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ErrorWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 340, 22));
        ErrorWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ErrorWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ErrorWindow->setStatusBar(statusbar);

        retranslateUi(ErrorWindow);

        QMetaObject::connectSlotsByName(ErrorWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ErrorWindow)
    {
        ErrorWindow->setWindowTitle(QApplication::translate("ErrorWindow", "Error!!!", 0));
        errorMessage->setText(QApplication::translate("ErrorWindow", "<pesan error disini>", 0));
        backButton->setText(QApplication::translate("ErrorWindow", "KEMBALI", 0));
    } // retranslateUi

};

namespace Ui {
    class ErrorWindow: public Ui_ErrorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORWINDOW_H

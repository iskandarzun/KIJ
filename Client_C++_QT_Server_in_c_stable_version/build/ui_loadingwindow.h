/********************************************************************************
** Form generated from reading UI file 'loadingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGWINDOW_H
#define UI_LOADINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadingWindow
{
public:
    QWidget *centralwidget;
    QProgressBar *progressBar;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoadingWindow)
    {
        if (LoadingWindow->objectName().isEmpty())
            LoadingWindow->setObjectName(QStringLiteral("LoadingWindow"));
        LoadingWindow->resize(169, 124);
        centralwidget = new QWidget(LoadingWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(30, 40, 118, 23));
        progressBar->setValue(24);
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 20, 81, 16));
        LoadingWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoadingWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 169, 22));
        LoadingWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoadingWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        LoadingWindow->setStatusBar(statusbar);

        retranslateUi(LoadingWindow);

        QMetaObject::connectSlotsByName(LoadingWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoadingWindow)
    {
        LoadingWindow->setWindowTitle(QApplication::translate("LoadingWindow", "MainWindow", 0));
        label->setText(QApplication::translate("LoadingWindow", "Loading . . .", 0));
    } // retranslateUi

};

namespace Ui {
    class LoadingWindow: public Ui_LoadingWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGWINDOW_H

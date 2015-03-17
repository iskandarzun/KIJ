#include "mainwindow.h"
#include "clientdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ClientData this_client;

    MainWindow myMainWindow;

    myMainWindow.show();

    return app.exec();
}

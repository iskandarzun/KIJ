#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
//#include <QMenuBar>
#include "clientdata.h"
#include "errorwindow.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connect_slots();

private slots:
    void goToSignupMenu();
    void goToLoginMenu();
    void errorShow();
    void serverAddressInput(QString);
    void checkErrorSignup();
    void checkErrorLogin();
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    QMainWindow *signupWindow;
    QMainWindow *loginWindow;
    ErrorWindow *errorWindow;
    QMenuBar *allMenuBar;
    string serverAddress;
};

#endif // MAINWINDOW_H

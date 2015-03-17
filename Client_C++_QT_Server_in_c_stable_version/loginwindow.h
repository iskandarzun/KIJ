#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

//#include <QMainWindow>
#include "clientdata.h"
#include "errorwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

public slots:
    void connect_slots();

private slots:
    void usernameLoginInput(QString);
    void passwordLoginInput(QString);
    void loginStart();
    void backToMenu();
    void goToListUserMenu();
    void errorShow();
    void closeEvent(QCloseEvent *);

private:
    Ui::LoginWindow *ui;
    QMainWindow *currentWindow;
    ErrorWindow *errorWindow;
    string username;
    string password;
};

#endif // LOGINWINDOW_H

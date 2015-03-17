#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

//#include <QMainWindow>
#include "clientdata.h"
#include "errorwindow.h"

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = 0);
    ~SignupWindow();

public slots:
    void connect_slots();

private slots:
    void signupStart();
    void signupUsernameInput(QString);
    void signupPasswordInput(QString);
    void signupConfirmPasswordInput(QString);
    void errorShow();
    void goToListUserMenu();
    void backToMenu();
    void closeEvent(QCloseEvent *);

private:
    Ui::SignupWindow *ui;
    QMainWindow *currentWindow;
    ErrorWindow *errorWindow;
    string username;
    string password;
    string confirmPassword;
};

#endif // SIGNUPWINDOW_H

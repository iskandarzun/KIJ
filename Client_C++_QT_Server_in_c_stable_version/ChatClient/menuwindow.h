#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QRegExp>
#include <QShortcut>
#include "connection.h"
#include "clientdata.h"

using namespace std;

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = 0);
    ~MenuWindow();

public slots:
    void connect_slots();

private slots:
    //system function
    void goToSignup();
    void goToLogin();
    void checkSignup();
    void checkLogin();
    void backToMenu();
    void setListUserOnline(QString);
    void setListUserOffline(QString);
    QStringList getBufferProtocol(QString);
    void addUsers(QString);
    void sendMessage();
    void standByRead();
    void logout();
    void initMessage();
    void clearMessage();

private:
    Ui::MenuWindow *ui;

    Connection *myConnection;
    ClientData *myData;
};

#endif // MENUWINDOW_H

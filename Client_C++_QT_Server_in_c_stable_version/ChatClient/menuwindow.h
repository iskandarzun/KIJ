#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QRegExp>
#define MAX_BUFFER 4096
#define WAIT_TIME 3000 //in miliseconds

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
    //get function
    QString getServerAdress();
    QString getUsername();
    QString getPassword();
    QString getConfirmPassword();
    QString getLoggedUser();
    QString getChatFriend();

    //set function
    void setServerAddress(QString);
    void setUsername(QString);
    void setPassword(QString);
    void setConfirmPassword(QString);
    void setLoggedUser(QString);
    void setChatFriend(int);
    void setListUserOnline(QString);
    void setListUserOffline(QString);

    //system function
    void goToSignup();
    void goToLogin();
    void checkSignup();
    void checkLogin();
    void backToMenu();
    QString getFormatMessage(QString, QString, QString, QString, QString, QString);
    QStringList getBufferProtocol(QString);
    void setOnlineUsers(QString);
    void sendMessage();
    void standByRead();
    void logout();

private:
    Ui::MenuWindow *ui;
    QTcpSocket *socket;
    QString serverAddress;
    QString username;
    QString password;
    QString confirmPassword;
    QString chatFriend;
    QString loggedUser;
    QStringList onlineUsers;
};

#endif // MENUWINDOW_H

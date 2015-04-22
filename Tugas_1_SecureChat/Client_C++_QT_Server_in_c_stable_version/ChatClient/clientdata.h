#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <QObject>
#include <QStringList>
#define MIN_USERNAME 3
#define MIN_PASSWORD 5
#define MAX_INPUT_USER 512

class ClientData : public QObject
{
    Q_OBJECT
public:
    explicit ClientData(QObject *parent = 0);

signals:

public slots:
    //Get function
    QString getUsername();
    QString getPassword();
    QString getConfirmPassword();
    QString getLoggedUser();
    QString getChatFriend();
    QString getSessionKey();
    QStringList getOnlineUsers();

    //Set Function
    void setUsername(QString);
    void setPassword(QString);
    void setConfirmPassword(QString);
    void setLoggedUser();
    void setChatFriend(int);
    void setSessionKey(QString);
    void setOnlineUsers(QStringList);

    //System Function
    void clearData();
    void addNewUser(QString);
    void removeUser(int);
    int usersCount();
    bool validateUsername();
    bool validatePassword();
    bool confirmingPassword();
    QString userAtIndex(int);

private:
    //Properties
    QString username;
    QString password;
    QString confirmPassword;
    QString chatFriend;
    QString loggedUser;
    QString sessionKey;
    QStringList onlineUsers;

};

#endif // CLIENTDATA_H

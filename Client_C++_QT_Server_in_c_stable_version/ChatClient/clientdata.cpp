#include "clientdata.h"

ClientData::ClientData(QObject *parent) :
    QObject(parent)
{
}

//set function
void ClientData::setUsername(QString username)
{
    this->username = username;
}

void ClientData::setPassword(QString password)
{
    this->password = password;
}

void ClientData::setConfirmPassword(QString confirmPassword)
{
    this->confirmPassword = confirmPassword;
}

void ClientData::setLoggedUser()
{
    this->loggedUser = this->username;
}

void ClientData::setChatFriend(int index)
{
    if(this->onlineUsers.count() > 0)
    {
        this->chatFriend = this->onlineUsers[index];
    }
    else
    {
        this->chatFriend.clear();
    }
    //qDebug("chatfriend di pilih = %s, index = %d", this->onlineUsers[index].toStdString().c_str(), index);
}

void ClientData::setSessionKey(QString session_key)
{
    this->sessionKey = session_key;
}

void ClientData::setOnlineUsers(QStringList users)
{
    this->onlineUsers.clear();
    this->onlineUsers = users;
}

//get function
QString ClientData::getUsername()
{
    return this->username;
}

QString ClientData::getPassword()
{
    return this->password;
}

QString ClientData::getConfirmPassword()
{
    return this->confirmPassword;
}

QString ClientData::getLoggedUser()
{
    return this->loggedUser;
}

QString ClientData::getChatFriend()
{
    return this->chatFriend;
}

QString ClientData::getSessionKey()
{
    return this->sessionKey;
}

QStringList ClientData::getOnlineUsers()
{
    return this->onlineUsers;
}

//system function
void ClientData::clearData()
{
    //attributes clear
    this->onlineUsers.clear();
    this->username.clear();
    this->password.clear();
    this->confirmPassword.clear();
    this->loggedUser.clear();
}

void ClientData::addNewUser(QString newUser)
{
    this->onlineUsers.push_back(newUser);
}

void ClientData::removeUser(int index)
{
    this->onlineUsers.removeAt(index);
}

int ClientData::usersCount()
{
    return this->onlineUsers.count();
}

bool ClientData::validateUsername()
{
    if(this->username.length() > MIN_USERNAME && this->username.length() <= MAX_INPUT_USER)
    {
        return true;
    }
    return false;
}

bool ClientData::validatePassword()
{
    if(this->password.length() > MIN_PASSWORD && this->password.length() <= MAX_INPUT_USER)
    {
        return true;
    }
    return false;
}

bool ClientData::confirmingPassword()
{
    if(this->password == this->confirmPassword)
    {
        return true;
    }
    return false;
}

QString ClientData::userAtIndex(int index)
{
    return this->onlineUsers.at(index);
}

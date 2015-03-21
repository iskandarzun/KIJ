#include "menuwindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    this->socket = new QTcpSocket(this);
    ui->stackedWidget->setCurrentWidget(ui->connectWindow);
    this->connect_slots();
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

//slots mapper
void MenuWindow::connect_slots()
{
    //set connection
    connect(ui->serverAddress, SIGNAL(textChanged(QString)), this, SLOT(setServerAddress(QString)));
    connect(ui->usernameLogin, SIGNAL(textChanged(QString)), this, SLOT(setUsername(QString)));
    connect(ui->passwordLogin, SIGNAL(textChanged(QString)), this, SLOT(setPassword(QString)));
    connect(ui->usernameSignup, SIGNAL(textChanged(QString)), this, SLOT(setUsername(QString)));
    connect(ui->passwordSignup, SIGNAL(textChanged(QString)), this, SLOT(setPassword(QString)));
    connect(ui->confirmPasswordSignup, SIGNAL(textChanged(QString)), this, SLOT(setConfirmPassword(QString)));
    connect(ui->listUserWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setChatFriend(int)));

    //system function connection
    connect(ui->chooseSignupButton, SIGNAL(clicked()), this, SLOT(goToSignup()));
    connect(ui->chooseLoginButton, SIGNAL(clicked()), this, SLOT(goToLogin()));
    connect(ui->backButtonOnLogin, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->backButtonOnSignup, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->signupButton, SIGNAL(clicked()), this, SLOT(checkSignup()));
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(checkLogin()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(standByRead()));
}

//set function
void MenuWindow::setServerAddress(QString address)
{
    this->serverAddress = address;
}

void MenuWindow::setUsername(QString username)
{
    this->username = username;
}

void MenuWindow::setPassword(QString password)
{
    this->password = password;
}

void MenuWindow::setConfirmPassword(QString confirmPassword)
{
    this->confirmPassword = confirmPassword;
}

void MenuWindow::setLoggedUser(QString user)
{
    this->loggedUser = user;
}

void MenuWindow::setChatFriend(int index)
{
    if(this->onlineUsers.count() > 0)
    {
        this->chatFriend = this->onlineUsers[index];
    }
    else
    {
        this->chatFriend = "NONE";
    }
}

//get function
QString MenuWindow::getServerAdress()
{
    return this->serverAddress;
}

QString MenuWindow::getUsername()
{
    return this->username;
}

QString MenuWindow::getPassword()
{
    return this->password;
}

QString MenuWindow::getConfirmPassword()
{
    return this->confirmPassword;
}

QString MenuWindow::getLoggedUser()
{
    return this->loggedUser;
}

QString MenuWindow::getChatFriend()
{
    return this->chatFriend;
}

//system function
void MenuWindow::goToSignup()
{
    this->socket->connectToHost(this->serverAddress, 8888);
    //qDebug("%d", (int)this->socket->error());
    if(this->socket->waitForConnected(WAIT_TIME))
    {
        ui->stackedWidget->setCurrentWidget(ui->signupWindow);
    }
}

void MenuWindow::goToLogin()
{
    this->socket->connectToHost(this->serverAddress, 8888);
    //qDebug("%d", (int)this->socket->error());
    if(this->socket->waitForConnected(WAIT_TIME))
    {
        ui->stackedWidget->setCurrentWidget(ui->loginWindow);
    }
}

void MenuWindow::checkSignup()
{
    this->socket->write(this->getFormatMessage("SIGNUP", "AUTH_REQ", "0", "0", "AUTH", this->username+":"+this->password).toUtf8());
    this->socket->waitForReadyRead(WAIT_TIME);
    QString received_message = QString::fromUtf8(this->socket->read(MAX_BUFFER));

    //qDebug("%s\n", received_message.toStdString().c_str());

    QStringList temp_buffer = this->getBufferProtocol(received_message);
    if(temp_buffer[1] == "SIGNUP_SUCCESS")
    {
        temp_buffer.clear();
        received_message.clear();

        this->setLoggedUser(this->username);

        this->socket->write(this->getFormatMessage("LIST_USER", "LIST_USER_REQ", "0", this->username, "NULL", "NULL").toUtf8());
        this->socket->waitForReadyRead(WAIT_TIME);
        received_message = QString::fromUtf8(this->socket->read(MAX_BUFFER));

        temp_buffer = this->getBufferProtocol(received_message);

        setOnlineUsers(temp_buffer[5]);

        ui->stackedWidget->setCurrentWidget(ui->ChatWindow);
    }
}

void MenuWindow::checkLogin()
{
    this->socket->write(this->getFormatMessage("LOGIN", "AUTH_REQ", "0", "0", "AUTH", this->username+":"+this->password).toUtf8());
    this->socket->waitForReadyRead(WAIT_TIME);
    QString received_message = QString::fromUtf8(this->socket->read(MAX_BUFFER));

    //qDebug("%s\n", received_message.toStdString().c_str());


    QStringList temp_buffer = this->getBufferProtocol(received_message);
    if(temp_buffer[1] == "LOGIN_SUCCESS")
    {
        temp_buffer.clear();
        received_message.clear();

        this->setLoggedUser(this->username);

        this->socket->write(this->getFormatMessage("LIST_USER", "LIST_USER_REQ", "0", this->username, "NULL", "NULL").toUtf8());
        this->socket->waitForReadyRead(WAIT_TIME);
        received_message = QString::fromUtf8(this->socket->read(MAX_BUFFER));

        temp_buffer = this->getBufferProtocol(received_message);

        setOnlineUsers(temp_buffer[5]);

        ui->stackedWidget->setCurrentWidget(ui->ChatWindow);
    }
}

void MenuWindow::backToMenu()
{
    this->socket->disconnectFromHost();
    ui->stackedWidget->setCurrentWidget(ui->connectWindow);
}

QString MenuWindow::getFormatMessage(QString state, QString flag, QString receiver, QString sender, QString type, QString content)
{
    QString output;
    output += state + "\r\n" + flag + "\r\n" + receiver + "\r\n" + sender + "\r\n" + type + "\r\n" + content;
    return output;
}

QStringList MenuWindow::getBufferProtocol(QString message)
{
    QRegExp delimiter("\r\n");
    QStringList buffer_protocol = message.split(delimiter);
    return buffer_protocol;
}

void MenuWindow::setOnlineUsers(QString list_user)
{
    QRegExp delimiter(":");
    QStringList all_list = list_user.split(delimiter);
    this->onlineUsers.clear();
    this->onlineUsers = all_list;

    //ui->listUserWidget->takeItem(0);

    //qDebug("DISINI!\n");
    QListWidgetItem *users = NULL;
    QString tempname;
    int index;


    for (index = 0; index < this->onlineUsers.count()-1; index++)
    {
        tempname.clear();
        //qDebug("index ke : %d, jumlah user = %d\n", index, this->onlineUsers.count());
        if(this->onlineUsers.at(index) != NULL)
        {
            tempname = this->onlineUsers.at(index);
            users = new QListWidgetItem(tempname, 0, index);
            ui->listUserWidget->addItem(users);
        }
    }
}

void MenuWindow::sendMessage()
{
    this->socket->write(this->getFormatMessage("INCHAT", "SEND_MESSAGE", this->getChatFriend(), this->getLoggedUser(), "MESSAGE", ui->chatMessage->text()).toUtf8());
    ui->chatTextEdit->append("From <b>You</b> to <b>" + this->chatFriend + "</b>: " + ui->chatMessage->text());
    ui->chatMessage->clear();
    ui->chatMessage->setFocus();
}

void MenuWindow::standByRead()
{

    if(ui->stackedWidget->currentWidget() == ui->ChatWindow)
    {
        QString received_message = QString::fromUtf8(this->socket->read(MAX_BUFFER));
        QStringList temp_buffer = this->getBufferProtocol(received_message);

        if(temp_buffer[1] == "LIST_USER_SEND")
        {
            qDebug("%s\n", temp_buffer[5].toStdString().c_str());
            this->setOnlineUsers(temp_buffer[5]);
        }
        else
        if(temp_buffer[1] == "SEND_RECEIVE")
        {
            ui->chatTextEdit->append("<b>" + temp_buffer[3] + "</b>: " + temp_buffer[5]);
        }
        else
        if(temp_buffer[1] == "LOGOUT_SUCCESS")
        {
           logout();
        }
        else
        if(temp_buffer[1] == "LOGOUT_FAILED")
        {

        }
        else
        if(temp_buffer[1] == "SEND_MESSAGE_OK")
        {

        }
    }
}

void MenuWindow::logout()
{
    this->socket->disconnectFromHost();
    ui->stackedWidget->setCurrentWidget(ui->connectWindow);
}

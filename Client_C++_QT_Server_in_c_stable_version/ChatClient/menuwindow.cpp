#include "menuwindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    this->myData = new ClientData();

    this->myConnection = new Connection();
    this->myConnection->setPort(8888);

    this->initMessage();
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
    connect(ui->serverAddress, SIGNAL(textChanged(QString)), this->myConnection, SLOT(setServerAddress(QString)));
    connect(ui->usernameLogin, SIGNAL(textChanged(QString)), this->myData, SLOT(setUsername(QString)));
    connect(ui->passwordLogin, SIGNAL(textChanged(QString)), this->myData, SLOT(setPassword(QString)));
    connect(ui->usernameSignup, SIGNAL(textChanged(QString)), this->myData, SLOT(setUsername(QString)));
    connect(ui->passwordSignup, SIGNAL(textChanged(QString)), this->myData, SLOT(setPassword(QString)));
    connect(ui->confirmPasswordSignup, SIGNAL(textChanged(QString)), this->myData, SLOT(setConfirmPassword(QString)));
    connect(ui->listUserWidget, SIGNAL(currentRowChanged(int)), this->myData, SLOT(setChatFriend(int)));

    //system function connection
    connect(ui->chooseSignupButton, SIGNAL(clicked()), this, SLOT(goToSignup()));
    connect(ui->chooseLoginButton, SIGNAL(clicked()), this, SLOT(goToLogin()));
    connect(ui->backButtonOnLogin, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->backButtonOnSignup, SIGNAL(clicked()), this, SLOT(backToMenu()));
    connect(ui->signupButton, SIGNAL(clicked()), this, SLOT(checkSignup()));
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(checkLogin()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(this->myConnection, SIGNAL(incomingData()), this, SLOT(standByRead()));
    connect(ui->chatMessage, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
}

//system function
void MenuWindow::goToSignup()
{
    this->clearMessage();
    this->myConnection->ConnectingToServer();
    //qDebug("%d", (int)this->socket->error());
    if(this->myConnection->isConnectedToServer())
    {
        this->clearMessage();
        ui->stackedWidget->setCurrentWidget(ui->signupWindow);
    }
    else
    {
        ui->serverError->setText("Koneksi ke server gagal");
        ui->serverError->show();
    }
}

void MenuWindow::goToLogin()
{
    this->clearMessage();
    this->myConnection->ConnectingToServer();
    //qDebug("%d", (int)this->socket->error());
    if(this->myConnection->isConnectedToServer())
    {
        this->clearMessage();
        ui->stackedWidget->setCurrentWidget(ui->loginWindow);
    }
    else
    {
        ui->serverError->setText("Koneksi ke server gagal");
        ui->serverError->show();
    }
}

void MenuWindow::checkSignup()
{
    QRegExp checker("(\\:|\\\\|\\/)");
    QStringList temp = this->myData->getUsername().split(checker);
    //qDebug("%d", temp.size());

    this->clearMessage();
    if(temp.size() == 1 && this->myData->validateUsername()
       && this->myData->validatePassword()
       && this->myData->confirmingPassword())
    {
        this->myConnection->sendData("SIGNUP", "AUTH_REQ", "0", "0", "AUTH", this->myData->getUsername()+":"+this->myData->getPassword());
        this->myConnection->waiting();
        QString received_message = this->myConnection->readData();

        //qDebug("%s\n", received_message.toStdString().c_str());

        QStringList temp_buffer = this->getBufferProtocol(received_message);
        if(temp_buffer[1] == "SIGNUP_SUCCESS")
        {
            QRegExp delimiters(":");
            QStringList user_and_session = temp_buffer[3].split(delimiters);
            if(user_and_session[1] != NULL)
            {
                this->myData->setSessionKey(user_and_session[1]);
            }

            temp_buffer.clear();
            received_message.clear();

            this->myData->setLoggedUser();

            this->myConnection->sendData("LIST_USER", "LIST_USER_REQ", "0", this->myData->getUsername()+":"+this->myData->getSessionKey(), "NULL", "NULL");
            this->myConnection->waiting();
            received_message = this->myConnection->readData();

            temp_buffer = this->getBufferProtocol(received_message);

            this->addUsers(temp_buffer[5].trimmed());

            this->clearMessage();
            ui->stackedWidget->setCurrentWidget(ui->ChatWindow);
            ui->loggedUser->setText("Login sebagai : " + this->myData->getLoggedUser());
        }
        else
        {
            ui->userSignupError->setText("Username sudah dipakai");
            ui->userSignupError->show();
        }
    }

    if(!this->myData->validateUsername() || temp.size() > 1)
    {
        ui->userSignupError->setText("Gunakan angka atau huruf lebih dari 3 dan kurang dari 512 Karakter!");
        ui->userSignupError->show();
    }

    if(!this->myData->validatePassword())
    {
        ui->passwordSignupError->setText("Password harus lebih dari 5 dan kurang dari 512 Karakter!");
        ui->passwordSignupError->show();
    }
    else
    if(!this->myData->confirmingPassword())
    {
        ui->passwordSignupError->setText("Password dan Konfirmasi password tidak sama!");
        ui->passwordSignupError->show();
    }
}

void MenuWindow::checkLogin()
{
    QRegExp checker("(\\:|\\\\|\\/)");
    QStringList temp = this->myData->getUsername().split(checker);
    //qDebug("%d", temp.size());

    this->clearMessage();
    if(temp.size() == 1 && this->myData->validateUsername()
            && this->myData->validatePassword())
    {
        this->myConnection->sendData("LOGIN", "AUTH_REQ", "0", "0", "AUTH", this->myData->getUsername()+":"+this->myData->getPassword());
        this->myConnection->waiting();
        QString received_message = this->myConnection->readData();

        //qDebug("%s\n", received_message.toStdString().c_str());


        QStringList temp_buffer = this->getBufferProtocol(received_message);
        if(temp_buffer[1] == "LOGIN_SUCCESS")
        {
            QRegExp delimiters(":");
            QStringList user_and_session = temp_buffer[3].split(delimiters);
            if(user_and_session[1] != NULL)
            {
                this->myData->setSessionKey(user_and_session[1]);
            }
            temp_buffer.clear();
            received_message.clear();

            this->myData->setLoggedUser();

            this->myConnection->sendData("LIST_USER", "LIST_USER_REQ", "0", this->myData->getUsername()+":"+this->myData->getSessionKey(), "NULL", "NULL");
            this->myConnection->waiting();
            received_message = this->myConnection->readData();

            temp_buffer = this->getBufferProtocol(received_message);

            addUsers(temp_buffer[5].trimmed());

            this->clearMessage();
            ui->stackedWidget->setCurrentWidget(ui->ChatWindow);
            ui->loggedUser->setText("Login sebagai : " + this->myData->getLoggedUser());
        }
        else
        {
            ui->userLoginError->setText("Login Gagal! Coba Cek input");
            ui->userLoginError->show();
        }
    }

    if(!this->myData->validateUsername() || temp.size() > 1)
    {
        ui->userLoginError->setText("Gunakan angka atau huruf lebih dari 3 dan kurang dari 512 Karakter!");
        ui->userLoginError->show();
    }

    if(!this->myData->validatePassword())
    {
        ui->passwordLoginError->setText("Password harus lebih dari 5 dan kurang dari 512 Karakter!");
        ui->passwordLoginError->show();
    }
}

void MenuWindow::backToMenu()
{
    this->clearMessage();
    this->myConnection->disconnecting();
    ui->stackedWidget->setCurrentWidget(ui->connectWindow);
}

QStringList MenuWindow::getBufferProtocol(QString message)
{
    QRegExp delimiter("\r\n");
    QStringList buffer_protocol = message.split(delimiter);
    return buffer_protocol;
}

void MenuWindow::addUsers(QString list_user)
{
    QRegExp delimiter(":");
    QStringList all_list = list_user.split(delimiter);
    all_list.pop_back();
    all_list.removeOne(this->myData->getUsername());
    this->myData->setOnlineUsers(all_list);

    //ui->listUserWidget->takeItem(0);

    //qDebug("DISINI!\n");
    QListWidgetItem *users = NULL;
    QString tempname;
    int index;


    for (index = 0; index < this->myData->usersCount(); index++)
    {
        tempname.clear();
        //qDebug("index ke : %d, jumlah user = %d\n", index, this->onlineUsers.count());
        if(this->myData->userAtIndex(index) != NULL)
        {
            tempname = this->myData->userAtIndex(index);
            users = new QListWidgetItem(tempname, 0, index);
            ui->listUserWidget->addItem(users);
        }
    }
    ui->listUserWidget->setCurrentRow(0);

    qDebug("DISINI jumlah online = %d\n", this->myData->usersCount() /*this->onlineUsers[index].toStdString().c_str()*/);
}

void MenuWindow::setListUserOnline(QString user)
{
    this->myData->addNewUser(user);
    int index = this->myData->usersCount();

    qDebug("DISINI jumlah %d\n", index /*this->onlineUsers[index].toStdString().c_str()*/);
    QListWidgetItem *newuser = NULL;

    newuser = new QListWidgetItem(user, 0, index);
    ui->listUserWidget->addItem(newuser);
    if(index == 1)
    {
        ui->listUserWidget->setCurrentRow(0);
    }
}

void MenuWindow::setListUserOffline(QString user)
{
    int index;

    for(index = 0; index < this->myData->usersCount(); index++)
    {
        if(this->myData->userAtIndex(index) == user)
        {
            break;
        }
    }

    if(this->myData->usersCount() > 1)
    {
        ui->listUserWidget->takeItem(index);

        this->myData->removeUser(index);
    }
    else
    {
        this->myData->removeUser(index);

        ui->listUserWidget->takeItem(index);
    }

    qDebug("DISINI jumlah %d\n", this->myData->usersCount() /*this->onlineUsers[index].toStdString().c_str()*/);

}

void MenuWindow::sendMessage()
{
    if(this->myData->getChatFriend() != NULL)
    {
        this->myConnection->sendData("INCHAT", "SEND_MESSAGE", this->myData->getChatFriend(), this->myData->getLoggedUser()+":"+this->myData->getSessionKey(), "MESSAGE", ui->chatMessage->text());
        ui->chatTextEdit->append("From <b>You</b> to <b>" + this->myData->getChatFriend() + "</b>: " + ui->chatMessage->text());
        ui->chatMessage->clear();
        ui->chatMessage->setFocus();
    }
}

void MenuWindow::standByRead()
{
    if(ui->stackedWidget->currentWidget() == ui->ChatWindow)
    {
        QString received_message = this->myConnection->readData();
        QStringList temp_buffer = this->getBufferProtocol(received_message);

        if(temp_buffer[1] == "LIST_USER_SEND_ONLINE")
        {
            //qDebug("%s\n", temp_buffer[5].toStdString().c_str());
            this->setListUserOnline(temp_buffer[5].trimmed());
        }
        else
        if(temp_buffer[1] == "LIST_USER_SEND_OFFLINE")
        {
            //qDebug("%s\n", temp_buffer[5].toStdString().c_str());
            this->setListUserOffline(temp_buffer[5].trimmed());
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
    this->myConnection->disconnecting();
    ui->stackedWidget->setCurrentWidget(ui->connectWindow);

    //attributes clear
    this->myData->clearData();

    //ui clear
    ui->chatTextEdit->clear();
    ui->usernameLogin->clear();
    ui->usernameSignup->clear();
    ui->passwordLogin->clear();
    ui->passwordSignup->clear();
    ui->confirmPasswordSignup->clear();
    if(this->myData->usersCount() <= 0)
    {
        ui->listUserWidget->clear();
    }
}

void MenuWindow::initMessage()
{
    ui->serverError->hide();
    ui->serverError->setStyleSheet("QLabel { color : red; }");

    ui->userLoginError->hide();
    ui->userLoginError->setStyleSheet("QLabel { color : red; font-size : 10pt; }");

    ui->userSignupError->hide();
    ui->userSignupError->setStyleSheet("QLabel { color : red; font-size : 10pt; }");

    ui->passwordLoginError->hide();
    ui->passwordLoginError->setStyleSheet("QLabel { color : red; font-size : 10pt; }");

    ui->passwordSignupError->hide();
    ui->passwordSignupError->setStyleSheet("QLabel { color : red; font-size : 10pt; }");
}

void MenuWindow::clearMessage()
{
    ui->serverError->hide();
    ui->userLoginError->hide();
    ui->userSignupError->hide();
    ui->passwordLoginError->hide();
    ui->passwordSignupError->hide();
}

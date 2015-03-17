#include "listuserwindow.h"
#include "ui_listuserwindow.h"

ListUserWindow::ListUserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ListUserWindow)
{
    ui->setupUi(this);
    this_client.transferData("LIST_USER", "LIST_USER_REQ", "0", this_client.getUsername(), "NULL", "NULL");
    connect_slots();
    /*
    if(this_client.getErrorFlag() == 1)
    {
        this->errorShow();
    } */
    setActiveUsername();
    setDataOnlineUsers();
}

ListUserWindow::~ListUserWindow()
{
    delete ui;
}

void ListUserWindow::connect_slots()
{
    connect(ui->startChatButton,SIGNAL(clicked()),this,SLOT(chatStart()));
    connect(ui->logoutButton,SIGNAL(clicked()),this,SLOT(logout()));
    connect(ui->listUserWidget,SIGNAL(currentRowChanged(int)),this,SLOT(setChatFriend(int)));
}

void ListUserWindow::setActiveUsername()
{
    string message = "Selamat Datang " + this_client.getUsername() + "!";
    ui->activeUser->setText(QString::fromStdString(message));
}

void ListUserWindow::setDataOnlineUsers()
{
    this_client.inputUsers();
    vector<list_username> tempusr = this_client.getUsers();

    ui->listUserWidget->clear();
    QListWidgetItem *users = NULL;
    QString tempname;
    int index;

    for (index = 0; index < (int)tempusr.size(); index++)
    {
        tempname.clear();
        tempname.append(QString::fromStdString(tempusr[index].username));
        users = new QListWidgetItem(tempname, 0, index);
        ui->listUserWidget->addItem(users);
    }
}

void ListUserWindow::chatStart()
{
    chatMenu = new ChatMenu();
    chatMenu->setChatFriend(this->chatFriend);
    chatMenu->show();
    chatMenu->raise();
    chatMenu->activateWindow();
}

void ListUserWindow::openChatMenu()
{
    chatMenu = new ChatMenu();
    chatMenu->show();
    chatMenu->raise();
    chatMenu->activateWindow();
}

void ListUserWindow::logout()
{
    this_client.transferData("LOGOUT", "LOGOUT_REQ", "0", this_client.getUsername(), "NULL", "NULL");
    this->hide();
    QMainWindow *back = this_client.backToMainWindow();
    back->show();
    back->raise();
    back->activateWindow();
}

void ListUserWindow::errorShow()
{
    this_client.setPreviousWindow(*this);
    this->hide();
    errorWindow = new ErrorWindow();
    errorWindow->setErrorMessage(this_client.getErrorType());
    errorWindow->show();
    errorWindow->raise();
    errorWindow->activateWindow();
}

void ListUserWindow::activateWindow()
{
    this_client.standbyReceive();
    if(this_client.getReceiveFlag() == 1)
    {
        vector<string> temp_buffer = this_client.getBufferProtocol();
        if(temp_buffer[0] == "LIST_USER" && temp_buffer[1] == "LIST_USER_SEND")
        {
            setDataOnlineUsers();
        }
        else
        if(temp_buffer[0] == "INCHAT" && temp_buffer[1] == "SEND_MESSAGE")
        {
            openChatMenu();
        }
        this_client.setReceiveFlag(0);
    }
}

void ListUserWindow::setChatFriend(int index)
{
    vector<list_username> tempusr = this_client.getUsers();

    this->chatFriend = tempusr[index].username;
}

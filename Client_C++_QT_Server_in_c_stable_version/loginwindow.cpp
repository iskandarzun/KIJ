#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "listuserwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect_slots();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::connect_slots()
{
    connect(ui->usernameLogin,SIGNAL(textChanged(QString)),this,SLOT(usernameLoginInput(QString)));
    connect(ui->passwordLogin,SIGNAL(textChanged(QString)),this,SLOT(passwordLoginInput(QString)));
    connect(ui->loginButton,SIGNAL(clicked()),this,SLOT(loginStart()));
    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(backToMenu()));
}

void LoginWindow::loginStart()
{
    if(this_client.getErrorFlag() == 1)
    {
        this->errorShow();
    }
    else
    {
        this_client.transferData("LOGIN", "AUTH_REQ", "0", "0", "AUTH", this->username+":"+this->password);
        if(this_client.getErrorFlag() == 1)
        {
            this->errorShow();
        }
        else
        {
            vector<string> received_buffer = this_client.getBufferProtocol();
            if(received_buffer[1] == "LOGIN_SUCCESS")
            {
                this_client.setUsername(this->username);
                this->goToListUserMenu();
                //printf("SUCCESS");

            }
            else
            if(received_buffer[1] == "LOGIN_FAILED")
            {
                this_client.setErrorFlag(1);
                this_client.setErrorType("Data akun tidak ditemukan, coba daftar dahulu!");
                this->errorShow();
            }
        }
    }
}

void LoginWindow::usernameLoginInput(QString text)
{
    this->username = text.toStdString();
}

void LoginWindow::passwordLoginInput(QString text)
{
    this->password = text.toStdString();
}

void LoginWindow::goToListUserMenu()
{
    this_client.setPreviousWindow(*this);
    this->hide();
    currentWindow = new ListUserWindow();
    currentWindow->show();
    currentWindow->raise();
    currentWindow->activateWindow();
}

void LoginWindow::errorShow()
{
    this_client.setPreviousWindow(*this);
    this->hide();
    errorWindow = new ErrorWindow();
    errorWindow->setErrorMessage(this_client.getErrorType());
    errorWindow->show();
    errorWindow->raise();
    errorWindow->activateWindow();
}

void LoginWindow::backToMenu()
{
    this->hide();
    currentWindow = this_client.getPreviousWindow();
    currentWindow->show();
    currentWindow->raise();
    currentWindow->activateWindow();
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
    this_client.closeConnection();
}

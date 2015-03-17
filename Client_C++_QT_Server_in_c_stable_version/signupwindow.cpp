#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "listuserwindow.h"

SignupWindow::SignupWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
    connect_slots();
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

void SignupWindow::connect_slots()
{
    connect(ui->signupUsername,SIGNAL(textChanged(QString)),this,SLOT(signupUsernameInput(QString)));
    connect(ui->signupPassword,SIGNAL(textChanged(QString)),this,SLOT(signupPasswordInput(QString)));
    connect(ui->signupConfirmPassword,SIGNAL(textChanged(QString)),this,SLOT(signupConfirmPasswordInput(QString)));
    connect(ui->signupButton,SIGNAL(clicked()),this,SLOT(signupStart()));
    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(backToMenu()));
}

void SignupWindow::signupStart()
{

    if(this_client.getErrorFlag() == 1)
    {
        this->errorShow();
    }
    else
    if(this->password != this->confirmPassword)
    {
        this_client.setErrorFlag(1);
        this_client.setErrorType("Password tidak cocok, masukkan lagi!");
    } //no error
    else
    {
        this_client.transferData("SIGNUP", "AUTH_REQ", "0", "0", "AUTH", this->username+":"+this->password);
        if(this_client.getErrorFlag() == 1)
        {
            this->errorShow();
        }
        else
        {
            vector<string> received_buffer = this_client.getBufferProtocol();
            if(received_buffer[1] == "SIGNUP_SUCCESS")
            {
                this_client.setUsername(this->username);
                this->goToListUserMenu();
                //printf("SUCCESS");

            }
            else
            if(received_buffer[1] == "SIGNUP_FAILED")
            {
                this_client.setErrorFlag(1);
                this_client.setErrorType("Data akun sudah dipakai atau error saat dibuat!");
                this->errorShow();
            }
        }
    }
}

void SignupWindow::signupUsernameInput(QString text)
{
    //if(text.length() > 2 && text.length() < MAX_USER_INPUT)
    //{
        this->username = text.toStdString();
    //}
    //else
    //{
    //    this_client.setErrorFlag(1);
    //    this_client.setErrorType("Username karakter terlalu sedikit atau banyak (min 3)!");
    //}
}

void SignupWindow::signupPasswordInput(QString text)
{
    //if(text.length() > 5 && text.length() < MAX_USER_INPUT)
    //{
        this->password = text.toStdString();
    //}
    //else
    //{
    //    this_client.setErrorFlag(1);
    //    this_client.setErrorType("Password karakter terlalu sedikit atau banyak (min 5)!");
    //}
}

void SignupWindow::signupConfirmPasswordInput(QString text)
{
    this->confirmPassword = text.toStdString();
}

void SignupWindow::goToListUserMenu()
{
    this_client.setPreviousWindow(*this);
    this->hide();
    currentWindow = new ListUserWindow();
    currentWindow->show();
    currentWindow->raise();
    currentWindow->activateWindow();
}

void SignupWindow::errorShow()
{
    this_client.setPreviousWindow(*this);
    this->hide();
    errorWindow = new ErrorWindow();
    errorWindow->setErrorMessage(this_client.getErrorType());
    errorWindow->show();
    errorWindow->raise();
    errorWindow->activateWindow();
}

void SignupWindow::backToMenu()
{
    this->hide();
    currentWindow = this_client.getPreviousWindow();
    currentWindow->show();
    currentWindow->raise();
    currentWindow->activateWindow();
}

void SignupWindow::closeEvent(QCloseEvent *event)
{
    this_client.closeConnection();
}



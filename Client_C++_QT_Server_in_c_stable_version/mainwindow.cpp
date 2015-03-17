#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signupwindow.h"
#include "loginwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect_slots();
    this_client.closeConnection();
    /*
    allMenuBar = new QMenuBar(this);
    allMenuBar->clear();

    QMenu *aboutMenu = new QMenu("Menu");
    aboutMenu->addAction("Tentang");
    allMenuBar->addAction(aboutMenu->menuAction());
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_slots()
{
    connect(ui->menuSignupButton,SIGNAL(clicked()),this,SLOT(checkErrorSignup()));
    connect(ui->menuLoginButton,SIGNAL(clicked()),this,SLOT(checkErrorLogin()));
    connect(ui->serverAddress,SIGNAL(textChanged(QString)),this,SLOT(serverAddressInput(QString)));
}

void MainWindow::checkErrorSignup()
{
    this_client.connectToServer(this->serverAddress, 8888);

    if(this->serverAddress.size() == 0)
    {
        this_client.setErrorFlag(1);
        this_client.setErrorType("Alamat server salah atau sedang tidak aktif!");
        this->errorShow();
    }
    else
    if(this_client.getErrorFlag() == 1)
    {
        this_client.setErrorType("Koneksi ke server gagal, cek koneksi ke server!");
        this->errorShow();
    }
    else
    {
        this->goToSignupMenu();
    }
}

void MainWindow::checkErrorLogin()
{
    this_client.connectToServer(this->serverAddress, 8888);

    if(this->serverAddress.size() == 0)
    {
        this_client.setErrorFlag(1);
        this_client.setErrorType("Alamat server salah atau sedang tidak aktif!");
        this->errorShow();
    }
    else
    if(this_client.getErrorFlag() == 1)
    {
        this_client.setErrorType("Koneksi ke server gagal, cek koneksi ke server!");
        this->errorShow();
    }
    else
    {
        this->goToLoginMenu();
    }
}


void MainWindow::goToSignupMenu()
{
    this_client.setPreviousWindow(*this);
    this->hide();
    signupWindow = new SignupWindow();
    signupWindow->show();
    signupWindow->raise();
    signupWindow->activateWindow();
}

void MainWindow::goToLoginMenu()
{
    this_client.setPreviousWindow(*this);
    this->hide();
    loginWindow = new LoginWindow();
    loginWindow->show();
    loginWindow->raise();
    loginWindow->activateWindow();
}

void MainWindow::errorShow()
{
    this_client.setPreviousWindow(*this);
    this->hide();
    errorWindow = new ErrorWindow();
    errorWindow->setErrorMessage(this_client.getErrorType());
    errorWindow->show();
    errorWindow->raise();
    errorWindow->activateWindow();
}

void MainWindow::serverAddressInput(QString text)
{
    if(!text.isEmpty())
    {
        this->serverAddress = text.toStdString();
    }
    else
    {
        this->serverAddress = "";
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    this_client.closeConnection();
}

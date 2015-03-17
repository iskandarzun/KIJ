#include "errorwindow.h"
#include "ui_errorwindow.h"
#include "mainwindow.h"

ErrorWindow::ErrorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);
    connect_slots();
}

ErrorWindow::~ErrorWindow()
{
    delete ui;
}

void ErrorWindow::connect_slots()
{
    connect(ui->backButton,SIGNAL(clicked()),this,SLOT(goToPreviousMenu()));
}

void ErrorWindow::setErrorMessage(string text)
{
    this->message.append(QString::fromStdString(text));
    ui->errorMessage->setText(this->message);
    ui->errorMessage->adjustSize();
}

void ErrorWindow::goToPreviousMenu()
{
    this_client.setErrorFlag(0);
    this->hide();
    previousWindow = this_client.getPreviousWindow();
    previousWindow->show();
    previousWindow->raise();
    previousWindow->activateWindow();
}

void ErrorWindow::closeEvent(QCloseEvent *event)
{
   this_client.closeConnection();
}

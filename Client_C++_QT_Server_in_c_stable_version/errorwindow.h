#ifndef ERRORWINDOW_H
#define ERRORWINDOW_H

//#include <QMainWindow>
#include "clientdata.h"

using namespace std;

namespace Ui {
class ErrorWindow;
}

class ErrorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ErrorWindow(QWidget *parent = 0);
    void setErrorMessage(string);
    ~ErrorWindow();

public slots:
    void connect_slots();

private slots:
    void goToPreviousMenu();
    void closeEvent(QCloseEvent *);

private:
    Ui::ErrorWindow *ui;
    QString message;
    QMainWindow *previousWindow;
};

#endif // ERRORWINDOW_H

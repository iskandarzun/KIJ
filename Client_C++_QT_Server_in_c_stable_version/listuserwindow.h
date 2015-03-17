#ifndef LISTUSERWINDOW_H
#define LISTUSERWINDOW_H

#include <QMainWindow>
#include "clientdata.h"
#include "errorwindow.h"
#include "chatmenu.h"

namespace Ui {
class ListUserWindow;
}

class ListUserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ListUserWindow(QWidget *parent = 0);
    ~ListUserWindow();

public slots:
    void connect_slots();

private slots:
    void setActiveUsername();
    void setDataOnlineUsers();
    void chatStart();
    void openChatMenu();
    void logout();
    void errorShow();
    void activateWindow();
    void setChatFriend(int);

private:
    Ui::ListUserWindow *ui;
    ErrorWindow *errorWindow;
    ChatMenu *chatMenu;
    string chatFriend;
};

#endif // LISTUSERWINDOW_H

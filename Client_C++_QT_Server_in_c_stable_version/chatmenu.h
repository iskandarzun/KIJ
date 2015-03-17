#ifndef CHATMENU_H
#define CHATMENU_H

#include <QMainWindow>
#include "clientdata.h"

namespace Ui {
class ChatMenu;
}

class ChatMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatMenu(QWidget *parent = 0);
    ~ChatMenu();

public slots:
    void setChatFriend(string);
    string getChatFriend();
    void setActiveChatFriend();
    void showEvent(QShowEvent *);

private:
    Ui::ChatMenu *ui;
    string chatFriend;
};

#endif // CHATMENU_H

#include "chatmenu.h"
#include "ui_chatmenu.h"

ChatMenu::ChatMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatMenu)
{
    ui->setupUi(this);
}

ChatMenu::~ChatMenu()
{
    delete ui;
}

string ChatMenu::getChatFriend()
{
    return this->chatFriend;
}

void ChatMenu::setChatFriend(string name)
{
    this->chatFriend = name;
}

void ChatMenu::setActiveChatFriend()
{
    string message = "Percakapan dengan " + this->chatFriend + ":";
    ui->anotherUser->setText(QString::fromStdString(message));
}

void ChatMenu::showEvent(QShowEvent *event)
{
    setActiveChatFriend();
}

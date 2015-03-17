#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <QMainWindow>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX_BUFFER 4096
#define MAX_USER_INPUT 512

QT_BEGIN_NAMESPACE
class QMainWindow;
class QMenuBar;
class QMessageBox;
class QCloseEvent;

using namespace std;

typedef struct all_users
{
    string username;
    vector<string> chat_history;
} list_username;

class ClientData
{
public:
    ClientData();
    ClientData(string, int, int, string);

    //get function
    string getConnectedServer();
    int getServerSocket();
    int getPort();
    string getUsername();
    vector<list_username> getUsers();
    int getErrorFlag();
    string getErrorType();
    int getReceiveFlag();
    QMainWindow* getPreviousWindow();
    vector<string> getBufferProtocol();

    //set function
    void setConnectedServer(string);
    void setServerSocket(int);
    void setPort(int);
    void setUsername(string);
    void setUsers(list_username);
    void setUsers(string);
    void setErrorFlag(int);
    void setErrorType(string);
    void setReceiveFlag(int);
    void setPreviousWindow(QMainWindow&);

    //system function
    void connectToServer(string, int);
    void transferData(string, string, string, string, string, string);
    void inputUsers();
    void standbyReceive();
    QMainWindow *backToMainWindow();
    void closeConnection();

private:
    string connected_server;
    int server_socket;
    int port;
    string username;
    vector<list_username> users;
    int errorFlag;
    string errorType;
    int receiveFlag;
    vector<string> bufferProtocol;
    vector<QMainWindow *> previousWindow;
    string getFormatMessage(string, string, string, string, string ,string);\
    vector<string> stripFormatMessage();
    void setBufferProtocol(char[MAX_BUFFER]);
};
QT_END_NAMESPACE

//declared global class
extern ClientData this_client;
extern QMainWindow *currentWindow;

#endif // CLIENTDATA_H

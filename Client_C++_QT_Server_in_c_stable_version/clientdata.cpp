#include "clientdata.h"
#include "mainwindow.h"

//constructor

ClientData::ClientData()
{
    this->setConnectedServer("127.0.0.1");
    this->setServerSocket(0);
    this->setPort(8888);
    this->setUsername("Default");
    this->setErrorFlag(0);
}

ClientData::ClientData(string connected_server, int server_socket, int port, string username)
{
    this->setConnectedServer(connected_server);
    this->setServerSocket(server_socket);
    this->setPort(port);
    this->setUsername(username);
    this->setErrorFlag(0);
}

//end of constructor

//get function below

string ClientData::getConnectedServer()
{
    return this->connected_server;
}

int ClientData::getServerSocket()
{
    return this->server_socket;
}

int ClientData::getPort()
{
    return this->port;
}

string ClientData::getUsername()
{
    return this->username;
}

vector<list_username> ClientData::getUsers()
{
    return this->users;
}

int ClientData::getErrorFlag()
{
    return this->errorFlag;
}

string ClientData::getErrorType()
{
    return this->errorType;
}

int ClientData::getReceiveFlag()
{
    return this->receiveFlag;
}

QMainWindow* ClientData::getPreviousWindow()
{
    if(!this->previousWindow.empty())
    {
        QMainWindow *temp = this->previousWindow.back();
        this->previousWindow.pop_back();
        return temp;
    }
    else
        return NULL;
}

vector<string> ClientData::getBufferProtocol()
{
    return this->bufferProtocol;
}

//end of get function

//set function below

void ClientData::setConnectedServer(string connected_server)
{
    this->connected_server = connected_server;
}

void ClientData::setServerSocket(int server_socket)
{
    this->server_socket = server_socket;
}

void ClientData::setPort(int port)
{
    this->port = port;
}

void ClientData::setUsername(string username)
{
    this->username = username;
}

void ClientData::setUsers(list_username users)
{
    this->users.push_back(users);
}

void ClientData::setUsers(string name)
{
    list_username user_data;
    user_data.username = name;
    this->users.push_back(user_data);
}

void ClientData::setErrorFlag(int flag)
{
    this->errorFlag = flag;
}

void ClientData::setErrorType(string type)
{
    this->errorType = type;
}

void ClientData::setReceiveFlag(int flag)
{
    this->receiveFlag = flag;
}

void ClientData::setPreviousWindow(QMainWindow &prev)
{
    this->previousWindow.push_back(&prev);
}

void ClientData::setBufferProtocol(char message[MAX_BUFFER])
{
    int i;
    QString messageQ = message;
    QRegExp rx("\r\n");
    QStringList query = messageQ.split(rx);
    this->bufferProtocol.clear();

    /*
    if(query[1].toStdString() == "LIST_USER_SEND")
    {
        this->setErrorFlag(1);
        this->setErrorType(query[5].toStdString());
    } */

    if(query.size() != 6)
    {
        this->setErrorFlag(1);
        string number;
        stringstream ss2;
        ss2 << query.size();
        ss2 >> number;
        string pesan = "Pesan tidak sesuai dengan protokol (" + number + " pesan)!" ;
        this->setErrorType(pesan);
    }
    else
    {
        for(i = 0; i < query.size(); i++)
        {
            this->bufferProtocol.push_back(query[i].toStdString());
        }
    }
}

//end set function

//system function below

void ClientData::connectToServer(string address, int port)
{
    int sock;
    struct sockaddr_in server;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    //printf("%d\n",sock);
    if (sock == -1)
    {
        this->setErrorFlag(1);
        this->setErrorType("Tidak dapat membuat socket!");
        //printf("Could not create socket");
    }

    //puts("Socket created");

    if(address.length() > 15)
    {
        this->setErrorFlag(1);
        this->setErrorType("IP Address terlalu panjang!");
    }
    else
    {
        const char *address_converted = address.c_str();

        server.sin_addr.s_addr = inet_addr(address_converted);
        server.sin_family = AF_INET;
        server.sin_port = htons( port );

        //Connect to remote server
        if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
            this->setErrorFlag(1);
            this->setErrorType("Koneksi ke server socket error!");
            /*
            perror("connect failed. Error");
            return 1;
            */
        }

        this->setConnectedServer(address);
        this->setServerSocket(sock);
        this->setPort(port);

        //puts("Connected\n");
    }
}

void ClientData::transferData(string state, string flag, string receiver, string sender, string content_type, string content)
{
    string protocol_message = "";
    char temp_protocol_message[MAX_BUFFER];
    char received_message[MAX_BUFFER];

    protocol_message = this->getFormatMessage(state, flag, receiver, sender, content_type, content);
    std::strcpy(temp_protocol_message, protocol_message.c_str());

    //encrypt here
    send(this->server_socket, temp_protocol_message, protocol_message.size()+1, 0);
    recv(this->server_socket, received_message, MAX_BUFFER, 0);

    this->setBufferProtocol(received_message); //finished
}

void ClientData::inputUsers()
{
    QString all_users = QString::fromStdString(this->bufferProtocol[5]);
    QRegExp rx(":");
    QStringList users_split = all_users.split(rx);
    int i;
    this->users.clear();
    for(i = 0; i < users_split.size(); i++)
    {
        this->setUsers(users_split[i].toStdString());
    }
}

void ClientData::standbyReceive()
{
    int read_size = 0;
    char client_message[MAX_BUFFER];

    while( (read_size = recv(this->getServerSocket() , client_message , MAX_BUFFER , 0)) > 0)
    {
        this->setReceiveFlag(1);
        this->setBufferProtocol(client_message);
    }
}

string ClientData::getFormatMessage(string state, string flag, string receiver, string sender, string content_type, string content)
{
    string output = "";
    output += state + "\r\n" + flag + "\r\n" + receiver + "\r\n" + sender + "\r\n" + content_type + "\r\n" + content;
    return output;
}

QMainWindow* ClientData::backToMainWindow()
{
    QMainWindow *main = this->previousWindow[0];
    this->previousWindow.clear();
    return main;
}

void ClientData::closeConnection()
{
    close(this->getServerSocket());
}

//end of system function

ClientData this_client;
QMainWindow *currentWindow;

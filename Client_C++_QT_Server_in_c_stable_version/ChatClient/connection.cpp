#include "connection.h"

Connection::Connection(QObject *parent) :
    QObject(parent)
{
    this->socket = new QTcpSocket(this);
    this->connect_slots();
}

//connect slots
void Connection::connect_slots()
{
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(emitSignalReady()));
}

//get function
QString Connection::getServerAdress()
{
    return this->serverAddress;
}

int Connection::getPort()
{
    return this->port;
}

//set function
void Connection::setServerAddress(QString address)
{
    this->serverAddress = address;
}

void Connection::setPort(int port)
{
    this->port = port;
}

//system function
void Connection::sendData(QString state, QString flag, QString receiver, QString sender, QString type, QString content)
{
    //encrypt here
    this->socket->write(this->getFormatMessage(state, flag, receiver, sender, type, content).toUtf8());
}

QString Connection::readData()
{
    //decrypt here
    return QString::fromUtf8(this->socket->read(MAX_BUFFER).trimmed());
}

void Connection::ConnectingToServer()
{
    this->socket->connectToHost(this->serverAddress, this->port);
}

void Connection::disconnecting()
{
    this->socket->disconnectFromHost();
}

bool Connection::isConnectedToServer()
{
    return this->socket->waitForConnected(WAIT_TIME);
}

void Connection::waiting()
{
    this->socket->waitForReadyRead(WAIT_TIME);
}

void Connection::emitSignalReady()
{
    emit incomingData();
}

//Private function
QString Connection::getFormatMessage(QString state, QString flag, QString receiver, QString sender, QString type, QString content)
{
    QString output;
    output += state + "\r\n" + flag + "\r\n" + receiver + "\r\n" + sender + "\r\n" + type + "\r\n" + content;
    return output;
}

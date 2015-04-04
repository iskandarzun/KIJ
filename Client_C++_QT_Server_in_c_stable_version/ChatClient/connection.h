#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#define MAX_BUFFER 4096
#define WAIT_TIME 3000 //in miliseconds

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = 0);

signals:
    void incomingData();

public slots:
    //Connected slots
    void connect_slots();

    //Get function
    QString getServerAdress();
    int getPort();

    //Set function
    void setServerAddress(QString);
    void setPort(int);

    //System function
    void sendData(QString, QString, QString, QString, QString, QString);
    QString readData();
    void ConnectingToServer();
    void disconnecting();
    bool isConnectedToServer();
    void waiting();
    void emitSignalReady();


private:
    //Properties
    QTcpSocket *socket;
    QString serverAddress;
    int port;

    //Private Function
    QString getFormatMessage(QString, QString, QString, QString, QString, QString);


};

#endif // CONNECTION_H

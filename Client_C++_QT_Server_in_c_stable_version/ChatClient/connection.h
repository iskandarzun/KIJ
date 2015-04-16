#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QObject>
#include <QTcpSocket>
#define MAX_BUFFER 8192
#define MAX_STRING 4096
#define WAIT_TIME 3000 //in miliseconds
#define Nb 4
#define MAX_DIVIDE MAX_BUFFER / 32
#define MAX_BUFF_DIVIDE MAX_STRING / 16

// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

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

    //AES Properties
    unsigned char Key[32];
    unsigned char RoundKey[240];
    char IV[MAX_BUFFER];
    int Nk;
    int Nr;
    int AES_Mode;
    unsigned char in[16], out[16], state[4][4];

    //AES Function
    QString AES_Encrypt(QString message);
    QString AES_Decrpyt(QString message);
    int getSBoxValue(int);
    int getRconValue(int);
    void KeyExpansion();
    void AddRoundKey(int);
    void SubBytes();
    void ShiftRows();
    void MixColumns();
    void Cipher();
    char hexDigit(unsigned);
    void charToHex(char, char[2]);
    char hexToAscii(char, char);
    void uncharToChar(char*, unsigned char*, size_t);
    void convertToReal(char*, char*);
    void containHex(char[MAX_BUFFER][1], char*);

    void xor_str(char*, char*, char*);
    void char2hex(char*, char*);
    void divideAscii(char[MAX_STRING][17], char*);
    void divideHexa(char[MAX_BUFFER][33], char*);


    //Private Function
    QString getFormatMessage(QString, QString, QString, QString, QString, QString);


};

#endif // CONNECTION_H

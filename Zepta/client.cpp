#include "client.h"
client::client()
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    tcpSocket = new QTcpSocket(this);

    //connect(tcpSocket, &QIODevice::readyRead, this, &client::establishServerConnection);

    tcpSocket->connectToHost(QString("95.80.47.153"), QString("65432").toInt());
    if(tcpSocket->waitForConnected())
        qDebug() << "Connected to Server";

}

client::~client()
{
    tcpSocket->close(); // always close socket.
    delete tcpSocket;

}

void client::send_room_code(std::string data)
{
    char buff[2048];
    strcpy(buff, data.c_str()); // Memory buffer is limited and can cause error if it is large. should never be the case tho
    tcpSocket->write(buff);
    tcpSocket->waitForBytesWritten(3000);
}

void client::send_public_key(char* data)
{
    tcpSocket->write(data);
    tcpSocket->waitForBytesWritten(1000);
}

void client::send_encrypted_message(char *data)
{
    tcpSocket->write(data);
    tcpSocket->waitForBytesWritten(20);
}

QByteArray client::recieve_code()
{
    tcpSocket->waitForReadyRead(3000);
    auto message =tcpSocket->readAll();
    return message;
}

void client::connet_to_server()
{
    tcpSocket->connectToHost(QString("95.80.47.153"), QString("65432").toInt());
    if(tcpSocket->waitForConnected())
        qDebug() << "Connected to Server";
}






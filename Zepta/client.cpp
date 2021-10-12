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
    char buff[1024];
    strcpy(buff, data.c_str()); // Memory buffer is limited and can cause error if it is large
    tcpSocket->write(buff);
    tcpSocket->waitForBytesWritten(1000);
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






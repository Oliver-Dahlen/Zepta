#pragma once
#include <QGuiApplication>
#include <QLineEdit>
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QtDebug>
#include "dialog.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <string>
#include <QLabel>
#include <QtWidgets>
#include <QPixmap>
#include <QRect>
#include <iostream>
#include <QDataStream>
#include <QTcpSocket>
#include <QAbstractSocket>

#define PORT = "65432"

class client : public QDialog
{
public:

    client();
    ~client();
    void send_room_code(std::string data);
    void connet_to_server();
    QTcpSocket *tcpSocket;

    QByteArray recieve_code();
private:
    QDataStream in;
    QString currentFortune;




};



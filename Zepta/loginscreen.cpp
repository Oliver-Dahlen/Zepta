#include "loginscreen.h"

loginScreen::loginScreen()
{
    background = new QLabel(this);
    button = new QPushButton(this);
    room_code = new QLineEdit(this);
    cli = new client();
    display_text = new QLabel(this);

    background->setGeometry(QRect(0,0,420,665));
    background->setPixmap(QPixmap( ":/resources/img/background.png" ));
    background->setScaledContents(true);

    button->setGeometry(QRect(80,350,291,31));
    button->setStyleSheet("background-color: rgb(54, 54, 54); font-size:14pt;\ncolor: rgb(255, 255, 255); border: 2px solid white;border-radius: 10px;");
    button->setText("Get message");

    room_code->setGeometry(QRect(0, 0, 291, 31));
    room_code->setPlaceholderText("Room code");
    room_code->setStyleSheet("border: 2px solid white;\n border-radius: 10px;\ncolor: rgb(255, 255, 255); background: rgb(54, 54, 54);");

    display_text->setText("rthfththfhf");
    display_text->setGeometry(QRect(100,100,291,31));

    connect(button, &QPushButton::released, this, &loginScreen::button_func); // Assign button function
}

loginScreen::~loginScreen()
{
    delete room_code;
    delete background;
    delete button;
    delete cli;
    delete display_text; // delete every thing created on the heap. Could use smart pointers insted i guess :/
}

void loginScreen::button_func()
{

    if(cli->tcpSocket->state() == QAbstractSocket::ConnectedState) // make sure that we have connection to sever before we send send room code;
    {
    cli->send_room_code(room_code->text().toStdString());
    auto message = cli->recieve_code();
    display_text->setText(message);
    }
    else
    {
        qDebug() << "No connection to server";
        qDebug() << "Trying to connect...";
        cli->connet_to_server();
    }

}

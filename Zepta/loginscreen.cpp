#include "loginscreen.h"
std::string WRONG_CODE = "The room code given is not valid";
std::string NO_DATA_ON_CODE = "No data";
loginScreen::loginScreen(rsa *rsap)
{
    rsaptr = rsap;
    background = new QLabel(this);
    button = new QPushButton(this);
    send_button = new QPushButton(this);
    room_code = new QLineEdit(this);
    data_to_send = new QLineEdit(this);
    cli = new client();
    display_text = new QLabel(this);

    background->setGeometry(QRect(0,0,420,670));
    background->setPixmap(QPixmap( ":/resources/img/background.png" ));
    background->setScaledContents(true);

    button->setGeometry(QRect(80,350,291,31));
    button->setStyleSheet("background-color: rgb(54, 54, 54); font-size:14pt;\ncolor: rgb(255, 255, 255); border: 2px solid white;border-radius: 10px;");
    button->setText("Get message");

    room_code->setGeometry(QRect(0, 0, 291, 31));
    room_code->setPlaceholderText("Room code");
    room_code->setStyleSheet("border: 2px solid white;\n border-radius: 10px;\ncolor: rgb(255, 255, 255); background: rgb(54, 54, 54);");

    display_text->setText("Text to be displayed");
    display_text->setGeometry(QRect(100,100,291,31));

    data_to_send->setGeometry(QRect(0,32,291,31));
    data_to_send->setPlaceholderText("Message");
    data_to_send->setStyleSheet("border: 2px solid white;\n border-radius: 10px;\ncolor: rgb(255, 255, 255); background: rgb(54, 54, 54);");

    send_button->setGeometry(QRect(80,400,291,31));
    send_button->setStyleSheet("background-color: rgb(54, 54, 54); font-size:14pt;\ncolor: rgb(255, 255, 255); border: 2px solid white;border-radius: 10px;");
    send_button->setText("send message");

    connect(send_button, &QPushButton::released, this, &loginScreen::button_func_send);
    connect(button, &QPushButton::released, this, &loginScreen::button_func); // Assign button function
}

void loginScreen::button_func_send()
{

}

void loginScreen::button_func()
{

    if(cli->tcpSocket->state() == QAbstractSocket::ConnectedState) // make sure that we have connection to sever before we send send room code;
    {
    cli->send_room_code(room_code->displayText().toStdString());
    auto message = cli->recieve_code();
    display_text->setText(message);

    if(message.toStdString() == WRONG_CODE)
    {
        qDebug() << "Wrong code";
    }

    if(message.toStdString() == NO_DATA_ON_CODE)
    {
        cli->send_public_key(rsaptr->get_public_key_text());
    }

    rsaptr->create_file("public_key_room.txt");
    rsaptr->file->open(QIODevice::WriteOnly);
    rsaptr->file->write(message.data());
    rsaptr->file->close();
    auto y = rsaptr->encrypt_data("encrypt", "public_key_room.txt");

    QByteArray jj = y;

    cli->send_encrypted_message(jj.toBase64().data());
    cli->tcpSocket->waitForReadyRead(3000);
    auto meg =cli->tcpSocket->readAll();
    qDebug() << meg;
    qDebug() << "hi";
    if(meg == "Encrypted message already exsist")
    {
        QByteArray ii = y;
        qDebug() << "no";
        qDebug() << ii.toBase64();
        cli->tcpSocket->waitForReadyRead(3000);

        auto megg = cli->tcpSocket->readAll();
        QByteArray kk = megg;
        qDebug() << megg;
        qDebug() << kk.fromBase64(kk.data()).data();
        qDebug() <<kk.fromBase64(kk.data()).data();
        qDebug() << rsaptr->decrypy_data(kk.fromBase64(kk.data()).data(), rsaptr->private_key_path_name);
    }

    rsaptr->file->close();


    }
    else
    {
        qDebug() << "No connection to server";
        qDebug() << "Trying to connect...";
        cli->connet_to_server();
    }

}


loginScreen::~loginScreen()
{
    delete room_code;
    delete background;
    delete button;
    delete cli;
    delete display_text; // delete every thing created on the heap. Could use smart pointers insted i guess :/
    delete send_button;
    delete data_to_send;
}

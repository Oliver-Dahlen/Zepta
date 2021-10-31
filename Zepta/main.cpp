#include <QGuiApplication>
#include <QLineEdit>
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QtDebug>
#include <QMainWindow>
#include <QStackedWidget>
#include <string>
#include <QLabel>
#include <QtWidgets>
#include <QPixmap>
#include <QRect>
#include <iostream>
#include "loginscreen.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include "rsa.h"
#include <fstream>

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);


    QStackedWidget window;
    rsa RSAA;

    loginScreen log(&RSAA);
    char plainText[2048/8] = "Hello this is Oliver";

    auto data = RSAA.encrypt_data(plainText, RSAA.public_key_path_name);
    auto de =  RSAA.decrypy_data(data, RSAA.private_key_path_name);


    window.setWindowTitle("Zepta");
    window.addWidget(&log);
    window.setFixedHeight(400);
    window.setFixedWidth(400);

    window.show();
    return app.exec();
}

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

    window.setWindowTitle("Zepta");
    window.addWidget(&log);
    window.setFixedHeight(400);
    window.setFixedWidth(400);

    window.show();
    return app.exec();
}

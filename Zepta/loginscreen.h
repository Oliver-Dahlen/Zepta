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
#include "client.h"
#include "rsa.h"
class loginScreen : public QDialog
{
public:

    loginScreen(rsa *rsaptr);
    ~loginScreen();

    client *cli;

private:
    rsa *rsaptr;
    QLineEdit *room_code;
    QLineEdit *data_to_send;
    QLabel *background;
    QPushButton *button;
    QPushButton *send_button;
    QLabel *display_text;
    void button_func();
    void button_func_send();

};

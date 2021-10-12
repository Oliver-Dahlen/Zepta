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
class loginScreen : public QDialog
{
public:

    loginScreen();
    ~loginScreen();


private:
    client *cli;
    QLineEdit *room_code;
    QLabel *background;
    QPushButton *button;
    QLabel *display_text;
    void button_func();

};

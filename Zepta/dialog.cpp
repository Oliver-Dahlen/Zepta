#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
Dialoge::Dialoge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialoge::~Dialoge()
{
    delete ui;
}


void Dialoge::on_pushButton_clicked()
{
    qDebug() << ui->lineEdit->text();

}


#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialoge : public QDialog
{
    Q_OBJECT

public:
    explicit Dialoge(QWidget *parent = nullptr);
    ~Dialoge();
    void get();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

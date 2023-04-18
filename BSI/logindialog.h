#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QVector>
#include "backend.h"
#include "utilities.h"
#include "mainwindow.h"

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

private slots:
    void on_loginbutton_clicked();


private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H

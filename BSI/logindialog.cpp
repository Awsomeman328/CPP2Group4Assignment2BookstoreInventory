#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog() :
    QDialog()
{
    //ui->setupUi(this);

    outputToLogFile("loginDialog() ... I have been made!");

}

loginDialog::~loginDialog()
{
    //delete ui;
    outputToLogFile("loginDialog() ... I have been deleted!");
}

void loginDialog::on_loginbutton_clicked()
{
    /*
    QString username = ui->username->text();
    QString password = QString::fromStdString( hash_password( ui->password->text().toStdString() ) );

    QVector<bool> loginresults = attemptLogin(username, password);

    if(loginresults[0])
    {
        QMessageBox::information(this, "Login", "Successful login!");
        emit loginClicked();
        loginDialog::close();
    }

    else
    {
        QMessageBox::information(this, "Login", "Login failed");
    }
    */
}


#include "loginscreen.h"
#include "ui_loginscreen.h"

loginscreen::loginscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginscreen)
{
    ui->setupUi(this);
}

loginscreen::~loginscreen()
{
    delete ui;
}

void loginscreen::logIn()
{
    QString username = ui->username->text();
    QString password = QString::fromStdString( hash_password( ui->password->text().toStdString() ) );

    QVector<bool> loginStatus = attemptLogin(username, password);

    if (loginStatus.size() == NULL)
    {

        outputToLogFile("loginscreen::logIn() Login Failed! No UserPass pairs of given inputs.");

    }
    else if (loginStatus.size() == 1)
    {

        if (loginStatus[0])
        {
            outputToLogFile("loginscreen::logIn() Login Successful! Admin Access Granted!");
        }
        else
        {
            outputToLogFile("loginscreen::logIn() Login Successful!");
        }

    }
    else
    {

        outputToLogFile("loginscreen::logIn() DB ERROR: Login Attempt Failed! More than 1 UserPass pairs found.");

    }

}

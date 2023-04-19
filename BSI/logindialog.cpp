#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);

    MainWindow w;
    QRect primaryGeometry = QGuiApplication::primaryScreen()->geometry();
    w.move(primaryGeometry.center() - w.rect().center());
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_loginbutton_clicked()
{
    QString username = ui->username->text();
    QString password = QString::fromStdString( hash_password( ui->password->text().toStdString() ) );

    QVector<bool> loginresults = attemptLogin(username, password);

    if(loginresults[0])
    {
        QMessageBox::information(this, "Login", "Successful login!");
//        mainW.show();
        loginDialog::close();
    }

    else
    {
        QMessageBox::information(this, "Login", "Login failed");
    }
}


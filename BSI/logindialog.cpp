#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
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
        MainWindow w;
        QRect primaryGeometry = QGuiApplication::primaryScreen()->geometry();
        w.move(primaryGeometry.center() - w.rect().center());
        QMessageBox::information(this, "Login", "Successful login!");
        QTimer::singleShot(3872, &w, SLOT(show()));
        loginDialog::hide();
    }

    else
    {
        QMessageBox::information(this, "Login", "Login failed");
    }
}


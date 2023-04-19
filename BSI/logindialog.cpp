#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog() :
    QDialog()
{
    //ui->setupUi(this);

    outputToLogFile("loginDialog() ... I have been made!");

    usernameLabel = new QLabel(tr("Username:"));
    usernameLineEdit = new QLineEdit();
    passwordLabel = new QLabel(tr("Password:"));
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton(tr("Login"));

    connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
     layout->addWidget(loginButton);

    setLayout(layout);
}

loginDialog::~loginDialog()
{
    //delete ui;
    outputToLogFile("loginDialog() ... I have been deleted!");
}

void loginDialog::login()
{

    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    // Authenticate username and password against system
    QVector<bool> loginresults = attemptLogin(username, password);

    if(loginresults[0])
    {
        /*
        QMessageBox::information(this, "Login", "Successful login!");
        emit loginClicked();
        loginDialog::close();
        */
        accept(); // Close the dialog and allow access to the main application
    }

    else
    {
        QMessageBox::warning(this, tr("Login Failed"), tr("Invalid username or password."));
    }

}


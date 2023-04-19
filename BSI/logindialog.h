#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "backend.h"
#include "utilities.h"
#include "mainwindow.h"

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog();
    ~loginDialog();

private slots:
    void login();


signals:
    void loginClicked();
    void exitClicked();
    void userIsAdmin();

private:
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
};

#endif // LOGINDIALOG_H

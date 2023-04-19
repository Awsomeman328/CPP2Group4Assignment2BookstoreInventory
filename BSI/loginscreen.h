#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QDialog>
#include <QVector>
#include "backend.h"
#include "utilities.h"
#include <ui_loginscreen.h> // include the UI definition file

namespace Ui {
class loginscreen;
}

class loginscreen : public QDialog
{
    Q_OBJECT

public:
    explicit loginscreen();
//
    explicit loginscreen(QWidget *parent = nullptr);
    ~loginscreen();

private:
    Ui::loginscreen *ui;

    // private helper functions
    QVector<bool> attemptLogin(QString username, QString password);
    std::string hash_password(std::string password);

private slots:
    void logIn();
};

#endif // LOGINSCREEN_H

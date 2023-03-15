#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "dbmanager.h"
#include "hashpasswordencryptor.h"
#include "backend.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createDB()
{
    dbManager db("sample1.db");

}

void MainWindow::createTable()
{

    dbManager db("books.db");
    // This calls the db method and uses its string output as the message on the status bar, a default element on a starting mainwindow.ui
    ui->statusbar->showMessage(QString::fromStdString(db.createDB("books.db")));
}

void MainWindow::readTable()
{

    dbManager db("books.db");
    QVector<QVariant> ISBNs = db.readDB("books.db");


    for (unsigned short index = 0; index < ISBNs.size(); index++)
    {
        ui->textEditLarge->append(ISBNs[index].toString());

    }



}

void MainWindow::searchDB()
{
    dbManager db("bookstoreInventory.db");
    QVector<QVector<QVariant>> searchResults = db.searchDB("bookstoreInventory.db", ui->lineEditSearchDB->text());


    ui->textEditLarge->append(&"Number of Results: " [ searchResults.size() ]);
    for (unsigned short index = 0; index < searchResults.size(); index++)
    {
        for (unsigned short innerIndex = 0; innerIndex < searchResults.at(index).size(); innerIndex++)
        {
            ui->textEditLarge->append(searchResults[index][innerIndex].toString());

        }
        ui->textEditLarge->append("\n");

    }



}

void MainWindow::logIn()
{
    QString username = ui->lineEditUsername->text();
    QString password = QString::fromStdString( hash_password( ui->lineEditPassword->text().toStdString() ) );

    QVector<bool> loginStatus = attemptLogin(username, password);

    if (loginStatus.size() == NULL)
    {

        ui->statusbar->showMessage("Login Failed! No UserPass pairs of given inputs.");

    }
    else if (loginStatus.size() == 1)
    {

        if (loginStatus[0])
        {
            ui->statusbar->showMessage("Login Successful! Admin Access Granted!");
        }
        else
        {
            ui->statusbar->showMessage("Login Successful!");
        }

    }
    else
    {

        ui->statusbar->showMessage("DB ERROR: Login Attempt Failed! More than 1 UserPass pairs found.");

    }

}




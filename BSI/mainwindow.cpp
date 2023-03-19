#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

void MainWindow::closeEvent(QCloseEvent *event)
{
    outputToLogFile("MainWindow::closeEvent(*event) Now attempting to Close Program...");
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Scroll Rack",
                                                                    tr("Are you sure?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes) {
            outputToLogFile("MainWindow::closeEvent(..) Closing the program has been cancelled.");
            event->ignore();
        } else {
            outputToLogFile("MainWindow::closeEvent(..) Now Closing Program via Close Event.\n");
            event->accept();
        }
}

void MainWindow::exitProgram()
{
    outputToLogFile("MainWindow::exitProgram() Closing Program via Exit Button.");
    close();
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

// If we actually use this function for getting our number of books, then rename this function to something more appropreate.
void MainWindow::readTable()
{
    /*
    dbManager db("books.db");
    QVector<QVariant> ISBNs = db.readDB("books.db");


    for (unsigned short index = 0; index < ISBNs.size(); index++)
    {
        ui->textEditLarge->append(ISBNs[index].toString());

    }
    */

    // My recomendation for this is to make an infinite loop that calls db.getTotalNumBooks() every 6-12 seconds
    // which would basically update the status bar automatically in the background each time it gets called.
    // Can probably accomplish this using Streams as we learned from our Week 9 Lecture.
    dbManager db("bookstoreInventory.db");

    // Note that this does not update the status bar, it only gives the values to display within the statud bar.
    // The first number is the total number of records in the database, aka the number of unique books our bookstore carries.
    // The second number is the total sum of all of our books' QUANTITY_ON_HAND values, aka the total number of all of the book printings we currently have on stock.
    QVector<QVariant> numBooks = db.getTotalNumBooks();

}

void MainWindow::searchDB()
{
    dbManager db("bookstoreInventory.db");
    const int searchCategory = ui->comboBoxSearchBy->currentIndex();
    QVector<QVector<QVariant>> searchResults = db.searchDB("bookstoreInventory.db", ui->lineEditSearchDB->text(), searchCategory);

    //outputToLogFile("dbManager.searchDB");

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

    // We can probably get rid of the commented out lines that would use the status bar to display the logIn results,
    if (loginStatus.size() == NULL)
    {

        outputToLogFile("MainWindow::logIn() Login Failed! No UserPass pairs of given inputs.");
        //ui->statusbar->showMessage("Login Failed! No UserPass pairs of given inputs.");

    }
    else if (loginStatus.size() == 1)
    {

        if (loginStatus[0])
        {
            outputToLogFile("MainWindow::logIn() Login Successful! Admin Access Granted!");
            //ui->statusbar->showMessage("Login Successful! Admin Access Granted!");
        }
        else
        {
            outputToLogFile("MainWindow::logIn() Login Successful!");
            //ui->statusbar->showMessage("Login Successful!");
        }

    }
    else
    {

        outputToLogFile("MainWindow::logIn() DB ERROR: Login Attempt Failed! More than 1 UserPass pairs found.");
        //ui->statusbar->showMessage("DB ERROR: Login Attempt Failed! More than 1 UserPass pairs found.");

    }



}




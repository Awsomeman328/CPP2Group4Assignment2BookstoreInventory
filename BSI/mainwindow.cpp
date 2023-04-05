#include "mainwindow.h"
#include <./ui_mainwindow.h>
#include "dbmanager.h"
#include "book.h"
#include "hardwareinfo.h"
#include "notesdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the menu bar and menus
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("File");
    QMenu *editMenu = new QMenu("Edit");
    QMenu *helpMenu = new QMenu("Help");

    // Create the menu items and add them to the menus
    //QAction *newAction = new QAction("New", this);
    importAction = new QAction("Import", this);
    exportAction = new QAction("Export", this);
    QAction *exitAction = new QAction("Exit", this);
    QAction *cutAction = new QAction("Cut", this);
    QAction *copyAction = new QAction("Copy", this);
    QAction *pasteAction = new QAction("Paste", this);
    QAction *displayNotesAction = new QAction("Notes", this);
    QAction *aboutAction = new QAction("About", this);
    QAction *displayHardwareAction = new QAction("Hardware Information", this);

    // Disable the functionality meant for Admins only!
    importAction->setEnabled(false);
    exportAction->setEnabled(false);

    fileMenu->addAction(importAction);
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(displayNotesAction);
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(displayHardwareAction);

    // Add the menus to the menu bar
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(helpMenu);

    // Set the menu bar as the main window's menu bar
    setMenuBar(menuBar);

    // Connect the menu items to their respective functions
    connect(importAction, &QAction::triggered, this, &MainWindow::importCSV);
    connect(exportAction, &QAction::triggered, this, &MainWindow::exportCSV);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitProgram);
    connect(cutAction, &QAction::triggered, ui->textEditLarge, &QTextEdit::cut);
    connect(copyAction, &QAction::triggered, ui->textEditLarge, &QTextEdit::copy);
    connect(pasteAction, &QAction::triggered, ui->textEditLarge, &QTextEdit::paste);
    connect(displayNotesAction, &QAction::triggered, this, &MainWindow::showNotesDialog);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(displayHardwareAction, &QAction::triggered, this, &MainWindow::showHardwareDialog);


    // Create a label to display the number of books
    QLabel *statusLabel = new QLabel(this);

    // Get the total number of books from the database
    dbManager db("bookstoreInventory.db");
    QVector<QVariant> totalNumBooks = db.getTotalNumBooks();
    QString numBooks = totalNumBooks[0].toString();
    QString totalQuantity = totalNumBooks[1].toString();

    // Set the text of the status label to display the total number of books
    statusLabel->setText(QString("Total number of unique books: " + numBooks + " | Total quantity of books currently on hand: " + totalQuantity));

    // Add the label to the status bar
    statusBar()->addWidget(statusLabel);

    // Add the status bar to the main window
    setStatusBar(statusBar());
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::CompareBookByMSRP::operator()(const Book& b1, const Book& b2) const
{
    return b1.getMSRP() < b2.getMSRP();
}

void MainWindow::importCSV()
{
    outputToLogFile("MainWindow::importCSV() Now starting the attempt to import a .CSV file.");

    QDir currentDir = QDir::current();
    QString parentDir = currentDir.dirName(); // get the parent directory name
    QString defaultPath = currentDir.absolutePath() + "/../" + parentDir;

    outputToLogFile("MainWindow::importCSV() Opening up File Dialog Box.");
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), defaultPath, tr("CSV Files (*.csv);;All Files (*.*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            outputToLogFile("MainWindow::importCSV() Error: Could not open file.");
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        // Do something with the file
        outputToLogFile("MainWindow::importCSV() Sucessfully opened the file!");

        // Check that the .CSV file is formated correctly,
        // then validate that each row in the .CSV will create a valid Book object,
        // and put each row's data into either a container of valid books and all of the invalid data into a 2nd containter,
        // finally send both containers to the dbmanager to be inserted into their respective tables.

        outputToLogFile("MainWindow::importCSV() Now closing the .CSV file.");
        file.close();
    }
    else
    {
        outputToLogFile("MainWindow::importCSV() Warning: Given File name was empty.");
    }

}

void MainWindow::exportCSV()
{
    for (int i = 0; i < bookList.size(); ++i) {
        // Do stuff, ...
    }
}

void MainWindow::showNotesDialog()
{
    NotesDialog notesDialog;
    notesDialog.exec();
}

void MainWindow::showAboutDialog()
{
    QMessageBox::about(this, "About",
        "This is a demo Bookstore Inventory Database Manager Application written by "
        "three college students: Michael Dolan, Christopher Rodela, and Jacob Wiles."
        "\n\n"
        "Everything in this application is for edjucational use and purposes only. "
        "If you have somehow paid ACTUAL money for this, you have been scammed. "
        "\n\n"
        "\"Scroll Rack\" illustration used for the splash screen was illustrated by "
        "Heather Hudson and is protected under Copyright for both her and for the  "
        "company \"Wizards of the Coast\" and the \"Magic: the Gathering\" brand.");
}

void MainWindow::showHardwareDialog()
{
    QList<QScreen*> screens = QGuiApplication::screens();
    hardwareInfo hardwareBox;
    //QMessageBox hardwareBox;
    //hardwareBox.setWindowTitle("HardwareInfo");
    //hardwareBox.setText("Placeholder Text for when Chris gets the hardware info");
    if (screens.size() > 1)
    {
        // Second screen is available
        QRect screenGeometry = screens.at(1)->geometry();
        hardwareBox.move(screenGeometry.center() - hardwareBox.rect().center());
    }
    int result = hardwareBox.exec(); // Was .exec() before being turned into a MainWindow Child Class
}

void MainWindow::showBookErrorDialog()
{
    QMessageBox::about(this, "Error", "Invalid book, please try again.");
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

void MainWindow::addBookToDB()
{
    Book newBook(
                ui->lineEditISBN->text().toStdString(),
                ui->lineEditTITLE->text().toStdString(),
                ui->lineEditAUTHOR->text().toStdString(),
                ui->lineEditYEAR->text().toInt(),
                ui->lineEditPUBLISHER->text().toStdString(),
                ui->lineEditDESC->text().toStdString(),
                ui->lineEditGENRE->text().toStdString(),
                ui->lineEditMSRP->text().toDouble(),
                ui->lineEditQUANTITY->text().toInt());

    if (newBook.getIsValid())
        {
            dbManager db("bookstoreInventory.db");
            db.addBookRecordToDatabase(newBook);
        }
        else
            showBookErrorDialog();
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

    // Set Admin features to false just in case they were enabled by a previous admin login
    toggleAdminFeatures(false);

    if (loginStatus.size() == NULL)
    {

        outputToLogFile("MainWindow::logIn() Login Failed! No UserPass pairs of given inputs.");

    }
    else if (loginStatus.size() == 1)
    {

        if (loginStatus[0])
        {
            outputToLogFile("MainWindow::logIn() Login Successful! Admin Access Granted!");
            toggleAdminFeatures(true);
        }
        else
        {
            outputToLogFile("MainWindow::logIn() Login Successful!");
        }

    }
    else
    {

        outputToLogFile("MainWindow::logIn() DB ERROR: Login Attempt Failed! More than 1 UserPass pairs found.");

    }



}

void MainWindow::toggleAdminFeatures(bool isEnabled)
{
    ui->tabAdminMenu->setEnabled(isEnabled);
    importAction->setEnabled(isEnabled);
    exportAction->setEnabled(isEnabled);
}

void MainWindow::searchBookToShoppingList()
{
    dbManager db("bookstoreInventory.db");
    const int searchCategory = ui->comboBoxShoppingListAddBy->currentIndex();
    QVector<QVector<QVariant>> searchResults = db.searchDB("bookstoreInventory.db", ui->lineEditSearchDBAddShoppingList->text(), searchCategory);

    //outputToLogFile("dbManager.searchDB");

    if (searchResults.size() == 1)
    {
        string ISBN = searchResults[0][0].toString().toStdString();
        string Title = searchResults[0][1].toString().toStdString();
        string Author = searchResults[0][2].toString().toStdString();
        unsigned int Year = searchResults[0][3].toInt();
        string Publisher = searchResults[0][4].toString().toStdString();
        string Description = searchResults[0][5].toString().toStdString();
        string Genre = searchResults[0][6].toString().toStdString();
        double MSRP = searchResults[0][7].toDouble();
        unsigned int Quantity = searchResults[0][8].toUInt();

        Book newBook = *new Book(ISBN, Title, Author, Year, Publisher,
                                 Description, Genre, MSRP, Quantity);

        if (newBook.getIsValid())
        {
            shoppingList.insert(newBook);
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("Book Added");
        }
        else
        {
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("Invalid Book, Book not added");
        }

    }
    else
    {
        // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
        ui->textEditLarge->append("Invalid search term");
    }

    ui->textEditLarge->append("\n");
}

void MainWindow::searchBookToBookList()
{
    dbManager db("bookstoreInventory.db");
    const int searchCategory = ui->comboBoxBookListAddBy->currentIndex();
    QVector<QVector<QVariant>> searchResults = db.searchDB("bookstoreInventory.db", ui->lineEditSearchDBAddBookList->text(), searchCategory);

    //outputToLogFile("dbManager.searchDB");

    if (searchResults.size() == 1)
    {
        string ISBN = searchResults[0][0].toString().toStdString();
        string Title = searchResults[0][1].toString().toStdString();
        string Author = searchResults[0][2].toString().toStdString();
        unsigned int Year = searchResults[0][3].toInt();
        string Publisher = searchResults[0][4].toString().toStdString();
        string Description = searchResults[0][5].toString().toStdString();
        string Genre = searchResults[0][6].toString().toStdString();
        double MSRP = searchResults[0][7].toDouble();
        unsigned int Quantity = searchResults[0][8].toUInt();

        Book newBook = *new Book(ISBN, Title, Author, Year, Publisher,
                                 Description, Genre, MSRP, Quantity);

        if (newBook.getIsValid())
        {
            bookList.push_back(newBook);
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("Book Added");
        }
        else
        {
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("Invalid Book, Book not added");
        }

    }
    else
    {
        // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
        ui->textEditLarge->append("Invalid search term");
    }

    ui->textEditLarge->append("\n");
}

void MainWindow::displayShoppingList()
{
    ui->textEditLarge->append(&"Number of Results: " [ shoppingList.size() ]);

    multiset<Book, CompareBookByMSRP>::iterator shoppingListIterator = shoppingList.begin();
    while (shoppingListIterator != shoppingList.end())
    {
        ui->textEditLarge->append(QString::fromStdString(shoppingListIterator->getISBN()));
        ui->textEditLarge->append(QString::fromStdString(shoppingListIterator->getTitle()));
        ui->textEditLarge->append(QString::fromStdString(shoppingListIterator->getAuthor()));
        ui->textEditLarge->append(QString::number(shoppingListIterator->getYear()));
        ui->textEditLarge->append(QString::fromStdString(shoppingListIterator->getPublisher()));
        ui->textEditLarge->append(QString::fromStdString(shoppingListIterator->getDescription()));
        ui->textEditLarge->append(QString::fromStdString(shoppingListIterator->getGenre()));
        ui->textEditLarge->append(QString::number(shoppingListIterator->getMSRP()));
        ui->textEditLarge->append(QString::number(shoppingListIterator->getQuantity()));
        ui->textEditLarge->append("\n");

        shoppingListIterator++;
    }
}

void MainWindow::purchaseShoppingList()
{

}

void MainWindow::displayBookList()
{
    ui->textEditLarge->append(&"Number of Results: " [ shoppingList.size() ]);

    for (int i = 0; i < bookList.size(); ++i)
    {
        ui->textEditLarge->append(QString::fromStdString(bookList[i].getISBN()));
        ui->textEditLarge->append(QString::fromStdString(bookList[i].getTitle()));
        ui->textEditLarge->append(QString::fromStdString(bookList[i].getAuthor()));
        ui->textEditLarge->append(QString::number(bookList[i].getYear()));
        ui->textEditLarge->append(QString::fromStdString(bookList[i].getPublisher()));
        ui->textEditLarge->append(QString::fromStdString(bookList[i].getDescription()));
        ui->textEditLarge->append(QString::fromStdString(bookList[i].getGenre()));
        ui->textEditLarge->append(QString::number(bookList[i].getMSRP()));
        ui->textEditLarge->append(QString::number(bookList[i].getQuantity()));
        ui->textEditLarge->append("\n");
    }
}

void MainWindow::addNewUser()
{

}

void MainWindow::changeUsersPassword()
{

}




#include "mainwindow.h"
#include <./ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loginDialog *login = new loginDialog;
    login->setWindowFlags(Qt::WindowStaysOnTopHint);
    QRect primaryGeometry = QGuiApplication::primaryScreen()->geometry();
    login->move(primaryGeometry.center() - login->rect().center());

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
    QAction *lowStockAction = new QAction("Low Stock", this);

    // Disable the functionality meant for Admins only!
    importAction->setEnabled(false);
    exportAction->setEnabled(false);

    fileMenu->addAction(importAction);
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    fileMenu->addAction(lowStockAction);
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
    connect(login, SIGNAL(loginClicked()), this, SLOT(enableWindow()));
    connect(login, SIGNAL(userIsAdmin()), this, SLOT(enableAdmin()));
    connect(lowStockAction, &QAction::triggered, this, &MainWindow::searchLowStockBooks);


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

    this->setEnabled(false);
    // Start Login Process
    int result = login->exec();
    if (result == QDialog::Accepted) {
        // Authentication successful - proceed to main window!
        this->setEnabled(true);
    } else {
        // User cancelled login or authentication failed
        close();
    }
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
        tr("Open & Import File"), defaultPath, tr("CSV Files (*.csv);;All Files (*.*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            outputToLogFile("MainWindow::importCSV() Error: Could not open file.");
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        // Do something with the file
        outputToLogFile("MainWindow::importCSV() Sucessfully opened the file!");

        QTextStream in(&file);

        // Check that the .CSV file's top row (or its header row) is formated correctly,
        QStringList headers = in.readLine().split(","); // read the first line and split by commas to get the headers
        if (headers.at(0) != "ISBN" || headers.at(1) != "Book-Title" || headers.at(2) != "Book-Author" ||
            headers.at(3) != "Year-Of-Publication" || headers.at(4) != "Publisher" || headers.at(5) != "Description" ||
            headers.at(6) != "Genre" || headers.at(7) != "MSRP" || headers.at(8) != "Quantity-On-Hand")

        {
            outputToLogFile("MainWindow::importCSV() Error: Selected file's Header Row is not properly formated.");
            QMessageBox::critical(this, tr("Error"), tr("Selected file's Header Row is not properly formated."));
            file.close();
            return;
        }

        // then validate that each row in the .CSV will create a valid Book object,
        // and put each row's data into either a container of valid books and all of the invalid data into a 2nd containter,
        QVector<Book> importList;
        QVector<QString> invalidImportList;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() != headers.size()) {
                outputToLogFile("MainWindow::importCSV() Error: Invalid row in CSV file. [Invalid Column Count]");
                // handle invalid row
                invalidImportList.push_back(line);
            }
            else if (fields.at(0).isEmpty() || fields.at(1).isEmpty() || fields.at(2).isEmpty() ||
                     fields.at(3).isEmpty() || fields.at(4).isEmpty() || fields.at(5).isEmpty() ||
                     fields.at(6).isEmpty() || fields.at(7).isEmpty() || fields.at(8).isEmpty())
            {
                outputToLogFile("MainWindow::importCSV() Error: Invalid row in CSV file. [Empty Row Value]");
                // handle invalid row
                invalidImportList.push_back(line);
            }
            else
            {
                Book book(fields.at(0).toStdString(), fields.at(1).toStdString(), fields.at(2).toStdString(),
                          fields.at(3).toInt(), fields.at(4).toStdString(), fields.at(5).toStdString(),
                          fields.at(6).toStdString(), fields.at(7).toDouble(), fields.at(8).toInt());

                if (book.getIsValid()) importList.push_back(book);
                else
                {
                    outputToLogFile("MainWindow::importCSV() Error: Invalid row in CSV file. [Invalid Row Value]");
                    // handle invalid row
                    invalidImportList.push_back(line);
                }
            }
        }

        // finally send both containers to the dbmanager to be inserted into their respective tables.
        dbManager db("bookstoreInventory.db");
        while (!importList.empty()) {
            db.addBookRecordToDatabase(importList.front());

            importList.pop_front();
        }
        while (!invalidImportList.empty()) {
            db.addInvalid_BookRecordToDatabase(invalidImportList.front());

            invalidImportList.pop_front();
        }

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
    QDir currentDir = QDir::current();
    QString parentDir = currentDir.dirName(); // get the parent directory name
    QString defaultPath = currentDir.absolutePath() + "/../" + parentDir;

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save & Export Book List to File"), defaultPath, tr("CSV File (*.csv)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            outputToLogFile("MainWindow::exportCSV() Error: Could not open file.");
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        outputToLogFile("MainWindow::exportCSV() Sucessfully opened the file!");

        QTextStream out(&file);
        // Write the header row
        out << "ISBN,Book-Title,Book-Author,Year-Of-Publication,Publisher,Description,Genre,MSRP,Quantity-On-Hand\n";

        // Write each row of data
        for (const auto& book : bookList) {
            // Do stuff, ...
            out << QString::fromStdString(book.getISBN()) << "," << QString::fromStdString(book.getTitle()) << ","
                << QString::fromStdString(book.getAuthor()) << "," << book.getYear() << ","
                << QString::fromStdString(book.getPublisher()) << "," << QString::fromStdString(book.getDescription()) << ","
                << QString::fromStdString(book.getGenre()) << "," << QString::number(book.getMSRP(), 'f', 2) << ","
                << book.getQuantity() << "\n";
        }

        bookList.clear();

        outputToLogFile("MainWindow::exportCSV() Now closing the .CSV file.");
        file.close();
    }
    else
    {
        outputToLogFile("MainWindow::exportCSV() Warning: Given File name was empty.");
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
        dbManager db("bookstoreInventory.db");
        while (!bookList.empty()) {
            db.addBookRecordToDatabase(bookList.front());

            bookList.pop_front();
        }

        outputToLogFile("MainWindow::closeEvent(..) Now Closing Program via Close Event.\n");
        event->accept();
    }

    outputToLogFile("MainWindow::closeEvent(..) Now Closing Program via Close Event.\n");
    event->accept();
}


void MainWindow::exitProgram()
{
    dbManager db("bookstoreInventory.db");
    while (!bookList.empty()) {
        db.addBookRecordToDatabase(bookList.front());

        bookList.pop_front();
    }

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
    if (ui->lineEditSearchDB->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Search Formatting Error"), tr("Search parameters must have at least 1 character"));
        return;
    }

    dbManager db("bookstoreInventory.db");
    const int searchCategory = ui->comboBoxSearchBy->currentIndex();
    QVector<QVector<QVariant>> searchResults = db.searchDB("bookstoreInventory.db", ui->lineEditSearchDB->text(), searchCategory);

    //outputToLogFile("dbManager.searchDB");

    int listSize = searchResults.size();
    QString message = QString("Display Search Results - Number of Results: %1").arg(listSize);
    ui->textEditLarge->append(message);

    for (unsigned short i = 0; i < searchResults.size(); i++)
    {
        ui->textEditLarge->append("Result #: \t" + searchResults[i][0].toString());

        ui->textEditLarge->append("ISBN: \t" + searchResults[i][1].toString());
        ui->textEditLarge->append("Title: \t" + searchResults[i][2].toString());
        ui->textEditLarge->append("Author: \t" + searchResults[i][3].toString());
        ui->textEditLarge->append("Year: \t" + searchResults[i][4].toString());
        ui->textEditLarge->append("Publisher: \t" + searchResults[i][5].toString());
        ui->textEditLarge->append("Description: \t" + searchResults[i][6].toString());
        ui->textEditLarge->append("Genre: \t" + searchResults[i][7].toString());
        ui->textEditLarge->append("MSRP: \t$" + searchResults[i][8].toString());
        ui->textEditLarge->append("Quantity: \t" + searchResults[i][9].toString());

        ui->textEditLarge->append("\n");

    }

}

void MainWindow::logIn()
{
    /*
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


    */
}

void MainWindow::toggleAdminFeatures(bool isEnabled)
{
    ui->tabAdminMenu->setEnabled(isEnabled);
    importAction->setEnabled(isEnabled);
    exportAction->setEnabled(isEnabled);
}

void MainWindow::searchBookToShoppingList()
{
    // check that ui->lineEditShoppingListAddAmount->text() is a valid positive number (greater than 0)

    dbManager db("bookstoreInventory.db");
    const int searchCategory = ui->comboBoxShoppingListAddBy->currentIndex();
    QVector<QVector<QVariant>> searchResults = db.searchDB("bookstoreInventory.db", ui->lineEditSearchDBAddShoppingList->text(), searchCategory);

    //outputToLogFile("dbManager.searchDB");

    if (searchResults.size() == 1)
    {
        // check that ui->lineEditShoppingListAddAmount->text() is a number that is less than the searched book's Quantity On Hand Amount.
        // if we do not have enough on hand, then throw an error message box

        string ISBN = searchResults[0][1].toString().toStdString();
        string Title = searchResults[0][2].toString().toStdString();
        string Author = searchResults[0][3].toString().toStdString();
        unsigned int Year = searchResults[0][4].toInt();
        string Publisher = searchResults[0][5].toString().toStdString();
        string Description = searchResults[0][6].toString().toStdString();
        string Genre = searchResults[0][7].toString().toStdString();
        double MSRP = searchResults[0][8].toDouble();
        unsigned int Quantity = searchResults[0][9].toUInt(); // replace with ui->lineEditShoppingListAddAmount->text()

        Book newBook = *new Book(ISBN, Title, Author, Year, Publisher,
                                 Description, Genre, MSRP, Quantity);

        if (newBook.getIsValid())
        {
            shoppingList.insert(newBook);
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("Book Added");
            outputToLogFile("MainWindow::searchBookToShoppingList() Found Book is Valid! Adding the valid result into the Shopping List.");
        }
        else
        {
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("Invalid Book, Book not added");
            outputToLogFile("MainWindow::searchBookToShoppingList() [Error]: Found Book is Invalid! ...");
        }

    }
    else
    {
        // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
        ui->textEditLarge->append("Invalid search term");
        outputToLogFile("MainWindow::searchBookToShoppingList() [Error]: Invalid search Term! Search returned with either 0 or 2+ number of results.");
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
        string ISBN = searchResults[0][1].toString().toStdString();
        string Title = searchResults[0][2].toString().toStdString();
        string Author = searchResults[0][3].toString().toStdString();
        unsigned int Year = searchResults[0][4].toInt();
        string Publisher = searchResults[0][5].toString().toStdString();
        string Description = searchResults[0][6].toString().toStdString();
        string Genre = searchResults[0][7].toString().toStdString();
        double MSRP = searchResults[0][8].toDouble();
        unsigned int Quantity = searchResults[0][9].toUInt();

        Book newBook = *new Book(ISBN, Title, Author, Year, Publisher,
                                 Description, Genre, MSRP, Quantity);

        if (newBook.getIsValid())
        {
            if (db.removeBookRecordFromDatabase(newBook))
            {
                bookList.push_back(newBook);

                // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
                ui->textEditLarge->append("Book Added to List and Removed from Database.");
            }
            else
            {
                // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
                ui->textEditLarge->append("Book is valid, but couldn't be Removed from Database.");
            }

        }
        else
        {
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("Invalid Book, Book not added to list");
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
    int listSize = shoppingList.size();
    QString message = QString("Display Shopping List - Number of Results: %1").arg(listSize);
    ui->textEditLarge->append(message);

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
    QString shopperEmail = ui->lineEditCurrentShopper->text();
    if (shopperEmail.isEmpty())
    {
        ui->textEditLarge->append("Empty Email! Please enter a valid shopper email!\n");
        return;
    }

    dbManager db("bookstoreInventory.db");

    // First check for a valid shopper. If not valid, then give a warning.
    if (!db.checkForValidShopper(shopperEmail))
    {
        ui->textEditLarge->append("Invalid Shopper! Please enter a valid shopper!\n");
        return;
    }

    ui->textEditLarge->append("Starting Buying Process");

    // For each book in the Shopping List,
    // Try to decrease that book's amount by 1.
    // If you can, then increase the Shopper's total spent by that book's MSRP.
    // Then remove all of the books from the list
    multiset<Book, bool(*)(const Book&, const Book&)>::iterator shoppingListIterator = shoppingList.begin();
    while (shoppingListIterator != shoppingList.end())
    {
        // Do stuff
        if (db.adjustBookQuantityInInventory(shoppingListIterator->getISBN(), -1))
        {
            if (db.increaseShopperTotalSpent(shopperEmail, shoppingListIterator->getMSRP()))
            {
                ui->textEditLarge->append("Sucessfully Bought the book: " + QString::fromStdString(shoppingListIterator->getTitle()));
            }
            else
            {
                db.adjustBookQuantityInInventory(shoppingListIterator->getISBN(), 1);
            }
        }
        shoppingListIterator++;
    }

    shoppingList.clear();
}

void MainWindow::displayBookList()
{
    int listSize = bookList.size();
    QString message = QString("Display Book List - Number of Results: %1").arg(listSize);
    ui->textEditLarge->append(message);

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
    QString username = ui->lineEditNewUserUsername->text();
    QString password = QString::fromStdString( hash_password( ui->lineEditNewUserPassword->text().toStdString() ) );
    bool isAdmin = ui->checkBoxIsAdmin->isChecked();

    dbManager db("bookstoreInventory.db");

    if (db.addNewUser(username, password, isAdmin))
    {
        ui->textEditLarge->append("New user added successfully!");
    }
    else
    {
        ui->textEditLarge->append("Failed to add new user.");
    }

    /* We are not using .CSV files to store our user Info in anymore!
    // Open the users.csv file for writing in append mode
    QFile file("users.csv");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        // Write the new user's details to the file in CSV format
        out << username << "," << password << "\n";
        file.close();
        outputToLogFile("MainWindow::addNewUser() New user added successfully!");
    }
    else {
        outputToLogFile("MainWindow::addNewUser() Error: Failed to open users.csv for writing!");
    }
    */
}

void MainWindow::changeUsersPassword()
{
    QString username = ui->lineEditChangeUserUsername->text();
    QString password = QString::fromStdString( hash_password( ui->lineEditChangeUserPassword->text().toStdString() ) );

    dbManager db("bookstoreInventory.db");

    if (db.changeUserPassword(username, password))
    {
        ui->textEditLarge->append("User password changed successfully!");
    }
    else
    {
        ui->textEditLarge->append("Failed to change user password.");
    }

    /* We are not using .CSV files to store our user Info in anymore!
    // Open the users.csv file for reading and writing
    QFile file("users.csv");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        outputToLogFile("Error: Failed to open users.csv for reading and writing!");
        return;
    }

    // Read in all the existing data from the file
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine();
        lines.append(line);
    }

    // Close the file to truncate it
    file.close();

    // Reopen the file in write mode to overwrite with updated data
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        outputToLogFile("Error: Failed to open users.csv for writing!");
        return;
    }

    // Write the updated data to the file
    QTextStream out(&file);
    bool updated = false;
    for (const QString& line : lines) {
        QStringList parts = line.split(",");
        if (parts.length() == 2 && parts[0] == username) {
            out << username << "," << password << "\n";
            updated = true;
        } else {
            out << line << "\n";
        }
    }
    */
    /*
    if (updated) {
        outputToLogFile("MainWindow::changeUsersPassword() Password for user " + username + " changed successfully!");
    } else {
        outputToLogFile("MainWindow::changeUsersPassword() Error: User " + username + " not found!");
    }
*/

    //file.close();
}





void MainWindow::checkValidBookToUpdate()
{
    dbManager db("bookstoreInventory.db");
    const int searchCategory = ui->comboBoxUpdateBook->currentIndex();
    QVector<QVector<QVariant>> searchResults = db.searchDB("bookstoreInventory.db", ui->lineEditSearchDBUpdateBook->text(), searchCategory);

    //outputToLogFile("dbManager.searchDB");

    if (searchResults.size() == 1)
    {
        string ISBN = searchResults[0][1].toString().toStdString();
        string Title = searchResults[0][2].toString().toStdString();
        string Author = searchResults[0][3].toString().toStdString();
        unsigned int Year = searchResults[0][4].toInt();
        string Publisher = searchResults[0][5].toString().toStdString();
        string Description = searchResults[0][6].toString().toStdString();
        string Genre = searchResults[0][7].toString().toStdString();
        double MSRP = searchResults[0][8].toDouble();
        unsigned int Quantity = searchResults[0][9].toUInt();

        Book newBook = *new Book(ISBN, Title, Author, Year, Publisher,
                                 Description, Genre, MSRP, Quantity);

        if (newBook.getIsValid())
        {
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("A valid Book was found in the Database!");

            ui->textEditLarge->append("ISBN: \t" + searchResults[0][1].toString());
            ui->textEditLarge->append("Title: \t" + searchResults[0][2].toString());
            ui->textEditLarge->append("Author: \t" + searchResults[0][3].toString());
            ui->textEditLarge->append("Year: \t" + searchResults[0][4].toString());
            ui->textEditLarge->append("Publisher: \t" + searchResults[0][5].toString());
            ui->textEditLarge->append("Description: \t" + searchResults[0][6].toString());
            ui->textEditLarge->append("Genre: \t" + searchResults[0][7].toString());
            ui->textEditLarge->append("MSRP: \t$" + searchResults[0][8].toString());
            ui->textEditLarge->append("Quantity: \t" + searchResults[0][9].toString());

        }
        else
        {
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("Invalid Book! Book found in the Database, but is not valid!");
        }

    }
    else
    {
        // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
        ui->textEditLarge->append("Invalid search term! Either 0 or 2+ results were found from your search.");
    }

    ui->textEditLarge->append("\n");
}

void MainWindow::updateBook()
{
    dbManager db("bookstoreInventory.db");
    const int searchCategory = ui->comboBoxUpdateBook->currentIndex();
    QVector<QVector<QVariant>> searchResults = db.searchDB("bookstoreInventory.db", ui->lineEditSearchDBUpdateBook->text(), searchCategory);

    //outputToLogFile("dbManager.searchDB");

    if (searchResults.size() == 1)
    {
        string ISBN = searchResults[0][1].toString().toStdString();
        string Title = searchResults[0][2].toString().toStdString();
        string Author = searchResults[0][3].toString().toStdString();
        unsigned int Year = searchResults[0][4].toInt();
        string Publisher = searchResults[0][5].toString().toStdString();
        string Description = searchResults[0][6].toString().toStdString();
        string Genre = searchResults[0][7].toString().toStdString();
        double MSRP = searchResults[0][8].toDouble();
        unsigned int Quantity = searchResults[0][9].toUInt();

        Book oldBook = *new Book(ISBN, Title, Author, Year, Publisher,
                                 Description, Genre, MSRP, Quantity);

        if (!ui->lineEditISBNUpdate->text().isEmpty() && oldBook.validateISBN(ui->lineEditISBNUpdate->text().toStdString()))
        {
            ISBN = ui->lineEditISBNUpdate->text().toStdString();
        }
        if (!ui->lineEditTITLEUpdate->text().isEmpty() && oldBook.validateTitle(ui->lineEditTITLEUpdate->text().toStdString()))
        {
            Title = ui->lineEditTITLEUpdate->text().toStdString();
        }
        if (!ui->lineEditAUTHORUpdate->text().isEmpty() && oldBook.validateAuthor(ui->lineEditAUTHORUpdate->text().toStdString()))
        {
            Author = ui->lineEditAUTHORUpdate->text().toStdString();
        }
        if (!ui->lineEditYEARUpdate->text().isEmpty() && oldBook.validatePubYear(ui->lineEditYEARUpdate->text().toUInt()))
        {
            Year = ui->lineEditYEARUpdate->text().toUInt();
        }
        if (!ui->lineEditPUBLISHERUpdate->text().isEmpty() && oldBook.validatePublisher(ui->lineEditPUBLISHERUpdate->text().toStdString()))
        {
            Publisher = ui->lineEditPUBLISHERUpdate->text().toStdString();
        }
        if (!ui->lineEditDESCUpdate->text().isEmpty() && oldBook.validateDescription(ui->lineEditDESCUpdate->text().toStdString()))
        {
            Description = ui->lineEditDESCUpdate->text().toStdString();
        }
        if (!ui->lineEditGENREUpdate->text().isEmpty() && oldBook.validateGenre(ui->lineEditGENREUpdate->text().toStdString()))
        {
            Genre = ui->lineEditGENREUpdate->text().toStdString();
        }
        if (!ui->lineEditMSRPUpdate->text().isEmpty() && oldBook.validateMSRP(ui->lineEditMSRPUpdate->text().toDouble()))
        {
            MSRP = ui->lineEditMSRPUpdate->text().toDouble();
        }
        if (!ui->lineEditQUANTITYUpdate->text().isEmpty() && oldBook.validateQuantity(ui->lineEditQUANTITYUpdate->text().toUInt()))
        {
            Quantity = ui->lineEditQUANTITYUpdate->text().toUInt();
        }

        Book newBook = *new Book(ISBN, Title, Author, Year, Publisher,
                                 Description, Genre, MSRP, Quantity);

        if (newBook.getIsValid())
        {
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("A new valid book can be created! Time to update!");

            // Update all of the fields that are different. If ISBN is different, update that last.
            // For text/string values, surround the new value in 'single quotes'. For numbers do not.
            if (oldBook.getTitle() != newBook.getTitle())
            {
                if (db.updateBookRecordColumnValue(oldBook.getISBN(), "TITLE", newBook.getTitle()))
                {
                    ui->textEditLarge->append("Title Updated!");
                }
            }
            if (oldBook.getAuthor() != newBook.getAuthor())
            {
                if (db.updateBookRecordColumnValue(oldBook.getISBN(), "AUTHOR", newBook.getAuthor()))
                {
                    ui->textEditLarge->append("Author Updated!");
                }
            }
            if (oldBook.getYear() != newBook.getYear())
            {
                if (db.updateBookRecordColumnValue(oldBook.getISBN(), "PUBLICATION_YEAR", QString::number(newBook.getYear()).toStdString()))
                {
                    ui->textEditLarge->append("Publication Year Updated!");
                }
            }
            if (oldBook.getPublisher() != newBook.getPublisher())
            {
                if (db.updateBookRecordColumnValue(oldBook.getISBN(), "PUBLISHER", newBook.getPublisher()))
                {
                    ui->textEditLarge->append("Publisher Updated!");
                }
            }
            if (oldBook.getDescription() != newBook.getDescription())
            {
                if (db.updateBookRecordColumnValue(oldBook.getISBN(), "DESCRIPTION", newBook.getDescription()))
                {
                    ui->textEditLarge->append("Description Updated!");
                }
            }
            if (oldBook.getGenre() != newBook.getGenre())
            {
                if (db.updateBookRecordColumnValue(oldBook.getISBN(), "GENRE", newBook.getGenre()))
                {
                    ui->textEditLarge->append("Genre Updated!");
                }
            }
            if (oldBook.getMSRP() != newBook.getMSRP())
            {
                if (db.updateBookRecordColumnValue(oldBook.getISBN(), "MSRP", QString::number(newBook.getMSRP()).toStdString()))
                {
                    ui->textEditLarge->append("MSRP Updated!");
                }
            }
            if (oldBook.getQuantity() != newBook.getQuantity())
            {
                if (db.updateBookRecordColumnValue(oldBook.getISBN(), "QUANTITY_ON_HAND", QString::number(newBook.getQuantity()).toStdString()))
                {
                    ui->textEditLarge->append("Quantity On Hand Updated!");
                }
            }
            if (oldBook.getISBN() != newBook.getISBN())
            {
                if (db.updateBookRecordColumnValue(oldBook.getISBN(), "ISBN", newBook.getISBN()))
                {
                    ui->textEditLarge->append("ISBN Updated!");
                }
            }

            ui->textEditLarge->append("New Book Updated! Here are the results:");

            QVector<QVector<QVariant>> newResults = db.searchDB("bookstoreInventory.db", QString::fromStdString(newBook.getISBN()), 0);

            ui->textEditLarge->append("ISBN: \t" + newResults[0][1].toString());
            ui->textEditLarge->append("Title: \t" + newResults[0][2].toString());
            ui->textEditLarge->append("Author: \t" + newResults[0][3].toString());
            ui->textEditLarge->append("Year: \t" + newResults[0][4].toString());
            ui->textEditLarge->append("Publisher: \t" + newResults[0][5].toString());
            ui->textEditLarge->append("Description: \t" + newResults[0][6].toString());
            ui->textEditLarge->append("Genre: \t" + newResults[0][7].toString());
            ui->textEditLarge->append("MSRP: \t$" + newResults[0][8].toString());
            ui->textEditLarge->append("Quantity: \t" + newResults[0][9].toString());

        }
        else
        {
            // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
            ui->textEditLarge->append("Invalid Book! Book found in the Database, but your updates are not valid!");
        }

    }
    else
    {
        // Since this is a DB operation, this should probably be a QMessageBox Pop-Up, ...
        ui->textEditLarge->append("Invalid search term! Either 0 or 2+ results were found from your search.");
    }

    ui->textEditLarge->append("\n");
}


void MainWindow::searchLowStockBooks()
{
    dbManager db("bookstoreInventory.db");

    QVector<QVector<QVariant>> searchResults = db.getLowStockedBooks();

    // Output the low stock books to user
    ui->textEditLarge->append("Low Stocked Books (Under 4 Copies):");

    for (unsigned short i = 0; i < searchResults.size(); i++)
    {
        ui->textEditLarge->append("Result #: \t" + searchResults[i][0].toString());

        ui->textEditLarge->append("ISBN: \t" + searchResults[i][1].toString());
        ui->textEditLarge->append("Title: \t" + searchResults[i][2].toString());
        ui->textEditLarge->append("Author: \t" + searchResults[i][3].toString());
        ui->textEditLarge->append("Year: \t" + searchResults[i][4].toString());
        ui->textEditLarge->append("Publisher: \t" + searchResults[i][5].toString());
        ui->textEditLarge->append("Description: \t" + searchResults[i][6].toString());
        ui->textEditLarge->append("Genre: \t" + searchResults[i][7].toString());
        ui->textEditLarge->append("MSRP: \t$" + searchResults[i][8].toString());
        ui->textEditLarge->append("Quantity: \t" + searchResults[i][9].toString());

        ui->textEditLarge->append("\n");

    }

    /*
    // Create the low stock books plain text edit and set its properties
    if (!lowStockBooks) {
        lowStockBooks = new QPlainTextEdit(this);
        lowStockBooks->setWindowTitle("Low Stock Books");
        lowStockBooks->resize(400, 300);
    }

    lowStockBooks->show();
    */
}

void MainWindow::enableWindow()
{
    this->setEnabled(true);
}



void MainWindow::enableAdmin()
{
    toggleAdminFeatures(true);
}

void MainWindow::addShopper()
{
    dbManager db("bookstoreInventory.db");
    QString firstname = ui->lineEditShopperFirstName->text();
    QString lastname = ui->lineEditShopperLastName->text();
    QString email = ui->lineEditShopperEmail->text();

    if (!firstname.isEmpty() && !lastname.isEmpty() && !email.isEmpty())
    {
        db.addShopperToDatabase(firstname, lastname, email);
        ui->textEditLarge->append("Shopper " + firstname + " " + lastname + " added to database.");
    }

    else
    {
        QMessageBox::warning(this, "Shopper", "Must fill out all fields");
    }
}

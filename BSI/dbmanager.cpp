#include "dbmanager.h"
#include <iostream>

dbManager::dbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE"); // The "QSQLITE" arg is the engine we use to connect to our database
    m_db.setDatabaseName(path); // This is both the path to and the name of the database we want to open

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok";
        std::cout << "Success";
    }

    m_db.close();
}

std::string dbManager::createDB(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    QSqlQuery CreateQuery;
    bool success = false;

    if (!m_db.open())
    {
       qDebug() << "Error: connection with database failed";
    }
    else
    {
       qDebug() << "Database: connection ok";
       std::cout << "Success";
    }

    // Technically, the rest of this SHOULD be within the .open() if statement above. Its fine for now, but should probably make this change.
    CreateQuery.prepare("CREATE TABLE BOOK(ISBN INTEGER PRIMARY KEY UNIQUE, TITLE STRING, PUBLISHED INTEGER)");
    if(CreateQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "create table error:"
                 << CreateQuery.lastError();
    }

    QSqlQuery InsertQuery;
    InsertQuery.prepare("INSERT INTO BOOK (ISBN, TITLE, PUBLISHED) VALUES (:ISBN, 'Good Morning', 2023)");
    InsertQuery.bindValue(":ISBN", 22222222);
    if(InsertQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "Insert Into error:"
                 << InsertQuery.lastError();
    }


    m_db.close();

    if (success == true)
        return "Created table";
    else
        return "Failed";

}

QVector<QVariant> dbManager::readDB(const QString& path)
{
    QVector<QVariant> ISBN;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
       qDebug() << "Error: connection with database failed";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }

    QSqlQuery query("SELECT * FROM BOOK");
    int idISBN = query.record().indexOf("ISBN");
    int idPublish = query.record().indexOf("PUBLISHED");

    while (query.next())
    {

        ISBN.push_back( query.value(1));
        ISBN.push_back( query.value(idISBN));
        ISBN.push_back( query.value(idPublish));

    }

    m_db.close();

    return ISBN;

}

QVector<QVector<QVariant>> dbManager::searchDB(const QString& path, const QString searchTerm, const int searchCategory)
{
    QVector<QVector<QVariant>> searchResults;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        outputToLogFile("dbManager::searchDB(" + path.toStdString() + ", .., ..) Error: connection with database failed");
        //qDebug() << "dbManager::searchDB(" + path + ", .., ..) Error: connection with database failed";
    }
    else
    {
        outputToLogFile("dbManager::searchDB(" + path.toStdString() + ", .., ..) Database: connection ok");
        //qDebug() << "Database: connection ok";

        outputToLogFile("dbManager::searchDB(.., " + searchTerm.toStdString() + ", " + to_string(searchCategory) + ") Database: connection ok");
        //qDebug() << "dbManager::searchDB(.., " + searchTerm + ", " + QString::fromStdString(to_string(searchCategory)) + ") Database: connection ok";

        QString queryString;

        switch (searchCategory) {
        case 0:
            queryString = "SELECT * FROM BOOKS WHERE ISBN LIKE '%" + searchTerm + "%';";
            break;
        case 1:
            queryString = "SELECT * FROM BOOKS WHERE TITLE LIKE '%" + searchTerm + "%';";
            break;
        case 2:
            queryString = "SELECT * FROM BOOKS WHERE AUTHOR LIKE '%" + searchTerm + "%';";
            break;
        case 3:
            queryString = "SELECT * FROM BOOKS WHERE PUBLICATION_YEAR=" + searchTerm + ";";
            break;
        case 4:
            queryString = "SELECT * FROM BOOKS WHERE PUBLISHER LIKE '%" + searchTerm + "%';";
            break;
        case 5:
            queryString = "SELECT * FROM BOOKS WHERE MSRP=" + searchTerm + ";";
            break;
        case 6:
            queryString = "SELECT * FROM BOOKS WHERE QUANTITY_ON_HAND=" + searchTerm + ";";
            break;
        default:
            queryString = "SELECT * FROM BOOKS WHERE TITLE LIKE '%" + searchTerm + "%';";
            break;
        }

        QSqlQuery query(queryString);
        int idISBN = query.record().indexOf("ISBN");
        int idTitle = query.record().indexOf("TITLE");
        int idAuthor = query.record().indexOf("AUTHOR");
        int idYear = query.record().indexOf("PUBLICATION_YEAR");
        int idPublisher = query.record().indexOf("PUBLISHER");
        int idDescription = query.record().indexOf("DESCRIPTION");
        int idGenre = query.record().indexOf("GENRE");
        int idMSRP = query.record().indexOf("MSRP");
        int idCurQuantity = query.record().indexOf("QUANTITY_ON_HAND");

        int numResults = 0;

        while (query.next())
        {

            if (numResults == 0)
            {
                outputToLogFile("dbManager::searchDB(.., .., ..) Database: found at least 1 result");
                //qDebug() << "dbManager::searchDB(.., .., ..) Database: found at least 1 result";
            }
            numResults++;

            QVector<QVariant> rowResult;
            rowResult.push_back( numResults );
            rowResult.push_back( query.value(idISBN) );
            rowResult.push_back( query.value(idTitle) );
            rowResult.push_back( query.value(idAuthor) );
            rowResult.push_back( query.value(idYear) );
            rowResult.push_back( query.value(idPublisher) );

            // Check if Description and Genre are NULLS, which they shouldn't be anymore but just in case.
            if (query.value(idDescription) == "")
            {
                rowResult.push_back( "No Description Data" );
            }
            else rowResult.push_back( query.value(idDescription) );

            if (query.value(idGenre) == "")
            {
                rowResult.push_back( "No Genre Data" );
            }
            else rowResult.push_back( query.value(idGenre) );

            rowResult.push_back( query.value(idMSRP) );
            rowResult.push_back( query.value(idCurQuantity) );

            searchResults.push_back(rowResult);

        }
    }


    outputToLogFile("dbManager::searchDB(.., .., ..) Database: closing connection");
    //qDebug() << "dbManager::searchDB(.., .., ..) Database: closing connection";
    m_db.close();

    outputToLogFile("dbManager::searchDB(.., .., ..) Database: returning search results");
    //qDebug() << "dbManager::searchDB(.., .., ..) Database: returning search results";
    return searchResults;

}

// This function returns a vector of bools that is either of size 0, 1, or 2.
// If the size is 0 or null, then there were no results for the log in process.
// If the size is 1, then exactly one result was found. The resulting bool represents if the user is an admin or not
// If the size is 2, then more than one result was found. The values of the returned bools are irrelevent and should be ignored.
QVector<bool> dbManager::checkLogInInfo(const QString username, const QString password)
{
    QVector<bool> logInResults;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
        outputToLogFile("dbManager::checkLogInInfo() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::checkLogInInfo() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::checkLogInInfo() Database: starting login process");

        QSqlQuery query("SELECT * FROM USERS WHERE USERNAME='" + username + "' AND PASSWORD='" + password + "';");
        int idAdmin = query.record().indexOf("IS_ADMIN");

        int numResults = 0;

        while (query.next())
        {

            if (numResults == 0)
            {
                outputToLogFile("dbManager::checkLogInInfo() Database: found at least 1 result");
                //qDebug() << "dbManager::checkLogInInfo() Database: found at least 1 result";
            }
            numResults++;

            // If the DB finds more than one match in the table, ...
            if (numResults > 1) {
                logInResults.push_front(false);
                break;
            }

            logInResults.push_back(true);

            if (query.value(idAdmin) == 1) logInResults.push_back(true);
            else logInResults.push_back(false);

        }


    }
    outputToLogFile("dbManager::checkLogInInfo() Database: closing connection");
    m_db.close();


    outputToLogFile("dbManager::checkLogInInfo() Database: returning login results: ");
    return logInResults;
}

QVector<QVariant> dbManager::getTotalNumBooks()
{
    QVector<QVariant> results;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
        outputToLogFile("dbManager::getTotalNumBooks() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::getTotalNumBooks() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::getTotalNumBooks() Database: starting book counting process");



        QString queryString1 = "SELECT COUNT(*) FROM BOOKS;";
        QString queryString2 = "SELECT SUM(QUANTITY_ON_HAND) FROM BOOKS;";

        QSqlQuery query1(queryString1);
        QSqlQuery query2(queryString2);

        if (query1.next())
        {
            results.push_back( query1.value(0) );
        }

        if (query2.next())
        {
            results.push_back( query2.value(0) );
        }
    }



    outputToLogFile("dbManager::getTotalNumBooks() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::getTotalNumBooks() Database: returning search results");
    return results;
}

// This function does not validate the data pased in with the newBook object, which may cause some errors to occur.
// We will need to add validation functions for our Book class to validate itself, but for now its fine.
bool dbManager::addBookRecordToDatabase(Book newBook)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::addBookRecordToDatabase() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::addBookRecordToDatabase() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::addBookRecordToDatabase() Database: attempting to add a new book record to the database");


        //QString queryString1 = "SELECT COUNT(*) FROM BOOKS;";


        QSqlQuery query;
        query.prepare("INSERT INTO BOOKS (ISBN, TITLE, AUTHOR, PUBLICATION_YEAR, PUBLISHER, DESCRIPTION, GENRE, MSRP, QUANTITY_ON_HAND) VALUES (:I, :T, :A, :Y, :P, :D, :G, :M, :Q);");
        query.bindValue(":I", QString::fromStdString(newBook.getISBN()));
        query.bindValue(":T", QString::fromStdString(newBook.getTitle()));
        query.bindValue(":A", QString::fromStdString(newBook.getAuthor()));
        query.bindValue(":Y", QString::fromStdString(to_string(newBook.getYear())));
        query.bindValue(":P", QString::fromStdString(newBook.getPublisher()));
        query.bindValue(":D", QString::fromStdString(newBook.getDescription()));
        query.bindValue(":G", QString::fromStdString(newBook.getGenre()));
        query.bindValue(":M", QString::fromStdString(to_string(newBook.getMSRP())));
        query.bindValue(":Q", QString::fromStdString(to_string(newBook.getQuantity())));

        if (query.exec())
        {
           result = true;
        }
        else
        {
           outputToLogFile("dbManager::addBookRecordToDatabase() Execution Error: " + (query.lastError().text().toStdString()));
        }
    }

    outputToLogFile("dbManager::addBookRecordToDatabase() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::addBookRecordToDatabase() Database: returning result [" + to_string(result) + "]");

    return result;
}

bool dbManager::addInvalid_BookRecordToDatabase(QString newRecord)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::addInvalid_BookRecordToDatabase() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::addInvalid_BookRecordToDatabase() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::addInvalid_BookRecordToDatabase() Database: attempting to add a new invalid_book record to the database");

        QSqlQuery query;
        query.prepare("INSERT INTO INVALID_BOOKS (INFO) VALUES (:I);");
        query.bindValue(":I", newRecord);

        if (query.exec())
        {
           result = true;
        }
        else
        {
           outputToLogFile("dbManager::addInvalid_BookRecordToDatabase() Execution Error: " + (query.lastError().text().toStdString()));
        }
    }

    outputToLogFile("dbManager::addInvalid_BookRecordToDatabase() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::addInvalid_BookRecordToDatabase() Database: returning result [" + to_string(result) + "]");

    return result;
}

bool dbManager::removeBookRecordFromDatabase(Book bookToRemove)
{
    string bookISBN = bookToRemove.getISBN();
    bool result = removeBookRecordFromDatabase(bookISBN);

    return result;
}

bool dbManager::removeBookRecordFromDatabase(string bookISBN)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::removeBookRecordFromDatabase(string) Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::removeBookRecordFromDatabase(string) Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::removeBookRecordFromDatabase(string) Database: attempting to remove a book record from the database");


        QSqlQuery countQuery;
        countQuery.prepare("SELECT COUNT(*) FROM BOOKS WHERE ISBN=':I';");
        countQuery.bindValue(":I", QString::fromStdString(bookISBN));
        QVariant count;

        if (countQuery.exec() && countQuery.next())
        {
            count = countQuery.value(0);

            if (count.convert(qMetaTypeId<int>()) == 1)
            {

                QSqlQuery deleteQuery;
                deleteQuery.prepare("DELETE FROM BOOKS WHERE ISBN=':I';");
                deleteQuery.bindValue(":I", QString::fromStdString(bookISBN));

                if (deleteQuery.exec())
                {
                    result = true;
                }
                else
                {
                   outputToLogFile("dbManager::removeBookRecordFromDatabase(string) Execution Error: " + (deleteQuery.lastError().text().toStdString()));
                }

            }
            else
            {
               outputToLogFile("dbManager::removeBookRecordFromDatabase(string) DB countQuery Error: db did not return exactly 1 result (0 or 2+ results returned)");
            }
        }
        else
        {
           outputToLogFile("dbManager::removeBookRecordFromDatabase(string) DB countQuery Error: " + (countQuery.lastError().text().toStdString()));
        }

    }

    outputToLogFile("dbManager::removeBookRecordFromDatabase(string) Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::removeBookRecordFromDatabase(string) Database: returning result [" + to_string(result) + "]");
    return result;
}

// This function SHOULD be completed now. I am not 100% sure, but so long as we can test this to make sure.
// If adjustAmount is positive this will increase the quantity of that book by that amount.
// If adjustAmount is negative this will decrease the quantity of that book by that amount
bool dbManager::adjustBookQuantityInInventory(string bookISBN, int adjustAmount)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::adjustBookQuantityInInventory() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::adjustBookQuantityInInventory() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::adjustBookQuantityInInventory() Database: attempting to adjust a book record's Quantity value in the database");


        QSqlQuery countQuery;
        countQuery.prepare("SELECT COUNT(*) FROM BOOKS WHERE ISBN=:I;");
        countQuery.bindValue(":I", QString::fromStdString(bookISBN));
        QVariant count;

        if (countQuery.exec() && countQuery.next())
        {
            count = countQuery.value(0);

            if (count.convert(qMetaTypeId<int>()) == 1)
            {

                QSqlQuery selectQuery;
                selectQuery.prepare("SELECT QUANTITY_ON_HAND FROM BOOKS WHERE ISBN=:I;");
                selectQuery.bindValue(":I", QString::fromStdString(bookISBN));

                if (selectQuery.exec())
                {
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE BOOKS SET QUANTITY_ON_HAND=QUANTITY_ON_HAND+:A WHERE ISBN=:I;");
                    updateQuery.bindValue(":I", QString::fromStdString(bookISBN));
                    updateQuery.bindValue(":A", QString::fromStdString(to_string(adjustAmount)));

                    if (updateQuery.exec())
                    {
                        result = true;
                    }
                    else
                    {
                        outputToLogFile("dbManager::adjustBookQuantityInInventory() Execution Error: " + (updateQuery.lastError().text().toStdString()));
                    }

                }
                else
                {
                   outputToLogFile("dbManager::adjustBookQuantityInInventory() Execution Error: " + (selectQuery.lastError().text().toStdString()));
                }

            }
            else
            {
               outputToLogFile("dbManager::adjustBookQuantityInInventory() DB countQuery Error: db did not return exactly 1 result (0 or 2+ results returned)");
            }
        }
        else
        {
           outputToLogFile("dbManager::adjustBookQuantityInInventory() DB countQuery Error: " + (countQuery.lastError().text().toStdString()));
        }

    }

    outputToLogFile("dbManager::adjustBookQuantityInInventory() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::adjustBookQuantityInInventory() Database: returning result [" + to_string(result) + "]");
    return result;
}

bool dbManager::addShopperToDatabase(QString firstName, QString lastName, QString email)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::addShopperToDatabase() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::addShopperToDatabase() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::addShopperToDatabase() Database: attempting to add a shopper record to the database");

        QSqlQuery query;
        query.prepare("INSERT INTO SHOPPERS (FIRST_NAME, LAST_NAME, EMAIL, TOTAL_SPENT) VALUES (:F, :L, :E, :T);");
        query.bindValue(":F", firstName);
        query.bindValue(":L", lastName);
        query.bindValue(":E", email);
        query.bindValue(":T", 0);


        if (query.exec())
        {
           result = true;
        }
        else
        {
           outputToLogFile("dbManager::addShopperToDatabase() Execution Error: " + (query.lastError().text().toStdString()));
        }
    }

    outputToLogFile("dbManager::addShopperToDatabase() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::addShopperToDatabase() Database: returning result [" + to_string(result) + "]");

    return result;
}

// For text/string values, surround the new value in 'single quotes'. For numbers do not.
bool dbManager::updateBookRecordColumnValue(string bookISBN, string categoryToUpdate, string newValue)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::updateBookRecordColumnValue() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::updateBookRecordColumnValue() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::updateBookRecordColumnValue() Database: attempting to update a book record's '" + categoryToUpdate + "' value in the database");


        QSqlQuery countQuery;
        countQuery.prepare("SELECT COUNT(*) FROM BOOKS WHERE ISBN=':I';");
        countQuery.bindValue(":I", QString::fromStdString(bookISBN));
        QVariant count;

        if (countQuery.exec() && countQuery.next())
        {
            count = countQuery.value(0);

            if (count.convert(qMetaTypeId<int>()) == 1)
            {

                QSqlQuery selectQuery;
                selectQuery.prepare("SELECT :C FROM BOOKS WHERE ISBN=':I';");
                selectQuery.bindValue(":I", QString::fromStdString(bookISBN));
                selectQuery.bindValue(":C", QString::fromStdString(categoryToUpdate));

                if (selectQuery.exec())
                {
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE BOOKS SET " + QString::fromStdString(categoryToUpdate) + " = :N WHERE ISBN= :I;");
                    updateQuery.bindValue(":I", QString::fromStdString(bookISBN));
                    updateQuery.bindValue(":N", QString::fromStdString(newValue));

                    if (updateQuery.exec())
                    {
                        result = true;
                    }
                    else
                    {
                        outputToLogFile("dbManager::updateBookRecordColumnValue() Execution Error: " + (updateQuery.lastError().text().toStdString()));
                    }

                }
                else
                {
                   outputToLogFile("dbManager::updateBookRecordColumnValue() Execution Error: " + (selectQuery.lastError().text().toStdString()));
                }

            }
            else
            {
               outputToLogFile("dbManager::updateBookRecordColumnValue() DB countQuery Error: db did not return exactly 1 result (0 or 2+ results returned)");
            }
        }
        else
        {
           outputToLogFile("dbManager::updateBookRecordColumnValue() DB countQuery Error: " + (countQuery.lastError().text().toStdString()));
        }

    }

    outputToLogFile("dbManager::updateBookRecordColumnValue() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::updateBookRecordColumnValue() Database: returning result [" + to_string(result) + "]");
    return result;
}

bool dbManager::addNewUser(QString username, QString password, bool isAdmin)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::addNewUser() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::addNewUser() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::addNewUser() Database: attempting to add a new user record to the database");


        //QString queryString1 = "SELECT COUNT(*) FROM BOOKS;";


        QSqlQuery query;
        query.prepare("INSERT INTO USERS (USERNAME, PASSWORD, IS_ADMIN) VALUES (:U, :P, :A);");
        query.bindValue(":U", username);
        query.bindValue(":P", password);
        query.bindValue(":A", isAdmin);

        if (query.exec())
        {
           result = true;
        }
        else
        {
           outputToLogFile("dbManager::addNewUser() Execution Error: " + (query.lastError().text().toStdString()));
        }

    }

    outputToLogFile("dbManager::addNewUser() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::addNewUser() Database: returning result [" + to_string(result) + "]");
    return result;
}

bool dbManager::changeUserPassword(QString username, QString password)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::changeUserPassword() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::changeUserPassword() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::changeUserPassword() Database: attempting to adjust a user record's Password value in the database");


        QSqlQuery countQuery;
        countQuery.prepare("SELECT COUNT(*) FROM USERS WHERE USERNAME=':U';");
        countQuery.bindValue(":U", username);
        QVariant count;

        if (countQuery.exec() && countQuery.next())
        {
            count = countQuery.value(0);

            if (count.convert(qMetaTypeId<int>()) == 1)
            {

                QSqlQuery selectQuery;
                selectQuery.prepare("SELECT PASSWORD FROM USERS WHERE USERNAME=':U';");
                selectQuery.bindValue(":U", username);

                if (selectQuery.exec())
                {
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE USERS SET PASSWORD=:P WHERE USERNAME=:U;");
                    updateQuery.bindValue(":U", username);
                    updateQuery.bindValue(":P", password);

                    if (updateQuery.exec())
                    {
                        outputToLogFile("dbManager::changeUserPassword() UpdateQuery has been executed.");
                        result = true;
                    }
                    else
                    {
                        outputToLogFile("dbManager::changeUserPassword() Execution Error: " + (updateQuery.lastError().text().toStdString()));
                    }

                }
                else
                {
                   outputToLogFile("dbManager::changeUserPassword() Execution Error: " + (selectQuery.lastError().text().toStdString()));
                }

            }
            else
            {
               outputToLogFile("dbManager::changeUserPassword() DB countQuery Error: db did not return exactly 1 result (0 or 2+ results returned)");
            }
        }
        else
        {
           outputToLogFile("dbManager::changeUserPassword() DB countQuery Error: " + (countQuery.lastError().text().toStdString()));
        }

    }

    outputToLogFile("dbManager::changeUserPassword() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::changeUserPassword() Database: returning result [" + to_string(result) + "]");
    return result;


}

bool dbManager::checkForValidShopper(QString shopperEmail)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::checkForValidShopper() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::checkForValidShopper() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::checkForValidShopper() Database: attempting to check for a valid shopper record in the database");


        QSqlQuery countQuery;
        countQuery.prepare("SELECT COUNT(*) FROM SHOPPERS WHERE EMAIL=:E;");
        countQuery.bindValue(":E", shopperEmail);
        QVariant count;

        if (countQuery.exec() && countQuery.next())
        {
            count = countQuery.value(0);

            if (count.convert(qMetaTypeId<int>()) == 1)
            {
                result = true;
            }
            else
            {
               outputToLogFile("dbManager::checkForValidShopper() DB countQuery Error: db did not return exactly 1 result (0 or 2+ results returned)");
            }
        }
        else
        {
           outputToLogFile("dbManager::checkForValidShopper() DB countQuery Error: " + (countQuery.lastError().text().toStdString()));
        }
    }

    outputToLogFile("dbManager::checkForValidShopper() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::checkForValidShopper() Database: returning result [" + to_string(result) + "]");
    return result;
}

bool dbManager::increaseShopperTotalSpent(QString shopperEmail, int amount)
{
    bool result = false;
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("bookstoreInventory.db");

    if (!m_db.open())
    {
       outputToLogFile("dbManager::increaseShopperTotalSpent() Error: connection with database named \"bookstoreInventory.db\" failed");
    }
    else
    {
        outputToLogFile("dbManager::increaseShopperTotalSpent() Database: connection ok with database named \"bookstoreInventory.db\"");

        outputToLogFile("dbManager::increaseShopperTotalSpent() Database: attempting to increase a shopper's total_spent in the database");


        QSqlQuery countQuery;
        countQuery.prepare("SELECT COUNT(*) FROM SHOPPERS WHERE EMAIL=:E;");
        countQuery.bindValue(":E", shopperEmail);
        QVariant count;

        if (countQuery.exec() && countQuery.next())
        {
            count = countQuery.value(0);

            if (count.convert(qMetaTypeId<int>()) == 1)
            {
                QSqlQuery selectQuery;
                selectQuery.prepare("SELECT TOTAL_SPENT FROM SHOPPERS WHERE EMAIL=:E");
                selectQuery.bindValue(":E", shopperEmail);

                if (selectQuery.exec())
                {
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE SHOPPERS SET TOTAL_SPENT=TOTAL_SPENT+:A WHERE EMAIL=:E");
                    updateQuery.bindValue(":E", shopperEmail);
                    updateQuery.bindValue(":A", amount);

                    if (updateQuery.exec())
                    {
                        result = true;
                    }
                    else
                    {
                        outputToLogFile("dbManager::adjustBookQuantityInInventory() Execution Error: " + (updateQuery.lastError().text().toStdString()));
                    }

                }
                else
                {
                   outputToLogFile("dbManager::adjustBookQuantityInInventory() Execution Error: " + (selectQuery.lastError().text().toStdString()));
                }
            }
            else
            {
               outputToLogFile("dbManager::increaseShopperTotalSpent() DB countQuery Error: db did not return exactly 1 result (0 or 2+ results returned)");
            }
        }
        else
        {
           outputToLogFile("dbManager::increaseShopperTotalSpent() DB countQuery Error: " + (countQuery.lastError().text().toStdString()));
        }
    }

    outputToLogFile("dbManager::increaseShopperTotalSpent() Database: closing connection");
    m_db.close();

    outputToLogFile("dbManager::increaseShopperTotalSpent() Database: returning result [" + to_string(result) + "]");
    return result;
}

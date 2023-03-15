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

QVector<QVector<QVariant>> dbManager::searchDB(const QString& path, const QString searchTerm)
{
    QVector<QVector<QVariant>> searchResults;
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

    qDebug() << "Database: starting search";

    QSqlQuery query("SELECT * FROM BOOKS WHERE TITLE LIKE '%" + searchTerm + "%';");
    int idISBN = query.record().indexOf("ISBN");
    int idTitle = query.record().indexOf("TITLE");
    int idAuthor = query.record().indexOf("AUTHOR");
    int idYear = query.record().indexOf("PUBLICATION_YEAR");
    int idPublisher = query.record().indexOf("PUBLISHER");
    int idMSRP = query.record().indexOf("MSRP");
    int idCurQuantity = query.record().indexOf("QUANTITY_ON_HAND");

    int numResults = 0;

    while (query.next())
    {

        qDebug() << "Database: found a result";
        numResults++;

        QVector<QVariant> rowResult;
        rowResult.push_back( numResults );
        rowResult.push_back( query.value(idISBN) );
        rowResult.push_back( query.value(idTitle) );
        rowResult.push_back( query.value(idAuthor) );
        rowResult.push_back( query.value(idYear) );
        rowResult.push_back( query.value(idPublisher) );
        rowResult.push_back( query.value(idMSRP) );
        rowResult.push_back( query.value(idCurQuantity) );

        searchResults.push_back(rowResult);;

    }

    qDebug() << "Database: closing connection";
    m_db.close();

    qDebug() << "Database: returning search results";
    return searchResults;

}

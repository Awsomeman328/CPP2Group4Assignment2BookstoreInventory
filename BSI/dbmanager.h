#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <Qtsql/QtSql>
#include <QVector>
#include "utilities.h"

class dbManager
{
public:
    dbManager(const QString& path);
    std::string createDB(const QString& path); // The returned string will send a message of if this method was successful
    QVector<QVariant> readDB(const QString& path);
    QVector<QVector<QVariant>> searchDB(const QString& path, const QString searchTerm, const int searchCategory);
    QVector<bool> checkLogInInfo(const QString username, const QString password);
    QVector<QVariant> getTotalNumBooks();
    bool addBookRecordToDatabase(Book newBook);
    bool addInvalid_BookRecordToDatabase(QString newRecord);
    bool removeBookRecordFromDatabase(Book bookToRemove);
    bool removeBookRecordFromDatabase(string bookISBN);
    bool adjustBookQuantityInInventory(string bookISBN, int adjustAmount);


private:
    QSqlDatabase m_db; // The object holding our SQL Database commands

};

#endif // DBMANAGER_H

#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <Qtsql/QtSql>
#include <QVector>

class dbManager
{
public:
    dbManager(const QString& path);
    std::string createDB(const QString& path); // The returned string will send a message of if this method was successful
    QVector<QVariant> readDB(const QString& path);
    QVector<QVector<QVariant>> searchDB(const QString& path, const QString searchTerm, const int searchCategory);
    QVector<bool> checkLogInInfo(const QString username, const QString password);
    QVector<QVariant> getTotalNumBooks();


private:
    QSqlDatabase m_db; // The object holding our SQL Database commands

};

#endif // DBMANAGER_H

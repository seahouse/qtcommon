#ifndef CONNECTION
#define CONNECTION

#include "sglobal.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid())
    {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(DB_HOST);
        db.setDatabaseName(DB_DATABASE);
        db.setUserName(DB_USERNAME);
        db.setPassword(DB_PASSWORD);
    }

    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    return true;
}

#endif // CONNECTION


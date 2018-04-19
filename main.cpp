#include <QCoreApplication>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //The name of the instance of SQLEXPRESS. You can find this through the Server Manager
    QString serverName = "DESKTOP-JDNIX\\SQLEXPRESS";
    //The name of the database you're trying to connect to
    QString dbName = "test";

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");

    db.setConnectOptions();

    //Use only one dsn at a time
    //QString dsn = QString("DRIVER={SQL Native Client};SERVER=%1;DATABASE=%2;Trusted_Connection=Yes;").arg(serverName).arg(dbName);
    QString dsn = QString("DRIVER={SQL Native Client 11.0};SERVER=DESKTOP-JDNIX\\SQLEXPRESS;DATABASE=test;Trusted_Connection=Yes;");

    //Set the name of the connection
    //db.setDatabaseName(dsn);
    db.setDatabaseName("mydsn32"); //must be created through ODBC Data Sources (32-bit) in Administrative Tools in Windows Control Panel
    //db.setDatabaseName("mydsn64"); //must be created through ODBC Data Sources (64-bit) in Administrative Tools in Windows Control Panel

    //Console debug line that makes sure we have the QODBC3 driver
    qDebug() << QSqlDatabase::isDriverAvailable("QODBC3"); // returns true

    //open a connection to the database. Otherwise, report the error
    if (db.open())
    {
        qDebug() << "Opened!";

        qDebug() << "Closing...";
        db.close();
    }
    else
    {
        qDebug() << "Error = " << db.lastError().text();
    }

    //Opens the connection to the database, creates a query to send to the database, then displays the information in the console.
    if (db.open())
    {
        qDebug() << "Opened!";

        QSqlQuery qry;

        QString sQuery = "INSERT INTO [dbo].[People] ([ID],[FirstName],[LastName]) VALUES(:id,:first,:last)";

        qry.prepare(sQuery);

        qry.bindValue(":id", "4");
        qry.bindValue(":first", "Tyrande");
        qry.bindValue(":last", "Whisperwind");

        //execute the prepared query, inserting a record. Otherwise, report the error
        if (qry.exec())
        {
            qDebug() << "Record inserted";
        }
        else
        {
            qDebug() << "Error = " << db.lastError().text();
        }

        //execute the query provided as a string argument. Otherwise, report the error
        if (qry.exec("SELECT * FROM [test].[dbo].[People]"))
        {
            while(qry.next())
            {
                qDebug() << qry.value(0).toString() << qry.value(1).toString() << qry.value(2).toString();
            }
        }
        else
        {
            qDebug() << "Error = " << db.lastError().text();
        }

        qDebug() << "Closing...";
        db.close();
    }
    else
    {
        qDebug() << "Error = " << db.lastError().text();
    }

    return a.exec();
}

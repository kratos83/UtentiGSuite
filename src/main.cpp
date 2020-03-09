#include "mainwindow.h"
#include <QtSql>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dat.db");
    db.open();
    MainWindow w;
    w.show();
    return a.exec();
}

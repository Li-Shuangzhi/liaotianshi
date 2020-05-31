#include "mainwidget.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

//链接数据库
void linkdb(QSqlDatabase*db){

    *db = QSqlDatabase::addDatabase("QMYSQL");
    db->setHostName("114.215.141.131");
    db->setDatabaseName("qtdatabase");
    db->setUserName("root");
    db->setPort(3306);
    db->setPassword("root");
    bool ok = db->open();
    if(ok)
    {
        qDebug()<<"ok";
    }else{
        qDebug()<<"open db errors";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db;
    //调用linkdb函数，链接数据库
    linkdb(&db);
    mainWidget w;
    w.show();

    return a.exec();
}

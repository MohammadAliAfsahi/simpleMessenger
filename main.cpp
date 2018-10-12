#include "homepage.h"
#include <QApplication>
#include <QGuiApplication>
#include "goodnewsmessengar.h"
#include "signup.h"
#include "WellcomePage.h"

#include "widget.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QJsonObject>
#include <QSqlRecord>

#include <QGuiApplication>
#include <QThread>
using namespace std;
QString USERN,PASSWOR,TOKEN;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //    HomePage w;
    //    w.show();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");
    db.setDatabaseName("project");
    db.setUserName("root");
    db.setPassword("project3939");
    db.open();
    QSqlQuery query;
    QByteArray temp;
    QJsonObject obj;
    QJsonDocument doc;
    // DELETE FROM 'project'.'lists' WHERE  'GetUserLists' IS NULL AND 'GetGroupLists' IS NULL AND 'GetChannelLists' IS NULL LIMIT 1;
    query.exec("DELETE FROM `project`.`lists` WHERE  `GetUserLists` IS NULL AND `GetGroupLists` IS NULL AND `GetChannelLists` IS NULL LIMIT 1");
    query.clear();
    query.exec("SELECT * FROM login_token WHERE JSON_CONTAINS(login, '\"Logged in Successfully\"', '$.message')");
    while(query.next())
    {
        //        qDebug()<<query.value(0).toString();
        temp=query.value(0).toByteArray();
        doc=QJsonDocument::fromJson(temp);
        obj=doc.object();
        TOKEN=obj["token"].toString();
        USERN=query.value(1).toByteArray();
    }


    if(obj["message"].toString()=="Logged in Successfully")
    {
        Widget w;
//        QThread cThread;
        w.set();
//        w.moveToThread(&cThread);
//        cThread.start();
        w.exec();
    }
    else
    {
        WellcomePage s;
        s.exec();
    }
    //    GoodNewsMessengar s;
    //    s.show();
    //  return a.exec();
    return 0;
    //return app.exec();
}

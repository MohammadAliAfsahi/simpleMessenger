#include "getchats.h"

#include "ui_widget.h"
#include <QDate>
#include <QDateTime>

#include <QSqlQuery>

extern QString USERN,PASSWOR,TOKEN;
extern int ret;

GetChats::GetChats()
{
    managerguc = new QNetworkAccessManager();
    managerggc = new QNetworkAccessManager();
    managergcc = new QNetworkAccessManager();

    connect(managerguc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinguc(QNetworkReply*)));
    connect(managerggc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinggc(QNetworkReply*)));
    connect(managergcc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfingcc(QNetworkReply*)));
}

GetChats::~GetChats()
{

}

void GetChats::DoSetup(QThread &cThread)
{
    connect(&cThread,SIGNAL(started()),this,SLOT(Get()));
}

void GetChats::Get()
{

    QString link;
    QString dst;
    bool ok;
    QDate current(QDate::currentDate());
    current.addMonths(-6).toString("yyyyMMdd");
    QString day= QString::number(current.day());
    QString month = QString::number(current.month());
    QString year = QString::number(current.year());
    //    qDebug()<<year<<month<<day;
    //    qDebug()<<current.addMonths(-6).toString("yyyyMMdd");
    QDateTime curtime(QDateTime::currentDateTime());
    //    qDebug()<<curtime.toString("HHmmss");

    // dst=ui->Name->text();

    set("h");

    if(ui->lblname->text()=="UserName")
    {
        qDebug()<<"in user name";
        link="http://api.softserver.org:1104/getuserchats?token=";
        link.append(TOKEN);
        link.append("&dst=");
        link.append(dst);
        link+="&date="+current.addMonths(-6).toString("yyyyMMdd")+curtime.toString("HHmmss");
        request.setUrl(QUrl(link));
        managerguc->get(request);
    }
    else if(ui->lblname->text()=="GroupName")
    {
        qDebug()<<"in group name";
        link="http://api.softserver.org:1104/getgroupchats?token=";
        link.append(TOKEN);
        link.append("&dst=");
        link.append(dst);
        request.setUrl(QUrl(link));
        managerggc->get(request);
    }
    else if(ui->lblname->text()=="ChannelName")
    {
        qDebug()<<"in channel name";
        link="http://api.softserver.org:1104/getchannelchats?token=";
        link.append(TOKEN);
        link.append("&dst=");
        link.append(dst);
        request.setUrl(QUrl(link));
        managergcc->get(request);
    }
}
void GetChats::mfinguc(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        qDebug() << reply->errorString ();
        return;
    }
    QByteArray test = reply->readAll ();
    //    qDebug()<<test;
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    //    qDebug()<<obj["message"].toString();


    //    qDebug()<<no;
    //    qDebug()<<obj["block 0"].toObject()["src"].toString();
    QString stt;
    QSqlQuery query;
    QString jsobj(doc.toJson(QJsonDocument::Compact));
    stt.clear();
    query.clear();

    stt.append("INSERT INTO chat (messagesU) VALUES ('");
    stt.append(jsobj);
    stt+="')";
    //    qDebug()<<stt;
    query.prepare(stt);
    query.exec();

    stt.clear();
    query.clear();

    query.exec("SELECT * FROM chat WHERE JSON_CONTAINS(messagesU, '\"200\"', '$.code')");
    while(query.next())
    {
        //        qDebug()<<query.value(0).toString();
        temp=query.value(2).toByteArray();
        doc=QJsonDocument::fromJson(temp);
        obj=doc.object();
    }
    QString number= obj["message"].toString();
    int no=number[11].digitValue();
    for(int i=0;i<no;i++)
    {
        QString block= "block "+QString::number(i);
        if(obj[block].toObject()["dst"].toString()==ui->Name->text() || obj[block].toObject()["src"].toString()==ui->Name->text() )
            ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());
        //        else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
    }
}

void GetChats::mfinggc(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        qDebug() << reply->errorString ();
        return;
    }
    QByteArray test = reply->readAll ();
    //    qDebug()<<test;
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    //    qDebug()<<obj["message"].toString();


    //    qDebug()<<no;
    QString stt;
    QSqlQuery query;
    QString jsobj(doc.toJson(QJsonDocument::Compact));

    stt.clear();
    query.clear();

    stt.append("INSERT INTO chat (messagesG) VALUES ('");
    stt.append(jsobj);
    stt+="')";
    //    qDebug()<<stt;
    query.prepare(stt);
    query.exec();

    stt.clear();
    query.clear();

    query.exec("SELECT * FROM chat WHERE JSON_CONTAINS(messagesG, '\"200\"', '$.code')");
    while(query.next())
    {
        //        qDebug()<<query.value(0).toString();
        temp=query.value(0).toByteArray();
        doc=QJsonDocument::fromJson(temp);
        obj=doc.object();
    }
    QString number= obj["message"].toString();
    int no=number[11].digitValue();
    for(int i=0;i<no;i++)
    {
        QString block= "block "+QString::number(i);

        //        if(obj[block].toObject()["dst"].toString()==ui->Name->text())
        //            ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());
        //        else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
    }
}

void GetChats::mfingcc(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        qDebug() << reply->errorString ();
        return;
    }

    QByteArray test = reply->readAll ();
    //    qDebug()<<test;
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    //    qDebug()<<obj["message"].toString();


    //    qDebug()<<no;

    QString stt;
    QSqlQuery query;
    QString jsobj(doc.toJson(QJsonDocument::Compact));
    stt.append("INSERT INTO chat (messagesC) VALUES ('");
    stt.append(jsobj);
    stt+="')";
    //    qDebug()<<stt;
    query.prepare(stt);
    query.exec();

    stt.clear();
    query.clear();

    query.exec("SELECT * FROM chat WHERE JSON_CONTAINS(messagesC, '\"200\"', '$.code')");
    while(query.next())
    {
        //        qDebug()<<query.value(0).toString();
        temp=query.value(1).toByteArray();
        doc=QJsonDocument::fromJson(temp);
        obj=doc.object();
    }
    QString number= obj["message"].toString();
    int no=number[11].digitValue();

    for(int i=0;i<no;i++)
    {
        QString block= "block "+QString::number(i);

        //        if(obj[block].toObject()["dst"].toString()==ui->Name->text())
        //            ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());
        //        else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
    }
}

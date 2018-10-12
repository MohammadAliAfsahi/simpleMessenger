#include "showchats.h"
#include "ui_showchats.h"

#include <QDate>
#include <QDateTime>

extern QString USERN,PASSWOR,TOKEN;
extern int ret;

ShowChats::ShowChats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowChats)
{
    ui->setupUi(this);
    managerguc = new QNetworkAccessManager();
    managerggc = new QNetworkAccessManager();
    managergcc = new QNetworkAccessManager();

    connect(managerguc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinguc(QNetworkReply*)));
    connect(managerggc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinggc(QNetworkReply*)));
    connect(managergcc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfingcc(QNetworkReply*)));
}

void ShowChats::ChangeLabelText(QString text)
{
    ui->lblname->setText(text);
}

ShowChats::~ShowChats()
{
    delete ui;
}

void ShowChats::on_SendRequest_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QDate current(QDate::currentDate());
    current.addMonths(-6).toString("yyyyMMdd");
    QString day= QString::number(current.day());
    QString month = QString::number(current.month());
    QString year = QString::number(current.year());
    qDebug()<<year<<month<<day;
    qDebug()<<current.addMonths(-6).toString("yyyyMMdd");
    QDateTime curtime(QDateTime::currentDateTime());
    qDebug()<<curtime.toString("HHmmss");

    if(ui->lblname->text()=="UserName")
    {
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
        link="http://api.softserver.org:1104/getgroupchats?token=";
        link.append(TOKEN);
        link.append("&dst=");
        link.append(dst);
        request.setUrl(QUrl(link));
        managerggc->get(request);
    }
    else if(ui->lblname->text()=="ChannelName")
    {
        link="http://api.softserver.org:1104/getchannelchats?token=";
        link.append(TOKEN);
        link.append("&dst=");
        link.append(dst);
        request.setUrl(QUrl(link));
        managergcc->get(request);
    }

}
void ShowChats::mfinguc(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        qDebug() << reply->errorString ();
        return;
    }
    QByteArray test = reply->readAll ();
    qDebug()<<test;
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    qDebug()<<obj["message"].toString();

    QString number= obj["message"].toString();
    int no=number[11].digitValue();
    qDebug()<<no;
    qDebug()<<obj["block 0"].toObject()["src"].toString();

    for(int i=0;i<no;i++)
    {
        QString block= "block "+QString::number(i);
        if(obj[block].toObject()["dst"].toString()==USERN)
            ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());


        //        else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
    }
}

void ShowChats::mfinggc(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        qDebug() << reply->errorString ();
        return;
    }
    QByteArray test = reply->readAll ();
    qDebug()<<test;
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    qDebug()<<obj["message"].toString();

    QString number= obj["message"].toString();
    int no=number[11].digitValue();
    qDebug()<<no;
    for(int i=0;i<no;i++)
    {
        QString block= "block "+QString::number(i);

        //        if(obj[block]["dst"].toString()==USERN)
        //        ui->textEdit->append(obj[block]["src"].toString()+" : "+obj[block]["body"].toString());

        //        else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
    }
}

void ShowChats::mfingcc(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        qDebug() << reply->errorString ();
        return;
    }
    QByteArray test = reply->readAll ();
    qDebug()<<test;
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    qDebug()<<obj["message"].toString();

    QString number= obj["message"].toString();
    int no=number[11].digitValue();
    qDebug()<<no;
}

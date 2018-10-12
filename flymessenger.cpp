#include "flymessenger.h"
#include "ui_flymessenger.h"
#include "homepage.h"

#include <QInputDialog>
#include <string>
#include <QScrollArea>
#include <QWidget>
#include <QPushButton>
#include <QSqlRecord>
#include <QSqlField>
#include "WellcomePage.h"

using namespace std;

extern QString USERN,PASSWOR,TOKEN;
extern int ret;
FlyMessenger::FlyMessenger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlyMessenger)
{
    ui->setupUi(this);

    //    db.setHostName("127.0.0.1");
    //    db.setDatabaseName("project");
    //    db.setUserName("root");
    //    db.setPassword("project3939");
    //db.open();



    //    managersum = new QNetworkAccessManager();
    //    managerscm = new QNetworkAccessManager();
    //    managersgm = new QNetworkAccessManager();
//    managerguc = new QNetworkAccessManager();
//    managerggc = new QNetworkAccessManager();
//    managergcc = new QNetworkAccessManager();



//    connect(managerggl,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinggl(QNetworkReply*)));
//    connect(managergcl,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfingcl(QNetworkReply*)));
//    connect(managergul,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfingul(QNetworkReply*)));

    //    connect(managersum,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinsum(QNetworkReply*)));
    //    connect(managerscm,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinscm(QNetworkReply*)));
    //    connect(managersgm,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinsgm(QNetworkReply*)));

//    connect(managerguc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinguc(QNetworkReply*)));
//    connect(managerggc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinggc(QNetworkReply*)));
//    connect(managergcc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfingcc(QNetworkReply*)));



}

FlyMessenger::~FlyMessenger()
{
    delete ui;
}
void FlyMessenger::on_btnLogout_clicked()
{

}

//void FlyMessenger::mfinggl(QNetworkReply *reply)
//{
//    QString s;
//    if(reply->error()){
//        qDebug() << reply->errorString ();
//        return;
//    }
//    QByteArray test = reply->readAll ();
//    qDebug()<<test;
//    QJsonDocument doc = QJsonDocument::fromJson(test);
//    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();
//    string str=obj["message"].toString().toStdString();

//    string garbage;
//    int no= str[12]-'0';

//    qDebug()<<no;
//    QString block;

//    for(size_t i=0;i<no;i++)
//    {
//        qDebug()<<i;
//        block.append("block ");
//        block.append(QString::number(i));
//        qDebug()<<block;
//        qDebug()<<obj[block].toObject()["group_name"].toString();
//        //        button->setText(obj[block][0]["group_name"].toString());
//        QPushButton *button = new QPushButton(this);
//        button->setText(obj[block].toObject()["group_name"].toString());
//        button->setStyleSheet("border:2px solid #ff4c4c;"
//                              "border-radius:5px;"
//                              "color:#a62af9;");
//        block.clear();
//        ui->scrollAreaWidgetContents->layout()->addWidget(button);
//    }
//}

//void FlyMessenger::mfingcl(QNetworkReply *reply)
//{
//    QString s;
//    if(reply->error()){
//        qDebug() << reply->errorString ();
//        return;
//    }
//    QByteArray test = reply->readAll ();
//    qDebug()<<test;
//    QJsonDocument doc = QJsonDocument::fromJson(test);
//    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();
//    string str=obj["message"].toString().toStdString();
//    string garbage;
//    int no= str[12]-'0';

//    qDebug()<<no;
//    QString block;
//    for(size_t i=0;i<no;i++)
//    {
//        qDebug()<<i;
//        block.append("block ");
//        block.append(QString::number(i));
//        qDebug()<<block;
//        qDebug()<<obj[block].toObject()["channel_name"].toString();
//        //        button->setText(obj[block][0]["group_name"].toString());
//        QPushButton *button = new QPushButton(this);
//        button->setText(obj[block].toObject()["channel_name"].toString());
//        button->setStyleSheet("border:2px solid #ff4c4c;"
//                              "border-radius:5px;"
//                              "color:#a62af9;");
//        block.clear();
//        ui->scrollAreaWidgetContents->layout()->addWidget(button);
//    }
//}

//void FlyMessenger::mfingul(QNetworkReply *reply)
//{
//    QString s;
//    if(reply->error()){
//        qDebug() << reply->errorString ();
//        return;
//    }
//    QByteArray test = reply->readAll ();
//    qDebug()<<test;
//    QJsonDocument doc = QJsonDocument::fromJson(test);
//    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();
//    //"You Chat With -0- User"
//    string str=obj["message"].toString().toStdString();
//    string garbage;
//    int no= str[20]-'0';

//    qDebug()<<no;
//    QString block;

//    ui->scrollAreaWidgetContents->layout()->update();
//    for(size_t i=0;i<no;i++)
//    {
//        qDebug()<<i;
//        block.append("block ");
//        block.append(QString::number(i));
//        qDebug()<<block;
//        qDebug()<<obj[block].toObject()["group_name"].toString();
//        //        button->setText(obj[block][0]["group_name"].toString());
//        QPushButton *button = new QPushButton(this);
//        button->setText(obj[block].toObject()["group_name"].toString());
//        button->setStyleSheet("border:2px solid #ff4c4c;"
//                              "border-radius:5px;"
//                              "color:#a62af9;");
//        block.clear();
//        ui->scrollAreaWidgetContents->layout()->addWidget(button);
//    }
//}

//void FlyMessenger::mfinsum(QNetworkReply *reply)
//{
//    QString s;
//    if(reply->error()){
//        qDebug() << reply->errorString ();
//        return;
//    }
//    QByteArray test = reply->readAll ();
//    qDebug()<<test;
//    QJsonDocument doc = QJsonDocument::fromJson(test);
//    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();
//    if(obj["message"].toString()== "Message Sent Successfully")
//    {

//    }
//    else{

//    }

//}

//void FlyMessenger::mfinscm(QNetworkReply *reply)
//{
//    QString s;
//    if(reply->error()){
//        qDebug() << reply->errorString ();
//        return;
//    }
//    QByteArray test = reply->readAll ();
//    qDebug()<<test;
//    QJsonDocument doc = QJsonDocument::fromJson(test);
//    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();
//    if(obj["message"].toString()== "Message Sent Successfully")
//    {

//    }
//    else{

//    }

//}

//void FlyMessenger::mfinsgm(QNetworkReply *reply)
//{
//    QString s;
//    if(reply->error()){
//        qDebug() << reply->errorString ();
//        return;
//    }
//    QByteArray test = reply->readAll ();
//    qDebug()<<test;
//    QJsonDocument doc = QJsonDocument::fromJson(test);
//    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();
//    if(obj["message"].toString()== "Message Sent Successfully")
//    {

//    }
//    else{

//    }
//}

//void FlyMessenger::mfinguc(QNetworkReply *reply)
//{
//    QString s;
//    if(reply->error()){
//        qDebug() << reply->errorString ();
//        return;
//    }
//    QByteArray test = reply->readAll ();
//    qDebug()<<test;
//    QJsonDocument doc = QJsonDocument::fromJson(test);
//    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();

//    QString number= obj["message"].toString();
//    int no=number[11].digitValue();
//    qDebug()<<no;
//    for(int i=0;i<no;i++)
//    {
//        QString block= "block "+QString::number(i);
//        if(obj[block]["dst"].toString()==USERN)
//            ui->textEdit->append(obj[block]["src"].toString()+" : "+obj[block]["body"].toString());

//        //        else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
//    }
//    if(obj["message"].toString()== "Message Sent Successfully")
//    {

//    }
//    else
//    {

//    }
//}

//void FlyMessenger::mfinggc(QNetworkReply *reply)
//{
//    QString s;
//    if(reply->error()){
//        qDebug() << reply->errorString ();
//        return;
//    }
//    QByteArray test = reply->readAll ();
//    qDebug()<<test;
//    QJsonDocument doc = QJsonDocument::fromJson(test);
//    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();

//    QString number= obj["message"].toString();
//    int no=number[11].digitValue();
//    qDebug()<<no;

//    if(obj["message"].toString()== "Message Sent Successfully")
//    {

//    }
//    else{

//    }
//}

//void FlyMessenger::mfingcc(QNetworkReply *reply)
//{
//    QString s;
//    if(reply->error()){
//        qDebug() << reply->errorString ();
//        return;
//    }
//    QByteArray test = reply->readAll ();
//    qDebug()<<test;
//    QJsonDocument doc = QJsonDocument::fromJson(test);
//    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();

//    QString number= obj["message"].toString();
//    int no=number[11].digitValue();
//    qDebug()<<no;

//    if(obj["message"].toString()== "Message Sent Successfully")
//    {

//    }
//    else{

//    }
//}


void FlyMessenger::on_btnCreateGroup_clicked()
{

}

void FlyMessenger::on_btnCreateChannel_clicked()
{

}

void FlyMessenger::on_btnJoinGroup_clicked()
{

}

void FlyMessenger::on_btnJoinChannel_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Channel name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api.softserver.org:1104/joinchannel?token=";
    link.append(TOKEN);
    link.append("&channel_name=");
    link.append(dst);
    request.setUrl(QUrl(link));
    managerjc->get(request);
}

void FlyMessenger::on_btnsendmessageuser_clicked()
{
    Widget sendmsg;
    sendmsg.exec();
}
//    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
//                                         tr("User name:"), QLineEdit::Normal,
//                                         QDir::home().dirName(), &ok);
//    QString body = QInputDialog::getText(this, tr("QInputDialog::getText()"),
//                                         tr("Text :"), QLineEdit::Normal,
//                                         QDir::home().dirName(), &ok);

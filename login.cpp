#include "login.h"
#include "ui_login.h"
#include "homepage.h"
#include "flymessenger.h"
#include <cstring>
#include <QSqlQuery>

extern int ret;
extern QString USERN,PASSWOR,TOKEN;
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //    db.setHostName("127.0.0.1");
    //    db.setDatabaseName("project");
    //    db.setUserName("root");
    //    db.setPassword("project3939");
    //    db.open();
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowMinimizeButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowCloseButtonHint);


    ui->txtbPassword->setEchoMode(QLineEdit::Password);
    setWindowIcon(QIcon(":/Icons/login.png"));
    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfin(QNetworkReply*)));
}
Login::~Login()
{
    delete ui;
}

void Login::on_btnCancel_clicked()
{
    this->close();
}

void Login::on_btbLogin_clicked()
{
    QString user;
    QString Passw;
    QByteArray Pass;
    if (! (ui->txtbUserName->text().isEmpty()|| ui->txtbPassword->text().isEmpty() ))
    {
        user=ui->txtbUserName->text();
        Passw=ui->txtbPassword->text();
        QByteArray str;
        QCryptographicHash hasher(QCryptographicHash::Md5);
        hasher.addData(str);
        Pass=hasher.result();
//        qDebug()<<Pass;
        QString link;
        link="http://api.softserver.org:1104/login?username=";
        link.append(user);
        link.append("&password=");
        link.append(Passw);
        request.setUrl(QUrl(link));
        manager->get(request);
    }
    else
    {
        QMessageBox msg;
        msg.setText("Username,password fields are neccessary feilds\nPlease fill them!");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
    }
}

void Login::mfin(QNetworkReply *reply)
{
    QString stt;
    if(reply->error()){
//        qDebug() << reply->errorString ();
        return;
    }
    QByteArray test = reply->readAll ();
    QString st=(QString)reply->readAll();
//    qDebug()<<test;
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();

    if(obj["message"].toString()!="Password is not Correct")
    {
        ret=200;
        USERN=ui->txtbUserName->text();
        PASSWOR=ui->txtbPassword->text();
        TOKEN=obj["token"].toString();
//        qDebug()<<obj["token"].toString();
        QSqlQuery query;
//        qDebug()<<obj;
        QString jsobj(doc.toJson(QJsonDocument::Compact));
//        qDebug()<<jsobj;
        stt.append("INSERT INTO login_token (login,username,password) VALUES ('");
        stt.append(jsobj);
        stt.append("',");
        stt+="'"+USERN+"'"+",'"+PASSWOR+"')";
//        qDebug()<<stt;
        query.prepare(stt);
        query.exec();
//        qDebug()<<query.isValid();
        this->accept();
        //select * from test
        //        INSERT INTO test (id,name) VALUES (10,20)
        //        INSERT INTO data VALUES('{"colour": "white"}','{"colour": "white"}');
        //        SELECT * FROM login_token WHERE JSON_CONTAINS(login, '"you are already loggen int"', '$.message');
        //        SELECT login FROM login_token WHERE JSON_VALUE(login,'$.message.Logged in Successfully') AND username!='';
        //        select * from login_token;
    }
    else
        ui->label->setText("UserName or Password is not Correct");
}

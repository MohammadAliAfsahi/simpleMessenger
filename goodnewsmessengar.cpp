#include "goodnewsmessengar.h"
#include "ui_goodnewsmessengar.h"

#include "homepage.h"
#include "creategroup.h"
#include "createchannel.h"
#include <QInputDialog>
extern QString USERN,PASSWOR,TOKEN;
GoodNewsMessengar::GoodNewsMessengar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GoodNewsMessengar)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Icons/mattermost.png"));
    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfin(QNetworkReply*)));
}

GoodNewsMessengar::~GoodNewsMessengar()
{
    delete ui;
}

void GoodNewsMessengar::on_btnLogout_clicked()
{
    QString link;
    link="http://api.softserver.org:1104/logout?username=";
    link.append(USERN);
    link.append("&password=");
    link.append(PASSWOR);
    request.setUrl(QUrl(link));
    manager->get(request);
}
void GoodNewsMessengar::mfin(QNetworkReply *reply)
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
    if(obj["message"].toString()=="Logged Out Successfully")
    {
        QMainWindow w;
        w.show();
    }
    else if(obj["message"].toString()=="Group Created Successfully")
    {

    }
    else if(obj["message"].toString()== "Channel Created Successfully")
    {

    }
    else if(obj["message"].toString()=="Successfully Joined")//channel
    {
    }
    else if(obj["message"].toString()=="Successfully Joined")//group
    {

    }
    else if(obj["message"].toString()== "Message Sent Successfully")//user
    {

    }
    else if (obj["message"].toString()== "Message Sent Successfully")//group
    {

    }
    else if(obj["message"].toString()== "Message Sent Successfully")//channel
    {

    }
}

void GoodNewsMessengar::on_btnCreateGroup_clicked()
{
    CreateGroup create;
    create.exec();
}

void GoodNewsMessengar::on_btnCreateChannel_clicked()
{

}

void GoodNewsMessengar::on_btnGetIntouches_clicked()
{
    QString link;
    link="http://api.softserver.org:1104/getuserlist?token=";
    link.append(TOKEN);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnGetGroupList_clicked()
{
    QString link;
    link="http://api.softserver.org:1104/getgrouplist?token=";
    link.append(TOKEN);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnGetChannelList_clicked()
{
    QString link;
    link="http://api.softserver.org:1104/getchannellist?token=";
    link.append(TOKEN);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnGetUserChats_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api.softserver.org:1104/getuserchats?token=";
    link.append(TOKEN);
    link.append("&dst=");
    link.append(dst);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnGetGroupChats_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api.softserver.org:1104/getgroupchats?token=";
    link.append(TOKEN);
    link.append("&dst=");
    link.append(dst);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnGetChannelChats_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api.softserver.org:1104/getchannelchats?token=";
    link.append(TOKEN);
    link.append("&dst=");
    link.append(dst);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnJoinGroup_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api:softserver.org:1104/joingroup?token=";
    link.append(TOKEN);
    link.append("&group_name=");
    link.append(dst);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnJoinChannel_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api:softserver.org:1104/joinchannel?token=";
    link.append(TOKEN);
    link.append("&channel_name=");
    link.append(dst);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnsendmessageuser_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    QString body = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Text :"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api.softserver.org:1104/sendmessageuser?token=";
    link.append(TOKEN);
    link.append("&dst=");
    link.append(dst);
    link.append("&body=");
    link.append(body);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnsendmessagegroup_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    QString body = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Text :"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api.softserver.org:1104/sendmessagegroup?token=";
    link.append(TOKEN);
    link.append("&dst=");
    link.append(dst);
    link.append("&body=");
    link.append(body);
    request.setUrl(QUrl(link));
    manager->get(request);
}

void GoodNewsMessengar::on_btnsendmessagechannel_clicked()
{
    QString link;
    QString dst;
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    QString body = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("Text :"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        dst=text;
    link="http://api.softserver.org:1104/sendmessagechannel?token=";
    link.append(TOKEN);
    link.append("&dst=");
    link.append(dst);
    link.append("&body=");
    link.append(body);
    request.setUrl(QUrl(link));
    manager->get(request);
}

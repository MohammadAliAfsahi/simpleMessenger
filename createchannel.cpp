#include "createchannel.h"
#include "ui_createchannel.h"

extern QString TOKEN;
CreateChannel::CreateChannel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateChannel)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfin(QNetworkReply*)));
    setWindowIcon(QIcon(":/Icons/user (2).png"));
    setWindowTitle("Create Group");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowMinimizeButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowCloseButtonHint);
}

CreateChannel::~CreateChannel()
{
    delete ui;
}
void CreateChannel::mfin(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        qDebug() << reply->errorString ();
         ui->label->setText(reply->errorString ());
        return;
    }
    QByteArray test = reply->readAll ();
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    if(obj["message"].toString()== "Channel Created Successfully")
    {
        this->accept();
    }
    else
    {
        ui->label->setText("Something went Wrong!");
    }
}

void CreateChannel::on_btnCancel_clicked()
{
    this->close();
}

void CreateChannel::on_btnCreate_clicked()
{

    QString link;
    link="http://api.softserver.org:1104/createchannel?token=";
    link.append(TOKEN);
    link.append("&channel_name=");
    link.append(ui->txtbName->text());
    link.append("&channel_title=");
    link.append(ui->txtbTitle->text());
//    qDebug()<<link;
    request.setUrl(QUrl(link));
    manager->get(request);
}

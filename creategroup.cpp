#include "creategroup.h"
#include "ui_creategroup.h"

extern QString TOKEN;
CreateGroup::CreateGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGroup)
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

CreateGroup::~CreateGroup()
{
    delete ui;
}

void CreateGroup::mfin(QNetworkReply *reply)
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
    if(obj["message"].toString()=="Group Created Successfully")
    {
        this->accept();
    }
    else
    {
        ui->label->setText("Something went Wrong!");
    }
}

void CreateGroup::on_btnCreate_clicked()
{
    QString link;
    link="http://api.softserver.org:1104/creategroup?token=";
    link.append(TOKEN);
    link.append("&group_name=");
    link.append(ui->txtbName->text());
    link.append("&group_title=");
    link.append(ui->txtbTitle->text());
    request.setUrl(QUrl(link));
    manager->get(request);
}

void CreateGroup::on_btnCancel_clicked()
{
    this->close();
}

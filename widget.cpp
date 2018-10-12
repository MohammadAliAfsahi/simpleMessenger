#include "widget.h"
#include "ui_widget.h"
#include <QInputDialog>
#include <QTextStream>
#include <QTcpSocket>
#include <sstream>
#include <string>
#include <QObject>
#include <windows.h>
#include <QtConcurrent>
#include <QIODevice>

extern QString USERN,PASSWOR,TOKEN;
extern int ret;
using namespace std;
Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->Name->setPlaceholderText("Fill this feild");
    ui->Messege->setPlaceholderText("Please Enter your message here!");
    setWindowIcon(QIcon(":/Icons/mattermost.png"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowMinimizeButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowCloseButtonHint);


    manager = new QNetworkAccessManager();
    managerjg = new QNetworkAccessManager();
    managerjc = new QNetworkAccessManager();

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfin(QNetworkReply*)));
    connect(managerjg,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinjg(QNetworkReply*)));
    connect(managerjc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinjc(QNetworkReply*)));

    managersum = new QNetworkAccessManager();
    managerscm = new QNetworkAccessManager();
    managersgm = new QNetworkAccessManager();


    connect(managerscm,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinscm(QNetworkReply*)));
    connect(managersgm,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinsgm(QNetworkReply*)));
    connect(managersum,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinsum(QNetworkReply*)));


    managerggl = new QNetworkAccessManager();
    managergcl = new QNetworkAccessManager();
    managergul = new QNetworkAccessManager();


    connect(managerggl,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinggl(QNetworkReply*)));
    connect(managergcl,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfingcl(QNetworkReply*)));
    connect(managergul,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfingul(QNetworkReply*)));

    managerguc = new QNetworkAccessManager();
    managerggc = new QNetworkAccessManager();
    managergcc = new QNetworkAccessManager();


    connect(managerguc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinguc(QNetworkReply*)));
    connect(managerggc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfinggc(QNetworkReply*)));
    connect(managergcc,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfingcc(QNetworkReply*)));


    QGridLayout *g =new QGridLayout;
    ui->scrollArea->widget()->setLayout(g);



    create_list();
    CreateMenus();
    createActions();

    timer2=new QTimer();
    connect(timer2,SIGNAL(timeout()),this,SLOT(RealTimeMessege()));
    timer2->start(1000);
}
void Widget::startrequestList(const QUrl &requestedurl)
{
    RealTimelist = RealTimeRequestlist->get(QNetworkRequest(requestedurl));
    connect(RealTimelist,SIGNAL(&QIODevice::readyRead),this,SLOT(Get_messages()));
    connect(RealTimelist,SIGNAL(&QNetworkReply::finished),this,SLOT(Get_messages()));
}

void Widget::startrequestmessege(const QUrl &requestedurl)
{
    RealTimemessege = RealTimeRequestmessege->get(QNetworkRequest(requestedurl));
    connect(RealTimemessege,SIGNAL(&QIODevice::readyRead),this,SLOT(Get_messages()));
    connect(RealTimemessege,SIGNAL(&QNetworkReply::finished),this,SLOT(Get_messages()));
}

void Widget::set()
{
    moveToThread(&cThread);
    connect(&cThread,SIGNAL(started()),this,SLOT(checkConnection()));
    cThread.start();

}

void Widget::RealTimeList()
{
    create_list();
}

Widget::~Widget()
{
    cThread.terminate();
    delete ui;
}

void Widget::onNetworkStateChanged(bool isOnline)
{
    qDebug()<<"isOnline: "<<isOnline;
    if(isOnline)
        ui->connection->setText("");
    else
        ui->connection->setText("No Internet connection");
}

void Widget::checkConnection()
{ 
    connect(&ncm, SIGNAL(onlineStateChanged(bool)), this, SLOT(onNetworkStateChanged(bool)));

    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if(reply->bytesAvailable())
        ui->connection->setText("");
    else
        ui->connection->setText("No Internet connection");

}

bool Widget::check_internet()
{
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("http://www.google.com"));
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if(reply->bytesAvailable())
       return true;
    else
        return false;
}
void Widget::RealTimeMessege()
{
    Get_messages();
}

void Widget::on_Submit_clicked()
{
    QString link;
    QString dst,body;
    if (!ui->Name->text().isEmpty() && !ui->Messege->text().isEmpty())
    {
        if(ui->lblname->text()=="UserName")
        {
            dst=ui->Name->text();
            dst.replace("'","\'");
            body=ui->Messege->text();
            link="http://api.softserver.org:1104/sendmessageuser?token=";
            link.append(TOKEN);
            link.append("&dst=");
            link.append(dst);
            link.append("&body=");
            link.append(body);
            request.setUrl(QUrl(link));
            managersum->get(request);
        }
        else if(ui->lblname->text()=="GroupName")
        {
            dst=ui->Name->text();
            body=ui->Messege->text();
            link="http://api.softserver.org:1104/sendmessagegroup?token=";
            link.append(TOKEN);
            link.append("&dst=");
            link.append(dst);
            link.append("&body=");
            link.append(body);
            request.setUrl(QUrl(link));

            managersgm->get(request);
        }
        else if(ui->lblname->text()=="ChannelName")
        {
            link="http://api.softserver.org:1104/sendmessagechannel?token=";
            link.append(TOKEN);
            link.append("&dst=");
            link.append(dst);
            link.append("&body=");
            link.append(body);
            request.setUrl(QUrl(link));

            managerscm->get(request);
        }
    }
    else if(ui->Name->text().isEmpty())
    {
        ui->Name->setPlaceholderText("Please Enter username!");
    }
    else if(ui->Messege->text().isEmpty())
    {
        ui->Messege->setPlaceholderText("Please Enter some text to send!");
    }
}

void Widget::create_list()
{

    if(ui->scrollArea->widget()->layout()->count()>0)
    {
        QLayoutItem *item = NULL;
        while ((item = ui->scrollArea->widget()->layout()->takeAt(0)) != 0)
        {
            delete item->widget();
        }
    }
    QString link;
    link="http://api.softserver.org:1104/getuserlist?token=";
    link.append(TOKEN);
    request.setUrl(QUrl(link));
    managergul->get(request);

    //    Sleep(2000);
    link.clear();

    link="http://api.softserver.org:1104/getgrouplist?token=";
    link.append(TOKEN);
    request.setUrl(QUrl(link));
    managerggl->get(request);

    link.clear();

    link="http://api.softserver.org:1104/getchannellist?token=";
    link.append(TOKEN);
    request.setUrl(QUrl(link));
    managergcl->get(request);
}

void Widget::onCreateGroupclicked()
{
    CreateGroup create;
    if(create.exec())
    {
        create_list();
    }
}

void Widget::onCreateChannelclicked()
{
    CreateChannel create;
    if(create.exec())
    {
        create_list();
    }
}

void Widget::onbtnJoinGroupclicked()
{
    QString link;
    QString dst;
    bool ok=false;
    QString text;
    while(text.isEmpty())
    {
        text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                     tr("Group name:"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);
        if(ok==false)
            return;
    }
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api.softserver.org:1104/joingroup?token=";
    link.append(TOKEN);
    link.append("&group_name=");
    link.append(dst);
    request.setUrl(QUrl(link));
    managerjg->get(request);
}

void Widget::onJoinChannelclicked()
{
    QString link;
    QString dst;
    bool ok=false;
    QString text;
    while(text.isEmpty())
    {
        text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                     tr("Channel name:"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);
        if(ok==false)
            return;
    }
    if (ok && !text.isEmpty())
        dst=text;

    link="http://api.softserver.org:1104/joinchannel?token=";
    link.append(TOKEN);
    link.append("&channel_name=");
    link.append(dst);
    request.setUrl(QUrl(link));
    managerjc->get(request);
}

void Widget::Qbtnclicked()
{

    QObject *senderObj = sender(); // This will give Sender object
    QString senderObjName = senderObj->objectName();

    ui->Name->setText(senderObjName);

    QPushButton *b = qobject_cast<QPushButton *> (sender());

    if(b->accessibleName()=="group")
    {
        ui->lblname->setText("GroupName");
        Get_messages();
    }
    else if(b->accessibleName()=="user")
    {
        ui->lblname->setText("UserName");
        Get_messages();
    }
    else if(b->accessibleName()=="channel")
    {
        ui->lblname->setText("ChannelName");
        Get_messages();
    }
}

void Widget::CreateMenus()
{
    menuBar=new QMenuBar;

    fileMenu = new QMenu(tr("&Create"), this);
    CGAct = fileMenu->addAction(tr("Group"));
    menuBar->addMenu(fileMenu);
    CCAct = fileMenu->addAction(tr("Channel"));
    menuBar->addMenu(fileMenu);

    editMenu = new QMenu(tr("&Join"),  this);
    JGAct = editMenu->addAction(tr("Group"));
    menuBar->addMenu(editMenu);
    JCAct = editMenu->addAction(tr("Channel"));
    menuBar->addMenu(editMenu);
    ui->gridLayout->setMenuBar(menuBar);
    // ui->horizontalLayout_4->setMenuBar(menuBar);
    //ui->horizontalLayout_4->setGeometry(QRect(0,0,100,20));
    //ui->horizontalLayout_3->setGeometry(QRect(0,0,100,20));

    //    fileMenu = menuBar()->addMenu(tr("&Create"));
    //    fileMenu->addAction(CGAct);
    //    fileMenu->addAction(CCAct);
    //    editMenu = layout()->menuBar()->addMenu(tr("&Join"));
    //    editMenu->addAction(JGAct);
    //    editMenu->addAction(JCAct);
}

void Widget::createActions()
{
    connect(CGAct, SIGNAL(triggered()), this,SLOT(onCreateGroupclicked()));


    connect(CCAct, SIGNAL(triggered()), this, SLOT(onCreateChannelclicked()));


    connect(JGAct, SIGNAL(triggered()), this, SLOT(onbtnJoinGroupclicked()));


    connect(JCAct, SIGNAL(triggered()), this,SLOT(onJoinChannelclicked()));
}

void Widget::mfinsum(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
                qDebug() << reply->errorString ();
        return;
    }
    QByteArray test = reply->readAll ();
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    if(obj["message"].toString()== "Message Sent Successfully")
    {
        ui->textEdit->append(USERN+": "+ui->Messege->text());
        ui->Messege->clear();
    }
    else
    {
        //check your connection
    }

}

void Widget::mfinscm(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        return;
    }
    QByteArray test = reply->readAll ();
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    if(obj["message"].toString()== "Message Sent Successfully")
    {
        ui->textEdit->setText(USERN+": "+ui->Messege->text());
        ui->Messege->clear();
    }
    else
    {

    }

}

void Widget::mfinsgm(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        return;
    }
    QByteArray test = reply->readAll ();
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    if(obj["message"].toString()== "Message Sent Successfully")
    {
        ui->textEdit->setText(USERN+": "+ui->Messege->text());
        ui->Messege->clear();
    }
    else
    {
    }
}

void Widget::mfinggl(QNetworkReply *reply)
{
    QString s;
    QByteArray test = reply->readAll ();
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();

    QString jsobj(doc.toJson(QJsonDocument::Compact));
    if(reply->error()){
        if(reply->errorString()!="Host api.softserver.org not found")
            return;
    }
    if(reply->errorString()=="Host api.softserver.org not found")
    {
        query.exec("SELECT * FROM lists WHERE JSON_CONTAINS(GetGroupLists, '\"200\"', '$.code')");
        while(query.next())
        {
            if(query.value(1).toByteArray()!=NULL)
            {
                temp=query.value(1).toByteArray();
                if(temp!=NULL)
                {
                    doc=QJsonDocument::fromJson(temp);
                    obj=doc.object();
                }
            }
        }
        if(obj["message"].toString()!="")
        {
            string str=obj["message"].toString().toStdString();
            string garbage;
            QString str2=obj["message"].toString();
            int h=12;
            QString nom;
            while(str2[h]!="-")
            {
                nom+= str[h];
                h++;
            }
            int no=nom.toInt();
            QString block;
            int y=40;
            for(size_t i=0;i<no;i++)
            {
                block.append("block ");
                block.append(QString::number(i));
                button= new QPushButton(obj[block].toObject()["group_name"].toString());
                button->setStyleSheet("border:none;"
                                      "border-radius:5px;"
                                      "color:#a62af9;");
                button->setCursor(Qt::PointingHandCursor);
                button->setVisible(true);

                button->setText(obj[block].toObject()["group_name"].toString());

                button->setAccessibleName("group");
                button->setGeometry(14,y,121,31);y+=35;
                ui->scrollArea->widget()->layout()->addWidget(button);


                button->setObjectName(obj[block].toObject()["group_name"].toString());

                button->setIcon(QIcon(":/Icons/group.png"));
                button->setIconSize(QSize(25,16));


                listButtonsG.push_back(button);
                connect(listButtonsG.at(i),SIGNAL(clicked()),this,SLOT(Qbtnclicked()));

                block.clear();
            }

        }
    }
    else
    {
        ui->scrollArea->widget()->clearMask();
        query.clear();
        stt.clear();
        QString namequery= "UPDATE lists SET GetGroupLists = NULL";

        query.exec(namequery);

        stt.clear();
        query.clear();
        jsobj.replace("'","\\'");
        stt.append("INSERT INTO lists (GetGroupLists) VALUES ('");
        stt.append(jsobj);
        stt+="')";
        query.prepare(stt);
        query.exec();

        stt.clear();
        query.clear();

        query.exec("SELECT * FROM lists WHERE JSON_CONTAINS(GetGroupLists, '\"200\"', '$.code')");
        while(query.next())
        {
            //        qDebug()<<query.value(0).toString();
            if(query.value(1).toByteArray()!=NULL)
            {
                temp=query.value(1).toByteArray();
                if(temp!=NULL)
                {
                    doc=QJsonDocument::fromJson(temp);
                    obj=doc.object();
                }
            }
        }

        string str=obj["message"].toString().toStdString();
        string garbage;
        QString str2=obj["message"].toString();
        int h=12;
        QString nom;
        while(str2[h]!="-")
        {
            nom+= str[h];
            h++;
        }
        int no=nom.toInt();
        qDebug()<<no;
        QString block;
        int y=40;
        listButtonsG.clear();
        for(size_t i=0;i<no;i++)
        {
            block.append("block ");
            block.append(QString::number(i));
            button= new QPushButton(obj[block].toObject()["group_name"].toString());
            button->setStyleSheet("border:none;"
                                  "border-radius:5px;"
                                  "color:#a62af9;");
            button->setCursor(Qt::PointingHandCursor);
            button->setVisible(true);


            button->setText(obj[block].toObject()["group_name"].toString());

            button->setAccessibleName("group");
            button->setGeometry(14,y,121,31);y+=35;

            ui->scrollArea->widget()->layout()->addWidget(button);



            button->setObjectName(obj[block].toObject()["group_name"].toString());

            button->setIcon(QIcon(":/Icons/group.png"));
            button->setIconSize(QSize(25,16));


            listButtonsG.push_back(button);
            connect(listButtonsG.at(i),SIGNAL(clicked()),this,SLOT(Qbtnclicked()));

            block.clear();
        }

    }
    query.clear();
    stt.clear();
}

void Widget::mfingcl(QNetworkReply *reply)
{
    QString s;
    QByteArray test = reply->readAll ();
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();


    QString jsobj(doc.toJson(QJsonDocument::Compact));
    if(reply->error())
    {
        if(reply->errorString()!="Host api.softserver.org not found")
            return;
    }
    if(reply->errorString()=="Host api.softserver.org not found")
    {
        query.exec("SELECT * FROM lists WHERE JSON_CONTAINS(GetChannelLists, '\"200\"', '$.code')");
        while(query.next())
        {
            if(query.value(2).toByteArray()!=NULL)
            {
                temp=query.value(2).toByteArray();
                if(temp!=NULL)
                {
                    doc=QJsonDocument::fromJson(temp);
                    obj=doc.object();
                }
            }
        }
        if(obj["message"].toString()!="")
        {
            string str=obj["message"].toString().toStdString();
            string garbage;
            QString str2=obj["message"].toString();
            int h=12;
            QString nom;
            while(str2[h]!="-")
            {
                nom+= str[h];
                h++;
            }
            int no=nom.toInt();

            //    qDebug()<<no;
            QString block;
            int y=40;
            for(size_t i=0;i<no;i++)
            {
                //        qDebug()<<i;
                block.append("block ");
                block.append(QString::number(i));
                //        qDebug()<<block;
                //        qDebug()<<obj[block].toObject()["channel_name"].toString();
                //        button->setText(obj[block][0]["group_name"].toString());
                button= new QPushButton(obj[block].toObject()["channel_name"].toString());
                button->setStyleSheet("border:none;"
                                      "border-radius:5px;"
                                      "color:#a62af9;");
                button->setCursor(Qt::PointingHandCursor);
                button->setVisible(true);

                button->setText(obj[block].toObject()["channel_name"].toString());
                ui->scrollArea->widget()->layout()->addWidget(button);
                button->setAccessibleName("channel");
                button->setGeometry(14,y,121,31);y+=35;
                //        button->layout()->addWidget(button);

                //        connect(button,SIGNAL(clicked()),mapper,SLOT(Qbtnclicked()) );
                button->setObjectName(obj[block].toObject()["channel_name"].toString());
                button->setIcon(QIcon(":/Icons/megaphone.png"));
                button->setIconSize(QSize(25,16));

                listButtonsC.push_back(button);
                connect(listButtonsC.at(i),SIGNAL(clicked()), this,SLOT(Qbtnclicked()));


                block.clear();
            }
        }
    }
    else
    {
        ui->scrollArea->widget()->clearMask();
        query.clear();
        stt.clear();
        QString namequery= "UPDATE lists SET GetChannelLists = NULL";

        query.exec(namequery);
        jsobj.replace("'","\\'");
        stt.append("INSERT INTO lists (GetChannelLists) VALUES ('");
        stt.append(jsobj);
        stt+="')";

        query.prepare(stt);
        query.exec();

        stt.clear();
        query.clear();

        query.exec("SELECT * FROM lists WHERE JSON_CONTAINS(GetChannelLists, '\"200\"', '$.code')");
        while(query.next())
        {
            //        qDebug()<<query.value(0).toString();
            if(query.value(2).toByteArray()!=NULL)
            {
                temp=query.value(2).toByteArray();
                if(temp!=NULL)
                {
                    doc=QJsonDocument::fromJson(temp);
                    obj=doc.object();
                }
            }
        }
        string str=obj["message"].toString().toStdString();
        string garbage;
        QString str2=obj["message"].toString();
        int h=12;
        QString nom;
        while(str2[h]!="-")
        {
            nom+= str[h];
            h++;
        }
        int no=nom.toInt();
        //    qDebug()<<no;
        QString block;
        int y=40;
        listButtonsC.clear();
        for(size_t i=0;i<no;i++)
        {
            //        qDebug()<<i;
            block.append("block ");
            block.append(QString::number(i));
            //        qDebug()<<block;
            //        qDebug()<<obj[block].toObject()["channel_name"].toString();
            //        button->setText(obj[block][0]["group_name"].toString());
            button= new QPushButton(obj[block].toObject()["channel_name"].toString());
            button->setStyleSheet("border:none;"
                                  "border-radius:5px;"
                                  "color:#a62af9;");
            button->setCursor(Qt::PointingHandCursor);;
            button->setVisible(true);

            button->setText(obj[block].toObject()["channel_name"].toString());


            //            if(ui->scrollArea->widget()->layout()->count()>0)
            //             {
            //                ui->scrollArea->takeWidget();
            //                ui->scrollArea->setWidget(button);
            //            }
            //            else
            ui->scrollArea->widget()->layout()->addWidget(button);

            button->setAccessibleName("channel");
            button->setGeometry(14,y,121,31);y+=35;


            //        connect(button,SIGNAL(clicked()),mapper,SLOT(Qbtnclicked()) );
            button->setObjectName(obj[block].toObject()["channel_name"].toString());
            button->setIcon(QIcon(":/Icons/megaphone.png"));
            button->setIconSize(QSize(25,16));

            listButtonsC.push_back(button);
            connect(listButtonsC.at(i),SIGNAL(clicked()), this,SLOT(Qbtnclicked()));


            block.clear();
        }

    }
    stt.clear();
    query.clear();
}

void Widget::mfingul(QNetworkReply *reply)
{
    QString s;
    QByteArray test = reply->readAll ();
    //    qDebug()<<test;
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    //    qDebug()<<obj["message"].toString();
    //"You Chat With -0- User"
    QString jsobj(doc.toJson(QJsonDocument::Compact));
    if(reply->error())
    {
        qDebug() << reply->errorString ();
        if(reply->errorString()!="Host api.softserver.org not found")
            return;
    }
    if(reply->errorString()=="Host api.softserver.org not found")
    {
        query.exec("SELECT * FROM lists WHERE JSON_CONTAINS(GetUserLists, '\"200\"', '$.code')");
        while(query.next())
        {
            qDebug()<<query.value(0).toString();
            if(query.value(0).toByteArray()!=NULL)
            {
                temp=query.value(0).toByteArray();
                if(temp!=NULL)
                {
                    doc=QJsonDocument::fromJson(temp);
                    obj=doc.object();
                }
            }
        }
        if(obj["message"].toString()!="")
        {
            string str=obj["message"].toString().toStdString();
            string garbage;
            QString str2=obj["message"].toString();
            int h=20;
            QString nom;
            while(str2[h]!="-")
            {
                nom+= str[h];
                h++;
            }
            int no=nom.toInt();
            //    qDebug()<<no;
            QString block;
            int y =40;
            for(size_t i=0;i<no;i++)
            {
                //        qDebug()<<i;
                block.append("block ");
                block.append(QString::number(i));
                //        qDebug()<<block;
                //        qDebug()<<obj[block].toObject()["src"].toString();
                //        button->setText(obj[block][0]["group_name"].toString());
                button= new QPushButton(obj[block].toObject()["src"].toString());
                button->setStyleSheet("border:none;"
                                      "border-radius:5px;"
                                      "color:#a62af9;");
                button->setCursor(Qt::PointingHandCursor);
                button->setVisible(true);


                button->setText(obj[block].toObject()["src"].toString());
                ui->scrollArea->widget()->layout()->addWidget(button);
                button->setAccessibleName("user");
                button->setGeometry(14,y,121,31);y+=35;
                button->setObjectName(obj[block].toObject()["src"].toString());
                //        connect(button, &QPushButton::clicked, [=] { Qbtnclicked(); });

                button->setIcon(QIcon(":/Icons/user.png"));
                button->setIconSize(QSize(25,16));

                listButtonsU.push_back(button);
                connect(listButtonsU.at(i),SIGNAL(clicked()),this,SLOT(Qbtnclicked()));
                //button->layout()->addWidget(button);
                block.clear();
                //        ui->scrollAreaWidgetContents->layout()->addWidget(button);
            }
        }
    }
    else
    {
        ui->scrollArea->widget()->clearMask();
        query.clear();
        stt.clear();
        QString namequery= "UPDATE lists SET GetUserLists = NULL";

        query.exec(namequery);
        query.clear();

        stt.clear();
        jsobj.replace("'","\\'");
        query.clear();

        stt.append("INSERT INTO lists (GetUserLists) VALUES ('");
        stt.append(jsobj);
        stt+="')";

        query.prepare(stt);
        query.exec();

        stt.clear();
        query.clear();

        query.exec("SELECT * FROM lists WHERE JSON_CONTAINS(GetUserLists, '\"200\"', '$.code')");
        while(query.next())
        {
            //        qDebug()<<query.value(0).toString();
            if(query.value(0).toByteArray()!=NULL)
            {
                temp=query.value(0).toByteArray();
                if(temp!=NULL)
                {
                    doc=QJsonDocument::fromJson(temp);
                    obj=doc.object();
                }
            }
        }

        string str=obj["message"].toString().toStdString();
        string garbage;
        QString str2=obj["message"].toString();
        int h=20;
        QString nom;
        while(str2[h]!="-")
        {
            nom+= str[h];
            h++;
        }
        int no=nom.toInt();
        //    qDebug()<<no;
        QString block;
        int y =40;
        listButtonsU.clear();
        for(size_t i=0;i<no;i++)
        {
            //        qDebug()<<i;
            block.append("block ");
            block.append(QString::number(i));
            //        qDebug()<<block;
            //        qDebug()<<obj[block].toObject()["src"].toString();
            //        button->setText(obj[block][0]["group_name"].toString());
            button= new QPushButton(obj[block].toObject()["src"].toString());
            button->setStyleSheet("border:none;"
                                  "border-radius:5px;"
                                  "color:#a62af9;");
            button->setCursor(Qt::PointingHandCursor);
            button->setVisible(true);


            button->setText(obj[block].toObject()["src"].toString());
            button->setAccessibleName("user");
            button->setGeometry(14,y,121,31);y+=35;
            button->setObjectName(obj[block].toObject()["src"].toString());
            //        connect(button, &QPushButton::clicked, [=] { Qbtnclicked(); });

            button->setIcon(QIcon(":/Icons/user.png"));
            button->setIconSize(QSize(25,16));

            listButtonsU.push_back(button);


            //            if(ui->scrollArea->widget()->layout()->count()>0)
            //             {
            //                ui->scrollArea->takeWidget();
            //                ui->scrollArea->setWidget(button);
            //            }
            //            else
            ui->scrollArea->widget()->layout()->addWidget(button);

            connect(listButtonsU.at(i),SIGNAL(clicked()),this,SLOT(Qbtnclicked()));

            //button->layout()->addWidget(button);
            block.clear();
            //        ui->scrollAreaWidgetContents->layout()->addWidget(button);
        }
    }
    stt.clear();
    query.clear();
}

void Widget::Get_messages()
{
    QString link;
    QString dst;
    QDate current(QDate::currentDate());
    current.addMonths(-6).toString("yyyyMMdd");
    QString day= QString::number(current.day());
    QString month = QString::number(current.month());
    QString year = QString::number(current.year());
    //    qDebug()<<year<<month<<day;
    //    qDebug()<<current.addMonths(-6).toString("yyyyMMdd");
    QDateTime curtime(QDateTime::currentDateTime());
    //    qDebug()<<curtime.toString("HHmmss");

    dst=ui->Name->text();
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

void Widget::mfinguc(QNetworkReply *reply)
{
    QString s;
    QJsonDocument doc;
    QJsonObject obj;
    QString stt;
    QSqlQuery query;
    QByteArray test = reply->readAll ();
    QString name=ui->Name->text();
    //    qDebug()<<test;
    if(reply->error())
    {
//        if(reply->errorString()!="Host api.softserver.org not found")
//            return;
    }
    //if(reply->errorString()=="Host api.softserver.org not found")
    if(!check_internet())
    {
        //        query.exec("SELECT * FROM chat WHERE JSON_CONTAINS(messagesU, '\"200\"', '$.code')");

        QString q="SELECT * FROM chat WHERE JSON_CONTAINS(messagesU,'\""+name+"\"' ,'$.block 0.dst')";
        query.exec(q);
        while(query.next())
        {
            temp=query.value(2).toByteArray();
            if(temp!=NULL)
            {
                doc=QJsonDocument::fromJson(temp);
                obj=doc.object();
            }
        }
        if(obj["message"].toString()!="")
        {
            QString number= obj["message"].toString();
            QString str2=obj["message"].toString();
            int h=11;
            QString nom;
            while(str2[h]!="-")
            {
                nom+= str2[h];
                h++;
            }
            int no=nom.toInt();
            ui->textEdit->clear();
            for(int i=0;i<no;i++)
            {
                QString block= "block "+QString::number(i);
                if(obj[block].toObject()["dst"].toString()==ui->Name->text() || obj[block].toObject()["src"].toString()==ui->Name->text() )
                    ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());
            }
        }
        else
            ui->textEdit->clear();
    }
    else
    {

        name.replace("'","\'");
        QString namequery= "DELETE FROM chat WHERE JSON_CONTAINS(messagesU,'\""+name+"\"' ,'$.block 0.dst')";
        query.exec(namequery);
        query.clear();

        doc = QJsonDocument::fromJson(test);
        obj=doc.object();
        QString jsobj(doc.toJson(QJsonDocument::Compact));
        jsobj.replace("'","\\'");

        stt.clear();
        query.clear();
        stt.append("INSERT INTO chat (messagesU) VALUES ('");
        stt.append(jsobj);
        stt+="')";
        query.prepare(stt);
        query.exec();
        stt.clear();
        query.clear();

        QString q="SELECT * FROM chat WHERE JSON_CONTAINS(messagesU,'\""+name+"\"' ,'$.block 0.dst')";
        query.exec(q);
        while(query.next())
        {
            //        qDebug()<<query.value(0).toString();
            temp=query.value(2).toByteArray();
            if(temp!=NULL)
            {
                doc=QJsonDocument::fromJson(temp);
                obj=doc.object();
            }
        }
        if(obj["message"].toString()!="")
        {
            QString number= obj["message"].toString();
            QString str2=obj["message"].toString();
            int h=11;
            QString nom;
            while(str2[h]!="-")
            {
                nom+= str2[h];
                h++;
            }
            int no=nom.toInt();
            ui->textEdit->clear();
            for(int i=0;i<no;i++)
            {
                QString block= "block "+QString::number(i);
                if(obj[block].toObject()["dst"].toString()==ui->Name->text() || obj[block].toObject()["src"].toString()==ui->Name->text() )
                    ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());
                //        else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
            }
        }
        else
            ui->textEdit->clear();
    }
}

void Widget::mfinggc(QNetworkReply *reply)
{
    QString s;
    if(reply->error())
    {
    }
    QByteArray test = reply->readAll ();
    QJsonDocument doc;
    QJsonObject obj;
    QString stt;
    QSqlQuery query;
    QString name=ui->Name->text();
    if(!check_internet())
    {
        //    qDebug()<<test;
        //        query.exec("SELECT * FROM chat WHERE JSON_CONTAINS(messagesG, '\"200\"', '$.code')");
        query.exec("SELECT * FROM chat WHERE JSON_CONTAINS(messagesG,'\""+name+"\"' ,'$.block 0.dst')");

        while(query.next())
        {
            //        qDebug()<<query.value(0).toString();
            temp=query.value(0).toByteArray();
            if(temp!=NULL)
            {
                doc=QJsonDocument::fromJson(temp);
                obj=doc.object();
            }
        }
        if(obj["message"].toString()!="")
        {
            QString number= obj["message"].toString();
            QString str2=obj["message"].toString();
            int h=11;
            QString nom;
            while(str2[h]!="-")
            {
                nom+= str2[h];
                h++;
            }
            int no=nom.toInt();
            ui->textEdit->clear();
            for(int i=0;i<no;i++)
            {
                QString block= "block "+QString::number(i);

                if(obj[block].toObject()["dst"].toString()==ui->Name->text())
                    ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());
                //                else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
            }
        }
        else
            ui->textEdit->clear();
    }
    else
    {
        doc = QJsonDocument::fromJson(test);
        obj=doc.object();
        //    qDebug()<<obj["message"].toString();
        //    qDebug()<<no;
        QString jsobj(doc.toJson(QJsonDocument::Compact));
        jsobj.replace("'","\\'");
        stt.clear();
        query.clear();

        QString namequery= "DELETE FROM chat WHERE JSON_CONTAINS(messagesG,'\""+name+"\"' ,'$.block 0.dst')";

        query.exec(namequery);
        query.clear();

        stt.append("INSERT INTO chat (messagesG) VALUES ('");
        stt.append(jsobj);
        stt+="')";
        //    qDebug()<<stt;
        query.prepare(stt);
        query.exec();

        stt.clear();
        query.clear();

        QString q="SELECT * FROM chat WHERE JSON_CONTAINS(messagesG,'\""+name+"\"' ,'$.block 0.dst')";
        query.exec(q);
        while(query.next())
        {
            //        qDebug()<<query.value(0).toString();
            temp=query.value(0).toByteArray();
            if(temp!=NULL)
            {
                doc=QJsonDocument::fromJson(temp);
                obj=doc.object();
            }
        }
        if(obj["message"].toString()!="")
        {
            QString number= obj["message"].toString();
            QString str2=obj["message"].toString();
            int h=11;
            QString nom;
            while(str2[h]!="-")
            {
                nom+= str2[h];
                h++;
            }
            int no=nom.toInt();
            ui->textEdit->clear();
            for(int i=0;i<no;i++)
            {
                QString block= "block "+QString::number(i);

                if(obj[block].toObject()["dst"].toString()==ui->Name->text())
                    ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());
                //                else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
            }
        }
        else
            ui->textEdit->clear();
    }

}

void Widget::mfingcc(QNetworkReply *reply)
{
    QString s;
    if(reply->error())
    {

    }

    QByteArray test = reply->readAll ();
    QJsonDocument doc;
    QJsonObject obj;
    QString stt;
    QSqlQuery query;
    QString name=ui->Name->text();
    if(!check_internet())
    {
        query.exec("SELECT * FROM chat WHERE JSON_CONTAINS(messagesC,'\""+name+"\"' ,'$.block 0.dst')");
        while(query.next())
        {
            temp=query.value(1).toByteArray();
            if(temp!=NULL)
            {
                doc=QJsonDocument::fromJson(temp);
                obj=doc.object();
            }
        }
        if(obj["message"].toString()!="")
        {
            QString number= obj["message"].toString();
            QString str2=obj["message"].toString();
            int h=11;
            QString nom;
            while(str2[h]!="-")
            {
                nom+= str2[h];
                h++;
            }
            int no=nom.toInt();
            ui->textEdit->clear();
            for(int i=0;i<no;i++)
            {
                QString block= "block "+QString::number(i);

                if(obj[block].toObject()["dst"].toString()==ui->Name->text())
                    ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());
            }
        }
        else
            ui->textEdit->clear();
    }
    else
    {
        doc = QJsonDocument::fromJson(test);
        obj=doc.object();

        QString namequery= "DELETE FROM chat WHERE JSON_CONTAINS(messagesC,'\""+name+"\"' ,'$.block 0.dst')";

        query.exec(namequery);
        query.clear();
        QString jsobj(doc.toJson(QJsonDocument::Compact));
        jsobj.replace("'","\\'");
        stt.append("INSERT INTO chat (messagesC) VALUES ('");
        stt.append(jsobj);
        stt+="')";
        query.prepare(stt);
        query.exec();

        stt.clear();
        query.clear();

        QString q="SELECT * FROM chat WHERE JSON_CONTAINS(messagesC,'\""+name+"\"' ,'$.block 0.dst')";
        query.exec(q);
        while(query.next())
        {
            temp=query.value(1).toByteArray();
            if(temp!=NULL)
            {
                doc=QJsonDocument::fromJson(temp);
                obj=doc.object();
            }
        }
        if(obj["message"].toString()!="")
        {
            QString number= obj["message"].toString();
            QString str2=obj["message"].toString();
            int h=11;
            QString nom;
            while(str2[h]!="-")
            {
                nom+= str2[h];
                h++;
            }
            int no=nom.toInt();
            ui->textEdit->clear();
            for(int i=0;i<no;i++)
            {
                QString block= "block "+QString::number(i);

                if(obj[block].toObject()["dst"].toString()==ui->Name->text())
                    ui->textEdit->append(obj[block].toObject()["src"].toString()+" : "+obj[block].toObject()["body"].toString());
                //                else if (obj[block]["dst"].toString()==) --> if dst was another user and src was the user
            }
        }
        else
            ui->textEdit->clear();
    }
}

void Widget::mfin(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        return;
    }
    QByteArray test = reply->readAll ();
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    if(obj["message"].toString()=="Logged Out Successfully")
    {
        ret=0;
        QSqlQuery query;
        query.exec("DELETE FROM login_token");
        WellcomePage sh;
        this->close();
        sh.exec();

    }
}

void Widget::mfinjg(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        return;
    }
    QByteArray test = reply->readAll ();
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    if(obj["message"].toString()== "Successfully Joined")
    {
        create_list();
    }
    else
    {
    }
}

void Widget::mfinjc(QNetworkReply *reply)
{
    QString s;
    if(reply->error()){
        return;
    }
    QByteArray test = reply->readAll ();
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
    if(obj["message"].toString()== "Successfully Joined")
    {
        create_list();
    }
    else{
    }

}

void Widget::on_LogOut_clicked()
{
    QString link;
    QSqlQuery query;
    QString us;
    query.prepare("SELECT * FROM login_token");
    query.exec();
    while(query.next())
    {
        USERN=query.value(1).toString();
        PASSWOR=query.value(2).toString();
    }
    link="http://api.softserver.org:1104/logout?username=";
    link.append(USERN);
    link.append("&password=");
    link.append(PASSWOR);
    request.setUrl(QUrl(link));
    manager->get(request);
}

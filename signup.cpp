#include "signup.h"
#include "ui_signup.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QRegExpValidator>


SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    ui->txtbPassword->setEchoMode(QLineEdit::Password);
    ui->txtbRePass->setEchoMode(QLineEdit::Password);
    setWindowIcon(QIcon(":/Icons/side-up.png"));
    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(mfin(QNetworkReply*)));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowMaximizeButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowMinimizeButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowCloseButtonHint);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_btnSave_clicked()
{
    QRegularExpression re("[0]\\d{10}[0-9]");
    QValidator *validator = new QRegularExpressionValidator(re, this);
    int symbol=0,digit=0,lower=0,upper=0;
    QString user = ui->txtbUserName->text();
    QString FirstName= ui->txtbFirstName->text();
    QString LastName= ui->txtbSureName->text();
    QByteArray Password;

    if (! (ui->txtbUserName->text().isEmpty()|| ui->txtbPassword->text().isEmpty() || ui->txtbRePass->text().isEmpty() ) )
    {
        if(ui->txtbFirstName->text().isEmpty())
            FirstName=" ";
        if(ui->txtbSureName->text().isEmpty())
            LastName=" ";
        if(ui->txtbUserName->text().length()>3)
        {
            if(ui->txtbPassword->text().length()>4)
            {
                if(ui->txtbPassword->text()==ui->txtbRePass->text())
                {
                    QString userName = ui->txtbPassword->text();
                    for ( const auto& character : userName )
                    {
                        if ( character.isUpper() )
                        {
                            upper++;
                        }
                        else if ( character.isLower() )
                        {
                            lower++;
                        }
                        else if ( character.isDigit() )
                        {
                            digit++;
                        }
                        else
                        {
                            symbol++;
                        }
                    }
                    if(symbol>0)
                    {
                        QMessageBox msg;
                        msg.setText("No Symbol!");
                        msg.setStandardButtons(QMessageBox::Ok);
                        msg.setDefaultButton(QMessageBox::Ok);
                        msg.exec();
                    }
                    else
                    {
                        if( (upper>0 || lower>0) &&digit>0)
                        {
                            QByteArray str=ui->txtbPassword->text().toUtf8();
                            QCryptographicHash hasher(QCryptographicHash::Md5);
                            hasher.addData(str);
                            Password=hasher.result();
//                            qDebug()<<Password;
//                            qDebug()<<user;
                            QString link;
                            link="http://api.softserver.org:1104/signup?username=";
                            link.append(user);
                            link.append("&password=");
                            link.append(str);
                            link.append("&firstname=");
                            link.append(FirstName);
                            link.append("&lastname=");
                            link.append(LastName);
                            request.setUrl(QUrl(link));
//                            qDebug()<<link;
                            manager->get(request);
                        }
                        else
                        {
                            QMessageBox msg;
                            msg.setText("Password Should contains Characters and digits!");
                            msg.setStandardButtons(QMessageBox::Ok);
                            msg.setDefaultButton(QMessageBox::Ok);
                            msg.exec();
                        }
                    }
                }
                else
                {
                    QMessageBox msg;
                    msg.setText("Password Fields do not match!");
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.setDefaultButton(QMessageBox::Ok);
                    msg.exec();
                }
            }
            else
            {
                QMessageBox msg;
                msg.setText("Minimum length of password is 5(characters and digits!");
                msg.setStandardButtons(QMessageBox::Ok);
                msg.setDefaultButton(QMessageBox::Ok);
                msg.exec();
            }
        }
        else
        {
            QMessageBox msg;
            msg.setText("Minimum length of username is 4!");
            msg.setStandardButtons(QMessageBox::Ok);
            msg.setDefaultButton(QMessageBox::Ok);
            msg.exec();
        }
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

void SignUp::mfin(QNetworkReply *reply)
{
    if(reply->error()){
//        qDebug() << reply->errorString ();
        return;
    }
    QByteArray test = reply->readAll ();
//    qDebug()<<test;
    QJsonDocument doc = QJsonDocument::fromJson(test);
    QJsonObject obj=doc.object();
//    qDebug()<<obj["message"].toString();

//    qDebug()<<obj["code"].toInt();
    if(obj["message"].toString()=="User Exist Try Another!")
        ui->label->setText("User Exist Try Another!");
    else
    {
        this->close();
    }
}
void SignUp::on_btnCancel_clicked()
{
    QMessageBox msg;
    msg.setText("If you continue all information will be lost");
    msg.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Cancel);
    if(msg.exec()==QMessageBox::Ok)
    {
        this->close();
    }
}

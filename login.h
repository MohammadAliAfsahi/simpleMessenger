#ifndef LOGIN_H
#define LOGIN_H

#include "goodnewsmessengar.h"
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtNetwork>
#include <QJsonObject>
#include <QSqlDatabase>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:

    void on_btnCancel_clicked();

    void on_btbLogin_clicked();

    void mfin(QNetworkReply*);
private:
    Ui::Login *ui;
    QNetworkRequest request;
    QNetworkAccessManager * manager;

    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

};

#endif // LOGIN_H

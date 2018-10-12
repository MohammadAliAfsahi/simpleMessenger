#ifndef GETCHATS_H
#define GETCHATS_H

#include <QDialog>
#include <QtNetwork>
#include <QJsonObject>
#include <QThread>
#include "widget.h"

namespace Ui {
class Widget;
}

class GetChats
{
    Q_OBJECT

public:
    GetChats();
    virtual ~GetChats();
    void DoSetup(QThread &cThread);

public slots:
    void Get();

private slots:

    void mfinguc(QNetworkReply*);

    void mfinggc(QNetworkReply*);

    void mfingcc(QNetworkReply*);

private:

    QNetworkRequest request;
    QNetworkAccessManager * managerguc;
    QNetworkAccessManager * managerggc;
    QNetworkAccessManager * managergcc;

};

#endif // GETCHATS_H

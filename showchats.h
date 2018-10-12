#ifndef SHOWCHATS_H
#define SHOWCHATS_H

#include <QDialog>
#include <QtNetwork>
#include <QJsonObject>

namespace Ui {
class ShowChats;
}

class ShowChats : public QDialog
{
    Q_OBJECT

public:
    explicit ShowChats(QWidget *parent = 0);
    void ChangeLabelText(QString text);
    ~ShowChats();

private slots:
    void on_SendRequest_clicked();

    void mfinguc(QNetworkReply*);

    void mfinggc(QNetworkReply*);

    void mfingcc(QNetworkReply*);
private:
    Ui::ShowChats *ui;

     QNetworkRequest request;
     QNetworkAccessManager * managerguc;
     QNetworkAccessManager * managerggc;
     QNetworkAccessManager * managergcc;
};

#endif // SHOWCHATS_H

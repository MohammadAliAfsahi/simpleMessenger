#ifndef GOODNEWSMESSENGAR_H
#define GOODNEWSMESSENGAR_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtNetwork>
#include <QJsonObject>
#include <QMainWindow>
namespace Ui {
class GoodNewsMessengar;
}

class GoodNewsMessengar : public QMainWindow
{
    Q_OBJECT
public:
    explicit GoodNewsMessengar(QWidget *parent = 0);
    ~GoodNewsMessengar();
private slots:
    void on_btnLogout_clicked();
     void mfin(QNetworkReply*);
     void on_btnCreateGroup_clicked();

     void on_btnCreateChannel_clicked();

     void on_btnGetIntouches_clicked();

     void on_btnGetGroupList_clicked();

     void on_btnGetChannelList_clicked();

     void on_btnGetUserChats_clicked();

     void on_btnGetGroupChats_clicked();

     void on_btnGetChannelChats_clicked();

     void on_btnJoinGroup_clicked();

     void on_btnJoinChannel_clicked();

     void on_btnsendmessageuser_clicked();

     void on_btnsendmessagegroup_clicked();

     void on_btnsendmessagechannel_clicked();

private:
    Ui::GoodNewsMessengar *ui; 
    QNetworkRequest request;
    QNetworkAccessManager * manager;
};

#endif // GOODNEWSMESSENGAR_H

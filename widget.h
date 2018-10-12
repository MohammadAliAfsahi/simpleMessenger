#ifndef WIDGET_H
#define WIDGET_H


#include <QtNetwork>
#include <QJsonObject>
#include <QList>
#include <QSqlQuery>
#include <QThread>
#include <QTimer>
#include <QMenuBar>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QMenu>

#include <QAction>

#include "createchannel.h"
#include "creategroup.h"
#include "WellcomePage.h"

namespace Ui {
class Widget;
}
class QMenu;
class Widget  : public QDialog
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    void startrequestList(const QUrl &requestedurl);

    void startrequestmessege(const QUrl &requestedurl);

    void set();

    ~Widget();
  QNetworkConfigurationManager ncm;
private slots:

    void onNetworkStateChanged(bool);

    void checkConnection();

    void RealTimeMessege();

    void RealTimeList();

    void Get_messages();

    void create_list();

    void onCreateGroupclicked();

    void onCreateChannelclicked();

    void onbtnJoinGroupclicked();

    void onJoinChannelclicked();

    void mfinguc(QNetworkReply*);

    void mfinggc(QNetworkReply*);

    void mfingcc(QNetworkReply*);

    void mfinsum(QNetworkReply*);

    void mfinscm(QNetworkReply*);

    void mfinsgm(QNetworkReply*);

    void mfinggl(QNetworkReply*);

    void mfingcl(QNetworkReply*);

    void mfingul(QNetworkReply*);

    void on_Submit_clicked();

    void Qbtnclicked();

    void mfin(QNetworkReply*);

    void mfinjg(QNetworkReply*);

    void mfinjc(QNetworkReply*);

    void on_LogOut_clicked();

private:
    void CreateMenus();

    void createActions();

    bool check_internet();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenuBar *menuBar;

    QAction *CGAct;
    QAction *CCAct;
    QAction *JGAct;
    QAction *JCAct;
    QAction *exitAct;

    QNetworkAccessManager * managersum;
    QNetworkAccessManager * managerscm;
    QNetworkAccessManager * managersgm;

    QNetworkAccessManager * managerggl;
    QNetworkAccessManager * managergcl;
    QNetworkAccessManager * managergul;

    QNetworkRequest request;

    QNetworkAccessManager * manager;
    QNetworkAccessManager * managerjg;
    QNetworkAccessManager * managerjc;

    QList<QPushButton*> listButtonsG;

    QList<QPushButton*> listButtonsU;

    QList<QPushButton*> listButtonsC;

    QPushButton *button;

    QNetworkAccessManager * managerguc;
    QNetworkAccessManager * managerggc;
    QNetworkAccessManager * managergcc;

    QNetworkReply *RealTimelist;
    QNetworkReply *RealTimemessege;

    QNetworkAccessManager *RealTimeRequestlist;
    QNetworkAccessManager *RealTimeRequestmessege;
    QThread cThread;
    Ui::Widget *ui;
    QByteArray temp;
    QString stt;
    QSqlQuery query;
    QTimer *timer;
    QTimer *timer2;
};


#endif // WIDGET_H

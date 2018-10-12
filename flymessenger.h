#ifndef FLYMESSENGER_H
#define FLYMESSENGER_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtNetwork>
#include <QJsonObject>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
namespace Ui {
class FlyMessenger;
}

class FlyMessenger : public QDialog
{
    Q_OBJECT

public:
    explicit FlyMessenger(QWidget *parent = 0);
    ~FlyMessenger();

private slots:
    void on_btnLogout_clicked();


     void on_btnCreateGroup_clicked();

     void on_btnCreateChannel_clicked();

     void on_btnJoinGroup_clicked();

     void on_btnJoinChannel_clicked();

     void on_btnsendmessageuser_clicked();

private:
    Ui::FlyMessenger *ui;

//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

};

#endif // FLYMESSENGER_H

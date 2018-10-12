#ifndef CREATECHANNEL_H
#define CREATECHANNEL_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtNetwork>
#include <QJsonObject>
#include <QMainWindow>

namespace Ui {
class CreateChannel;
}

class CreateChannel : public QDialog
{
    Q_OBJECT

public:
    explicit CreateChannel(QWidget *parent = 0);
    ~CreateChannel();


private slots:
    void on_btnCancel_clicked();

    void on_btnCreate_clicked();

    void mfin(QNetworkReply *);
private:
    Ui::CreateChannel *ui;
    QNetworkRequest request;
    QNetworkAccessManager * manager;
};

#endif // CREATECHANNEL_H

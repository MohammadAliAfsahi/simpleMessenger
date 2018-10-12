#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtNetwork>
#include <QJsonObject>
#include <QMainWindow>
namespace Ui {
class CreateGroup;
}

class CreateGroup : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGroup(QWidget *parent = 0);
    ~CreateGroup();

private slots:
    void on_btnCreate_clicked();

    void on_btnCancel_clicked();

    void mfin(QNetworkReply *);
private:
    Ui::CreateGroup *ui;
    QNetworkRequest request;
    QNetworkAccessManager * manager;
};

#endif // CREATEGROUP_H

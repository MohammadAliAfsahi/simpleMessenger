#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QtNetwork>
#include <QJsonObject>

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = 0);
    ~SignUp();

private slots:
    void on_btnSave_clicked();

    void on_btnCancel_clicked();

    void mfin(QNetworkReply*);
private:
    Ui::SignUp *ui;
     bool connected;
    int currentID;
    bool userexist;
    QNetworkRequest request;
    QNetworkAccessManager * manager;
};

#endif // SIGNUP_H

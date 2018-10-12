#include "homepage.h"
#include "ui_homepage.h"
#include "signup.h"
#include "login.h"
#include "goodnewsmessengar.h"
#include <QApplication>
extern int ret;
HomePage::HomePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Icons/traffic-sign.png"));

}

HomePage::~HomePage()
{
    delete ui;
}



void HomePage::on_btnSignUP_clicked()
{
    SignUp sign;
    sign.show();
    sign.exec();
}

void HomePage::on_btnLogin_clicked()
{
    Login log;
    log.exec();
    if(ret==200)
    {
       //showing chat windows
    }
}

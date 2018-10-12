#include "WellcomePage.h"
#include "ui_WellcomePage.h"



int ret;

WellcomePage::WellcomePage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WellcomePage)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Icons/network.png"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowMinimizeButtonHint);
    setWindowFlags(windowFlags() & Qt::WindowCloseButtonHint);
}


WellcomePage::~WellcomePage()
{
    delete ui;
}
void WellcomePage::on_btnSignUP_clicked()
{
    SignUp sign;
    sign.exec();
}

void WellcomePage::on_btnLogin_clicked()
{
    Login log;
    if(log.exec())
    {
        this->hide();
        Widget w;
        w.exec();
    }
}

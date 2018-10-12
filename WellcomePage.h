#ifndef WellcomePage_H
#define WellcomePage_H


#include "widget.h"
#include "signup.h"
#include "login.h"

namespace Ui {
class WellcomePage;
}

class WellcomePage :public QDialog
{
    Q_OBJECT

public:
    explicit WellcomePage(QWidget *parent = 0);
    ~WellcomePage();

private:
    Ui::WellcomePage *ui;

public slots:
    void on_btnSignUP_clicked();

    void on_btnLogin_clicked();
};

#endif // WellcomePage_H

#include "enrolldialog.h"
#include "ui_enrolldialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

enrolldialog::enrolldialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::enrolldialog)
{
    ui->setupUi(this);
    this->setFixedSize(360,330);
}

enrolldialog::~enrolldialog()
{
    delete ui;
}

void enrolldialog::on_pushButton_clicked()
{
    QString user = ui->nameEdit->text();
    QString password = ui->passwordEdit->text();
    QSqlQuery query;
    QString str = QString("select * from t1 where `name` = '%1';").arg(user);

    query.exec(str);
    if(query.next())
    {
        QMessageBox::information(this,"提示","已存在的用户名","Yes");
        ui->nameEdit->clear();
        ui->passwordEdit->clear();
    }
    else
    {
        QSqlQuery query;
        QString s = QString("insert into t1 (u_name,u_password) values('%1','%2');").arg(user).arg(password);
        query.exec(s);
        QMessageBox::information(this,"提示","注册成功","Yes");
        this->close();
     }
}

#include "logdialog.h"
#include "ui_logdialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "enrolldialog.h"

logDialog::logDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logDialog)
{
    ui->setupUi(this);
    ui->lineEdit_name->setFocus();
    this->setFixedSize(400,360);
}

logDialog::~logDialog()
{
    delete ui;
}

void logDialog::on_btn_cancle_clicked()
{
    this->close();
}

void logDialog::on_btn_confirm_2_clicked()
{
    this->user = ui->lineEdit_name->text();
    this->password = ui->lineEdit_pwd->text();
    QString check = QString("select * from t1 where `u_name` = '%1' and `u_password` = '%2'").arg(user).arg(password);
    QSqlQuery query;
    query.exec(check);
    if(query.next())
    {
        //        QSqlQuery query;
        //        QString str = QString("update t3 set `islogin` = '%1' where name = '%2'").arg(true).arg(user);
        //        query.exec(str);
        //        accept();
        QMessageBox::information(this,"信息","登陆成功！","Yes");
        //
        accept();
        this->close();
    }
    else
    {
        QMessageBox::warning(this,"警告！","输入信息有误","Yes");
        ui->lineEdit_name->setFocus();
    }
}

void logDialog::on_commandLinkButton_toenroll_clicked()
{
    enrolldialog *edg = new enrolldialog(this);
    edg->setModal(true);
    edg->show();
    edg->exec();
}

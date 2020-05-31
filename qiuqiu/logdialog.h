#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>

namespace Ui {
class logDialog;
}

class logDialog : public QDialog
{
    Q_OBJECT

public:
    explicit logDialog(QWidget *parent = nullptr);
    ~logDialog();

private slots:
    void on_btn_cancle_clicked();

    void on_btn_confirm_2_clicked();

    void on_commandLinkButton_toenroll_clicked();

private:
    Ui::logDialog *ui;
public:
    QString user;
    QString password;
};

#endif // LOGDIALOG_H

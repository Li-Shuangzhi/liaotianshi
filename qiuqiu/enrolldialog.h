#ifndef ENROLLDIALOG_H
#define ENROLLDIALOG_H

#include <QDialog>

namespace Ui {
class enrolldialog;
}

class enrolldialog : public QDialog
{
    Q_OBJECT

public:
    explicit enrolldialog(QWidget *parent = nullptr);
    ~enrolldialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::enrolldialog *ui;
};

#endif // ENROLLDIALOG_H

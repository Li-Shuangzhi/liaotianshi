#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QMenu>
#include <QWidget>
#include <QTcpSocket>
#include "logdialog.h"
#include "enrolldialog.h"

namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

    void background_to_default();
    void background_setting();
    void tolog();
    void toenroll();
protected:
    //重写这三个事件，实现窗体可拖放
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private slots:
    void on_btn_close_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_skin_clicked();

    void on_pushButton_clicked();

    void on_btn_send_clicked();

    void readMess();

private:
    Ui::mainWidget *ui;
    //实现窗体自由拖放时用到的两个成员变量
    bool bPressFlag;
    QPoint beginDrag;

    QMenu *menu_changeSkin;
    QMenu *menu_login;
    logDialog* Login;
    enrolldialog* edg;

    QTcpSocket* tcpSocket;

    qint16 blockSize;
};

#endif // MAINWIDGET_H

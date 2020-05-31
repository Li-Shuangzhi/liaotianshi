#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include <QImage>
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTimer>

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);

    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/img/default.jpg");
    QImage fitimgpic = ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);

    //实现窗体圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 10, 10);
    setMask(bmp);

    QAction *action_backgroud_to_default = new QAction(QIcon(":/img/default.jpg"),u8"更换到默认背景");
    connect(action_backgroud_to_default,&QAction::triggered,this,&mainWidget::background_to_default);
    QAction *action_backgroud_setting=new QAction(QIcon(":/img/setting.png"),u8"自定义背景");
    connect(action_backgroud_setting,&QAction::triggered,this,&mainWidget::background_setting);
    menu_changeSkin=new QMenu(this);
    menu_changeSkin->addAction(action_backgroud_to_default);
    menu_changeSkin->addAction(action_backgroud_setting);

    QAction *log = new QAction(u8"登录");
    connect(log,&QAction::triggered,this,&mainWidget::tolog);
    QAction *enroll = new QAction(u8"注册");
    connect(enroll,&QAction::triggered,this,&mainWidget::toenroll);

    menu_login = new QMenu(this);
    menu_login->addAction(log);
    menu_login->addAction(enroll);

    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::disconnected,[=]{
        tcpSocket->abort();
        QMessageBox::warning(this,"errors","服务端已断开");
        ui->textEdit_content->clear();
        ui->listWidget->clear();
    });

    connect(tcpSocket,&QTcpSocket::connected,[=]{
        QString str = QString("%1 已登录").arg(Login->user);
        ui->label->setText(str);
        QString ss = Login->user + "+";

        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_12);
        out<<(qint16)0;
        out<<ss;
        out.device()->seek(0);
        out<<(qint16)(block.size() - sizeof(qint16));
        tcpSocket->write(block);
    });
    connect(tcpSocket,&QTcpSocket::readyRead,this,&mainWidget::readMess);

}

void mainWidget::readMess()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    if(tcpSocket->bytesAvailable() < (int)sizeof(qint16))
        return;
    in>>blockSize;
    qDebug()<<blockSize;
    if(tcpSocket->bytesAvailable() < blockSize)
        return;
    QString str;

    in>>str;
    qDebug()<<str;
    if(str.back() == '+')
    {
        ui->listWidget->clear();
        QStringList list = str.split(",");
        for(int i = 0;i < list.size();i ++)
        {
            ui->listWidget->addItem(list.at(i));
        }
    }
    else
    {
        ui->textEdit_content->setText(str);
    }
}
mainWidget::~mainWidget()
{
    delete ui;
}
void mainWidget::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void mainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void mainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(bPressFlag)
    {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void mainWidget::on_btn_close_clicked()
{
    tcpSocket->close();
    QTimer::singleShot(1000,this,[=](){this->close();});

}

void mainWidget::on_pushButton_2_clicked()
{
    this->showMinimized();
}

void mainWidget::on_pushButton_skin_clicked()
{
    menu_changeSkin->exec(QCursor::pos());
}
void mainWidget::background_to_default()
{
    QString fileName=":/img/default.jpg";
    QSettings mysettings("./quiqui.ini",QSettings::IniFormat);
    mysettings.setIniCodec("UTF8");
    mysettings.setValue("background/image-url",fileName);

    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(fileName);
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
}

void mainWidget::background_setting()
{
    //从默认图片位置打开文件选择框
    QString fileName = QFileDialog::getOpenFileName(this,tr("选择自定义背景图片"),QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first(),u8"图片文件(*jpg *png)");
    if(!fileName.isEmpty())
    {
        QImage testImage(fileName);
        if(!testImage.isNull()){
            QSettings mysettings("./quiqui.ini",QSettings::IniFormat);
            mysettings.setIniCodec("UTF8");
            mysettings.setValue("background/image-url",fileName);

            QPalette PAllbackground = this->palette();
            QImage ImgAllbackground(fileName);
            QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
            PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
            this->setPalette(PAllbackground);
        }
    }
}
void mainWidget::tolog(){
    Login = new logDialog(this);
    if(Login->exec() == QDialog::Accepted)
    {
        tcpSocket->abort();
        QString ip = "127.0.0.1";
        qint16 port = 6666;
        //尝试连接到IP地址为ip，端口号为port的服务器。
        tcpSocket->connectToHost(ip,port);
    }
}
void mainWidget::toenroll(){
    enrolldialog *edg = new enrolldialog(this);
    edg->setModal(true);
    edg->show();
    edg->exec();
}

void mainWidget::on_pushButton_clicked()
{
    menu_login->exec(QCursor::pos());
}

void mainWidget::on_btn_send_clicked()
{
    if(tcpSocket->isValid() == false){
        QMessageBox::warning(this,"警告","连接失败！");
        return;
    }
    if( ui->textEdit_tosend ->toPlainText() == ""){
        QMessageBox::warning(this,"警告","消息不能为空！");
        return;
    }
    QString str = Login->user + " :";
    str += ui->textEdit_tosend ->toPlainText();

    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out<<(qint16)0;

    out<<str;
    out.device()->seek(0);
    out<<(qint16)(block.size() - sizeof(qint16));
    tcpSocket->write(block);

    ui->textEdit_tosend->clear();
}

#ifndef SEVERWIDGET_H
#define SEVERWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SeverWidget; }
QT_END_NAMESPACE

class SeverWidget : public QWidget
{
    Q_OBJECT

public:
    SeverWidget(QWidget *parent = nullptr);
    ~SeverWidget();

private:
    Ui::SeverWidget *ui;
};
#endif // SEVERWIDGET_H

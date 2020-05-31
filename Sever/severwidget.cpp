#include "severwidget.h"
#include "ui_severwidget.h"

SeverWidget::SeverWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SeverWidget)
{
    ui->setupUi(this);
}

SeverWidget::~SeverWidget()
{
    delete ui;
}


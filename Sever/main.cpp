#include "severwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SeverWidget w;
    w.show();
    return a.exec();
}

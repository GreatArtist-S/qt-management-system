#include "widget.h"
#include <QSqlError>
#include <QDebug>
#include<QSqlDatabase>
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

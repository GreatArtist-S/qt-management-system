#ifndef SALEWIDGET_H
#define SALEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "addsalerecorddialog.h"
#include "changesalesrecorddialog.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QString>

namespace Ui {
class SaleWidget;
}

class SaleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SaleWidget(QWidget *parent = nullptr);
    ~SaleWidget();
    void getNum(const QString N);

private slots:

    void on_RButton_clicked();

    void on_pushButton_3_clicked();

    void on_DButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::SaleWidget *ui;
    QString numb;
    addsalerecordDialog *addDialog;
    changesalesrecordDialog *changeDialog;
    int nowRow;

    //实现函数定义
    void showbutton();
    void showsqlite();
    void showmoney();
    void showthis();
    void changequantity();
    void showtotalmoney();
};

#endif // SALEWIDGET_H

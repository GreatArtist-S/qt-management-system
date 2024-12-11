#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include "Product.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDataStream>
#include <QTextStream>

namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformationDialog(QWidget *parent = nullptr);
    ~InformationDialog();
    Product *product;

private slots:
    void on_buttonBox_accepted();
signals:
    void info();
private:
    Ui::InformationDialog *ui;
};

#endif // INFORMATIONDIALOG_H


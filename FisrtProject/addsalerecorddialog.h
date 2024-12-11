#ifndef ADDSALERECORDDIALOG_H
#define ADDSALERECORDDIALOG_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

namespace Ui {
class addsalerecordDialog;
}

class addsalerecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addsalerecordDialog(QWidget *parent = nullptr);
    ~addsalerecordDialog();
    void send(QString &Num);

private slots:
    void on_buttonBox_accepted();


signals:
    void add();

private:
    Ui::addsalerecordDialog *ui;
    QString Numb;
};

#endif // ADDSALERECORDDIALOG_H

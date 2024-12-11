#ifndef CHANGESALESRECORDDIALOG_H
#define CHANGESALESRECORDDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QMessageBox>
namespace Ui {
class changesalesrecordDialog;
}

class changesalesrecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changesalesrecordDialog(QWidget *parent = nullptr);
    ~changesalesrecordDialog();
    void getrow(QString &num);
    void setchange(const QStringList &change);
    void send(QString &N);
private slots:
    void on_buttonBox_accepted();

signals:
    void change();
private:
    Ui::changesalesrecordDialog *ui;
    QString n;
    QString Num;
    int Q;
    int newQ;
};

#endif // CHANGESALESRECORDDIALOG_H

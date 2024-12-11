#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDataStream>
#include <QTextStream>
namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog();


signals:
    void deleteConfirmed();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DeleteDialog *ui;
};

#endif // DELETEDIALOG_H


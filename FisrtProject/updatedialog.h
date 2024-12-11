#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include <QDate>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
namespace Ui {
class updateDialog;
}

class updateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit updateDialog(QWidget *parent = nullptr);
    ~updateDialog();
    void setInformation(const QStringList &info); // 设置信息
    void getRow(const QString &num);//获得当前行

signals:
    void informationUpdated();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::updateDialog *ui;
    QString Number;
};

#endif // UPDATEDIALOG_H

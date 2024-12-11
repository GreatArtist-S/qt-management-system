#ifndef MANAGEWIDGET_H
#define MANAGEWIDGET_H

#include <QWidget>
#include <QTableWidget>
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
namespace Ui {
class managewidget;
}

class managewidget : public QWidget
{
    Q_OBJECT

public:
    explicit managewidget(QWidget *parent = nullptr);
    ~managewidget();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::managewidget *ui;
    QTableWidget *rTable;

    void showneed();
};

#endif // MANAGE_H

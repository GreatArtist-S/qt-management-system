#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "informationdialog.h"
#include "deletedialog.h"
#include "updatedialog.h"
#include "salewidget.h"
#include "managewidget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMessageBox>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QString pathname;
    ~MainWindow();


private slots:

    void on_exitpushButton_clicked();

    void on_SearchpushButton_clicked();

    void on_ReturnpushButton_clicked();

    void on_reviseButton_clicked();

    void on_salesButton_clicked();

    void on_actionaddNew_triggered();

    void on_actiondelete_triggered();

    void on_actionstockmanage_triggered();

    void on_actionsave_triggered();

private:
    Ui::MainWindow *ui;
    QTableWidget *productTable;
    DeleteDialog *deleteDialog;
    InformationDialog *infoDialog;// InformationDialog对象
    updateDialog *upDialog;
    SaleWidget *sale;
    managewidget *ma;
    int currentRow; // 记录当前正在修改的行号
    int saleRow;//记录正在添加数据的行号
    QList<Product> productList;
    QList<QList<QTableWidgetItem*>> originalTableData;

    // Helper function to add a product to the table
    void deleteProduct(const QString &productNumber);
    void updateProduct();
    void showtable();
    void showsql();
    void showall();
};

#endif // MAINWINDOW_H


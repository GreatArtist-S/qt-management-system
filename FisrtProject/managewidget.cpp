#include "managewidget.h"
#include "ui_managewidget.h"

managewidget::managewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::managewidget)
{
    ui->setupUi(this);

    QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setHostName("127.0.0");
    DB.setDatabaseName("first.db");     // 设置数据库名称
    DB.setUserName("root");
    DB.setPassword("123456");
    if(!DB.open())
    {
            QMessageBox::warning(this,"提示","打开数据库失败");
    }//数据库连接操作

    rTable = ui->tableWidget;
    rTable->setColumnCount(4);
    QStringList headers;
    headers << "商品名称" << "商品编号" << "商品数量" << "缺货状态";
    rTable->setHorizontalHeaderLabels(headers);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &managewidget::showneed);
    connect(ui->pushButton, &QPushButton::clicked, this, &managewidget::on_pushButton_clicked);
    showneed();
}

managewidget::~managewidget()
{
    delete ui;
}

void managewidget::showneed()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    QSqlQuery query;
    query.prepare("SELECT name, number, total FROM BasicInfo");

    if (!query.exec()) {
            QMessageBox::warning(this, "Error", "运行失败");
            return;
        }

        int row = 0;
        while (query.next()) {
            QString name = query.value(0).toString();
            QString number = query.value(1).toString();
            int total = query.value(2).toInt();

            if (total < 100) {
                ui->tableWidget->insertRow(row);

                ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(number));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(total)));

                QString status = (total == 0) ? "缺货" : "少量";
                ui->tableWidget->setItem(row, 3, new QTableWidgetItem(status));

                row++;
            }
        }
}

void managewidget::on_pushButton_3_clicked()
{
    this->close();
}

void managewidget::on_pushButton_clicked()
{
    // 从 lineEdit 和 lineEdit_2 中获取输入数据
    QString Number = ui->lineEdit->text();  // 获取 lineEdit 中的 QString
    int Total = ui->lineEdit_2->text().toInt();  // 获取 lineEdit_2 中的整型

    // 创建数据库查询对象
    QSqlQuery query;

    // 查找 BasicInfo 表中 number 列为 Number 的行
    query.prepare("SELECT total FROM BasicInfo WHERE number = :number");
    query.bindValue(":number", Number);

    if (!query.exec()) {
        // 执行查询失败时显示错误信息
        QMessageBox::warning(this, "Query Error", "Failed to execute query" );
        return;
    }

    // 如果找到符合条件的行
    if (query.next()) {
        int T = query.value(0).toInt();  // 获取 total 列的值并转为整型

        // 计算 T 和 Total 的和
        int newTotal = T + Total;

        // 更新数据库中的 total 列
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE BasicInfo SET total = :newTotal WHERE number = :number");
        updateQuery.bindValue(":newTotal", newTotal);
        updateQuery.bindValue(":number", Number);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();

        if (!updateQuery.exec()) {
            // 如果更新失败，显示错误信息
            QMessageBox::warning(this, "Update Error", "Failed to update total: " + updateQuery.lastError().text());
        }
    }
}

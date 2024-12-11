#include "informationdialog.h"
#include "ui_informationdialog.h"

InformationDialog::InformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InformationDialog)
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
}

InformationDialog::~InformationDialog()
{
    delete ui;
}

void InformationDialog::on_buttonBox_accepted()
{
    // Store values in QString format
    QString name = ui->lineEdit->text();
    QString number = ui->lineEdit_2->text();
    QString total = QString::number(ui->lineEdit_3->text().toInt());
    QString purchasePrice = QString::number(ui->lineEdit_4->text().toFloat());
    QString salePrice = QString::number(ui->lineEdit_5->text().toFloat());
    QString manufacturer = ui->lineEdit_6->text();
    QString productionDate = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString qualityDate = QString::number(ui->lineEdit_8->text().toInt());

    // Check if the product already exists in the database
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM BasicInfo WHERE name = :name");
    query.bindValue(":name", name);

    if(query.exec()) {
        query.next();  // Move to the first result
        int count = query.value(0).toInt();

        if(count > 0) {
            // If count is greater than 0, the name exists, show a message
            QMessageBox::information(this, "提醒", "商品已存在");
        } else {
            // If the name does not exist, insert the new product into the database
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO BasicInfo (name, number, total, PurchasePrice, SalePrice, Manufacturer, ProductionDate, QualityDate) "
                                "VALUES (:name, :number, :total, :PurchasePrice, :SalePrice, :Manufacturer, :ProductionDate, :QualityDate)");
            insertQuery.bindValue(":name", name);
            insertQuery.bindValue(":number", number);
            insertQuery.bindValue(":total", total);
            insertQuery.bindValue(":PurchasePrice", purchasePrice);
            insertQuery.bindValue(":SalePrice", salePrice);
            insertQuery.bindValue(":Manufacturer", manufacturer);
            insertQuery.bindValue(":ProductionDate", productionDate);
            insertQuery.bindValue(":QualityDate", qualityDate);

            if(insertQuery.exec()) {
                emit info();// Signal that data was successfully inserted
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->lineEdit_4->clear();
                ui->lineEdit_5->clear();
                ui->lineEdit_6->clear();
                ui->dateEdit->clear();
                ui->lineEdit_8->clear();
            } else {
                QMessageBox::warning(this, "错误", "无法插入数据");
            }
        }
    } else {
        QMessageBox::warning(this, "错误", "数据库查询失败");
    }
    this->close();
}

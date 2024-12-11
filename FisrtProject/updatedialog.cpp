#include "updatedialog.h"
#include "ui_updatedialog.h"

updateDialog::updateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateDialog)
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

updateDialog::~updateDialog()
{
    delete ui;
}
void updateDialog::setInformation(const QStringList &info)
{
        QDate dt = QDate::fromString(info.at(6), "yyyy-MM-dd");
        ui->lineEdit->setText(info.at(0));
        ui->lineEdit_2->setText(info.at(1));
        ui->lineEdit_3->setText(info.at(2));
        ui->lineEdit_4->setText(info.at(3));
        ui->lineEdit_5->setText(info.at(4));
        ui->lineEdit_6->setText(info.at(5));
        ui->dateEdit->setDate(dt);
        ui->lineEdit_8->setText(info.at(7));

}
void updateDialog::getRow(const QString &num)
{
    QSqlQuery query;
    query.prepare("SELECT number FROM BasicInfo WHERE number = :num");
    query.bindValue(":num", num);

    if (query.exec()) {
        // If a result is found, set 'Number' to the provided 'num'
        if (query.next()) {
            Number = num;
        } else {
            // Show an error message if no row with the provided number was found
            QMessageBox::warning(this, "错误", "未找到相应的行");
        }
    } else {
        // Show an error message if the query failed
        QMessageBox::warning(this, "错误", "无法从数据库加载数据: " + query.lastError().text());
    }
}
void updateDialog::on_buttonBox_accepted()
{
        // 获取用户修改后的信息
    QString name = ui->lineEdit->text();
    QString number = ui->lineEdit_2->text();  // Usually, this should not be changed for consistency
    QString total = ui->lineEdit_3->text();
    QString purchasePrice = ui->lineEdit_4->text();
    QString salePrice = ui->lineEdit_5->text();
    QString manufacturer = ui->lineEdit_6->text();
    QString productionDate = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString qualityDate = ui->lineEdit_8->text();

    // Prepare SQL query to update the row where the number matches the current one
    QSqlQuery query;
    query.prepare("UPDATE BasicInfo SET name = :name, number = :number, total = :total, "
                  "PurchasePrice = :purchasePrice, SalePrice = :salePrice, Manufacturer = :manufacturer, "
                  "ProductionDate = :productionDate, QualityDate = :qualityDate "
                  "WHERE number = :originalNumber");

    // Bind the new values to the query
    query.bindValue(":name", name);
    query.bindValue(":number", number);
    query.bindValue(":total", total);
    query.bindValue(":purchasePrice", purchasePrice);
    query.bindValue(":salePrice", salePrice);
    query.bindValue(":manufacturer", manufacturer);
    query.bindValue(":productionDate", productionDate);
    query.bindValue(":qualityDate", qualityDate);
    query.bindValue(":originalNumber", Number);  // This is the original number of the row being updated

    // Execute the query and check for success
    if (query.exec()) {
        emit informationUpdated();  // Emit signal to refresh the UI
    } else {
        QMessageBox::warning(this, "错误", "无法更新数据: " + query.lastError().text());
    }
    this->close(); // 关闭对话框
}

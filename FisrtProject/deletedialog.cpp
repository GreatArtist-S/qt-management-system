#include "deletedialog.h"
#include "ui_deletedialog.h"

DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
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

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::on_buttonBox_accepted()
{
    QString keyword = ui->lineEdit->text(); // 获取输入的关键字

    if (keyword.isEmpty()) {
        QMessageBox::warning(this, "警告", "请输入要删除的编号");
        return;
    }

    // Prepare SQL query to delete the row with the matching number
    QSqlQuery query;
    query.prepare("DELETE FROM BasicInfo WHERE number = :number");
    query.bindValue(":number", keyword);  // Bind the keyword value

    QSqlQuery sql;
    sql.prepare("delete form salesRecord where Number = :number");
    sql.bindValue(":number", keyword);

    if(query.exec()) {
        if (query.numRowsAffected() > 0) {
            emit deleteConfirmed();
            sql.exec();
        } else {
            QMessageBox::warning(this, "提示", "未找到匹配的编号");
        }
    } else {
        QMessageBox::warning(this, "错误", "无法删除数据");
    }

    // Clear the input field and close the dialog
    ui->lineEdit->clear();
}



#include "addsalerecorddialog.h"
#include "ui_addsalerecorddialog.h"

addsalerecordDialog::addsalerecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addsalerecordDialog)
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

addsalerecordDialog::~addsalerecordDialog()
{
    delete ui;
}
void addsalerecordDialog::send(QString &Num)
{
    Numb = Num;
}
void addsalerecordDialog::on_buttonBox_accepted()
{
    QString ID = ui->lineEdit->text();
    QString Quantity = ui->lineEdit_2->text();
    QString discount = ui->lineEdit_3->text();
    QString Date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString number = ui->lineEdit_4->text();

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM salesRecord WHERE orderID = :ID");
    query.bindValue(":ID", ID);

    if(query.exec())
    {
        query.next();
        int count = query.value(0).toInt();

        if(count > 0)
        {
            // If count is greater than 0, the name exists, show a message
            QMessageBox::information(this, "提醒", "订单号已存在");
        }
        else
        {
            int q = Quantity.toInt();
            QSqlQuery s;
            s.prepare("select total from BasicInfo where number = :Numb");
            s.bindValue(":Numb", Numb);
            s.exec();
            s.next();
            int T = s.value(0).toInt();
            int newT = T - q;
            if(newT<0)
            {
                QMessageBox::warning(this, "错误", "超出库存");
                this->close();

            }
            else{
                QSqlQuery query;
                query.prepare("UPDATE BasicInfo set total = :newT WHERE number = :Numb");
                query.bindValue(":newT", newT);
                query.bindValue(":Numb", Numb);
                query.exec();
            // If the name does not exist, insert the new product into the database
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO salesRecord (orderID, quantity, discountrate, orderDate, contactNumber, Number)"
                                "VALUES (:orderID, :quantity, :discountrate, :orderDate, :contactNumber, :Number)");
            insertQuery.bindValue(":orderID", ID);
            insertQuery.bindValue(":quantity", Quantity);
            insertQuery.bindValue(":discountrate", discount);
            insertQuery.bindValue(":orderDate", Date);
            insertQuery.bindValue(":contactNumber", number);
            insertQuery.bindValue(":Number", Numb);
            if(insertQuery.exec())
            {
                emit add();
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_3->clear();
                ui->dateEdit->clear();
                ui->lineEdit_4->clear();
            }
            else
            {
                QMessageBox::warning(this, "错误","数据插入失败");
            }
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "错误", "数据库查询失败");
    }
    this->close();
}

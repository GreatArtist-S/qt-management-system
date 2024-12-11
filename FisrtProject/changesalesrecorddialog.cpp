#include "changesalesrecorddialog.h"
#include "ui_changesalesrecorddialog.h"

changesalesrecordDialog::changesalesrecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changesalesrecordDialog)
{
    ui->setupUi(this);
}

changesalesrecordDialog::~changesalesrecordDialog()
{
    delete ui;
}
void changesalesrecordDialog::send(QString &N)
{
    Num = N;
}
void changesalesrecordDialog::getrow(QString &num)
{
    n = num;
}
void changesalesrecordDialog::setchange(const QStringList &change)
{
    //将表中数据填入界面
        QDate dt = QDate::fromString(change.at(3), "yyyy-MM-dd");
        ui->lineEdit->setText(change.at(0));
        ui->lineEdit_2->setText(change.at(1));
        ui->lineEdit_3->setText(change.at(2));
        ui->dateEdit->setDate(dt);
        ui->lineEdit_4->setText(change.at(4));
        Q = change.at(1).toInt();
}

void changesalesrecordDialog::on_buttonBox_accepted()
{
    //将更新后的数据保存，并更新库存商品数量
    QString ID = ui->lineEdit->text();
    QString Quantity = ui->lineEdit_2->text();
    QString discount = ui->lineEdit_3->text();
    QString Date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString number = ui->lineEdit_4->text();
    newQ = Quantity.toInt();
    QSqlQuery s;
    s.prepare("select total from BasicInfo where number = :Numb");
    s.bindValue(":Numb", Num);
    s.exec();
    s.next();
    int T = s.value(0).toInt();
    int newT = T + (Q - newQ);
    if(newT<0)
    {
        QMessageBox::warning(this, "错误", "超出库存");
        this->close();
    }
    else
    {
        QSqlQuery sql;
        sql.prepare("UPDATE BasicInfo set total = :newT WHERE number = :Numb");
        sql.bindValue(":newT", newT);
        sql.bindValue(":Numb", Num);
        sql.exec();
        QSqlQuery query;
        query.prepare("UPDATE salesRecord set orderID = :ID, quantity = :Quantity, discountrate = :discount, orderDate = :Date, contactNumber = :number WHERE orderID = :n");
        query.bindValue(":n", n);
        query.bindValue(":ID", ID);
        query.bindValue(":Quantity", Quantity);
        query.bindValue(":discount", discount);
        query.bindValue(":Date", Date);
        query.bindValue(":number", number);

        if (query.exec()) {
            emit change();  // Emit signal to refresh the UI
        } else {
            QMessageBox::warning(this, "错误", "无法更新数据: " + query.lastError().text());
        }
    }
    this->close();
}

#include "salewidget.h"
#include "ui_salewidget.h"

SaleWidget::SaleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaleWidget)
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

    ui->saletableWidget->setColumnCount(8);
    QStringList headers;
    headers << "订单号" << "数量" << "折扣率" << "订单日期" << "联系电话"
            << "订单总利润（元）" << "修改订单"<< "办理退货";
    ui->saletableWidget->setHorizontalHeaderLabels(headers);
    addDialog = new addsalerecordDialog(this);
    changeDialog = new changesalesrecordDialog(this);

    connect(addDialog, &addsalerecordDialog::add, this, &SaleWidget::showthis);
    connect(changeDialog, &changesalesrecordDialog::change, this, &SaleWidget::showthis);
    connect(ui->pushButton, &QPushButton::clicked, this, &SaleWidget::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &SaleWidget::showthis);
    ui->lcdNumber->setDigitCount(10);
    ui->lcdNumber->setMode(QLCDNumber::Dec);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setSmallDecimalPoint(false);

}

SaleWidget::~SaleWidget()
{
    delete ui;
}
void SaleWidget::getNum(const QString N)
{
    numb = N;
    qDebug() << "Received Num: " << numb;
    showsqlite();
    showmoney();
    showbutton();
    showtotalmoney();
}

void SaleWidget::showbutton()
{
    // 为每一行添加修改按钮，并连接槽函数
    for (int row = 0; row < ui->saletableWidget->rowCount(); ++row) {
        QPushButton *RButton = new QPushButton("修改", this);
        ui->saletableWidget->setCellWidget(row, ui->saletableWidget->columnCount() - 2, RButton);
        connect(RButton, &QPushButton::clicked, this, &SaleWidget::on_RButton_clicked);
    }
    //为每行添加删除按钮，并连接槽函数
    for(int row = 0; row < ui->saletableWidget->rowCount(); ++row){
        QPushButton *DButton = new QPushButton("退货", this);
        ui->saletableWidget->setCellWidget(row, ui->saletableWidget->columnCount() - 1, DButton);
        connect(DButton, &QPushButton::clicked, this, &SaleWidget::on_DButton_clicked);
    }

}
void SaleWidget::on_DButton_clicked(){
    //实现删除按钮，并在删除销售数据时补入货物
    int row = ui->saletableWidget->currentRow();
    nowRow = row;
    QSqlQuery s;
    s.prepare("select total from BasicInfo where number = :Numb");
    s.bindValue(":Numb", numb);
    s.exec();
    s.next();
    int T = s.value(0).toInt();
    int q = ui->saletableWidget->item(nowRow, 1)->text().toInt();
    int newT = T + q;
    QSqlQuery query;
    query.prepare("UPDATE BasicInfo set total = :newT WHERE number = :Numb");
    query.bindValue(":newT", newT);
    query.bindValue(":Numb", numb);
    query.exec();
        QString ID = ui->saletableWidget->item(nowRow, 0)->text();
        QSqlQuery sql;
        sql.prepare("DELETE FROM salesRecord WHERE orderID = :ID");
        sql.bindValue(":ID", ID);
        if(sql.exec()){
            showthis();
        }
        else{
            QMessageBox::information(this, "错误", "删除失败");
        }
}
void SaleWidget::on_RButton_clicked()
{
    //实现修改按钮，并修改库存货物数量
    int row = ui->saletableWidget->currentRow();
        nowRow = row;
        QStringList currentData;
                for (int col = 0; col < 5; ++col) { // 不包括最后两列的按钮列
                    QTableWidgetItem *item = ui->saletableWidget->item(row, col);
                    if (item) {
                        currentData << item->text();
                    } else {
                        currentData << ""; // 如果为空，则添加空字符串
                    }
                }
        QString ID = ui->saletableWidget->item(nowRow, 0)->text();
        changeDialog->setchange(currentData); // 将当前信息传递给对话框
        changeDialog->getrow(ID);
        changeDialog->send(numb);
        // 显示信息对话框
        changeDialog->show();

}
void SaleWidget::showsqlite()
{
    // 清空现有的 tableWidget 数据
    ui->saletableWidget->clearContents();
    ui->saletableWidget->setRowCount(0);

    // 构建 SQL 查询，查找 Number 列等于 numb 的记录，提取前5列
    QSqlQuery query;
    query.prepare("select orderID, quantity, discountrate, orderDate, contactNumber from salesRecord where Number = :numb");
    query.bindValue(":numb", numb);

    // 执行查询
    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError();
        return;
    }

    int row = 0;

    // 遍历查询结果
    while (query.next()) {

        // 获取前5列的数据并在 tableWidget 中展示
        ui->saletableWidget->insertRow(row);  // Insert a new row in the table

        // Insert each column value into the table widget
        for (int col = 0; col < 5; ++col) {
            ui->saletableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        // 增加一行
        row++;
    }

    if (row == 0) {
        qDebug() << "No matching records found for Number:" << numb;
    }
}
void SaleWidget::showmoney()
{
    QSqlQuery sql;
    sql.prepare("select PurchasePrice, SalePrice from BasicInfo where number = :numb");
    sql.bindValue(":numb",numb);
    sql.exec();
    sql.next();
    float cost = sql.value(0).toString().toFloat();
    float saleprice = sql.value(1).toString().toFloat();
    for (int row = 0; row < ui->saletableWidget->rowCount(); ++row) {
        // Extract Quantity (integer) from the second column
        int Quantity = ui->saletableWidget->item(row, 1)->text().toInt();

        // Extract DiscountRate (float) from the third column
        float DiscountRate = ui->saletableWidget->item(row, 2)->text().toFloat();

        float totalprice = Quantity * (saleprice * DiscountRate - cost);

        ui->saletableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(totalprice)));
    }
}
void SaleWidget::showthis()
{
    showsqlite();
    showmoney();
    showbutton();
    showtotalmoney();
}

void SaleWidget::on_pushButton_3_clicked()
{
    addDialog->send(numb);
    addDialog->show();
}


void SaleWidget::on_pushButton_clicked()
{
    QString keyword = ui->lineEdit->text();

    // Clear the tableWidget before displaying the new search result
    ui->saletableWidget->clearContents();
    ui->saletableWidget->setRowCount(0);

    // Prepare SQL query to find rows where the name matches the keyword
    QSqlQuery query;
    query.prepare("SELECT orderID, quantity, discountrate, orderDate, contactNumber "
                  "FROM salesRecord WHERE orderID = :ID");
    query.bindValue(":ID", keyword);

    // Execute the query and populate the tableWidget with the result
    if (query.exec()) {
        int row = 0;
        if (query.next()) {
            ui->saletableWidget->insertRow(row);  // Insert a new row in the table

            // Insert each column value into the table widget (first 8 columns)
            for (int col = 0; col < 5; ++col) {
                ui->saletableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
            }
            showmoney();
            showbutton();
        } else {
            QMessageBox::information(this, "提示", "未找到匹配的结果");
        }
    } else {
        QMessageBox::warning(this, "错误", "无法执行查询");
    }
}

void SaleWidget::showtotalmoney()
{
    float total = 0;
    for (int row = 0; row < ui->saletableWidget->rowCount(); ++row) {
        // Extract Quantity (integer) from the second column
        float money = ui->saletableWidget->item(row, 5)->text().toFloat();
        total+=money;
    }
    QString Total = QString::number(total);
    ui->lcdNumber->display(Total);
}

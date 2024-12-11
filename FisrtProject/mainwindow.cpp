#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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


    // 设置tablewidget的初始界面
    productTable = ui->tableWidget;
    productTable->setColumnCount(10);
    QStringList headers;
    headers << "商品名称" << "编号" << "总数量" << "进价（元）" << "售价（元）"
            << "生产厂家" << "生产日期" << "保质期（月）" << "销售数据" << "修改基础信息";
    productTable->setHorizontalHeaderLabels(headers);
    deleteDialog = new DeleteDialog(this); // 初始化DeleteDialog对象
    upDialog = new updateDialog(this);
    infoDialog = new InformationDialog(this);
    sale = new SaleWidget;
    ma = new managewidget;
    showall();
        // 连接deleteDialog的信号与删除操作的槽函数
    connect(deleteDialog, &DeleteDialog::deleteConfirmed, this, &MainWindow::showall);
    connect(ui->SearchpushButton, &QPushButton::clicked, this, &MainWindow::on_SearchpushButton_clicked);
    connect(ui->ReturnpushButton, &QPushButton::clicked, this, &MainWindow::showall);
    connect(infoDialog, &InformationDialog::info, this, &MainWindow::showall);
    // 连接信息更新信号到槽函数
    connect(upDialog, &updateDialog::informationUpdated, this, &MainWindow::showall);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exitpushButton_clicked()
{
    this->close();
}
void MainWindow::showall()
{
    showsql();
    showtable();
}
void MainWindow::showtable()
{
    // 为每一行添加修改按钮，并连接槽函数
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QPushButton *reviseButton = new QPushButton("修改", this);
        ui->tableWidget->setCellWidget(row, ui->tableWidget->columnCount() - 1, reviseButton);
        connect(reviseButton, &QPushButton::clicked, this, &MainWindow::on_reviseButton_clicked);
    }
    //为每行添加更多按钮
    for(int row = 0; row < ui->tableWidget->rowCount(); ++row){
        QPushButton *salesButton = new QPushButton("更多");
        ui->tableWidget->setCellWidget(row, ui->tableWidget->columnCount()-2, salesButton);
        connect(salesButton, &QPushButton::clicked, this, &MainWindow::on_salesButton_clicked);
    }
}
void MainWindow::on_salesButton_clicked()
{
    saleRow = ui->tableWidget->currentRow();
    QString Num = ui->tableWidget->item(saleRow, 1)->text();
    sale->getNum(Num);
    sale->show();
}
void MainWindow::showsql()
{
    // Clear the existing data in the table
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);  // Reset row count to 0

    QSqlQuery query;
    query.prepare("SELECT name, number, total, PurchasePrice, SalePrice, Manufacturer, ProductionDate, QualityDate FROM BasicInfo");

    if (query.exec()) {
        int row = 0;
        while (query.next()) {
            ui->tableWidget->insertRow(row);  // Insert a new row in the table

            // Insert each column value into the table widget
            for (int col = 0; col < 8; ++col) {
                ui->tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
            }

            row++;  // Move to the next row
        }
    } else {
        QMessageBox::warning(this, "错误", "无法加载数据");
    }
}
void MainWindow::on_reviseButton_clicked()
{
    int row = ui->tableWidget->currentRow();
        currentRow = row;
        QStringList currentData;
                for (int col = 0; col < 8; ++col) { // 不包括最后两列的按钮列
                    QTableWidgetItem *item = ui->tableWidget->item(row, col);
                    if (item) {
                        currentData << item->text();
                    } else {
                        currentData << ""; // 如果为空，则添加空字符串
                    }
                }
        QString Num = ui->tableWidget->item(row, 1)->text();
        upDialog->setInformation(currentData); // 将当前信息传递给对话框
        upDialog->getRow(Num);
                       // 显示信息对话框
        upDialog->show();
}


void MainWindow::on_SearchpushButton_clicked()
{
    QString keyword = ui->SearchlineEdit->text();

    // Clear the tableWidget before displaying the new search result
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Prepare SQL query to find rows where the name matches the keyword
    QSqlQuery query;
    query.prepare("SELECT name, number, total, PurchasePrice, SalePrice, Manufacturer, ProductionDate, QualityDate "
                  "FROM BasicInfo WHERE name = :name");
    query.bindValue(":name", keyword);

    // Execute the query and populate the tableWidget with the result
    if (query.exec()) {
        int row = 0;
        if (query.next()) {
            ui->tableWidget->insertRow(row);  // Insert a new row in the table

            // Insert each column value into the table widget (first 8 columns)
            for (int col = 0; col < 8; ++col) {
                ui->tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
            }
            showtable();
        } else {
            QMessageBox::information(this, "提示", "未找到匹配的结果");
        }
    } else {
        QMessageBox::warning(this, "错误", "无法执行查询");
    }
}

void MainWindow::on_ReturnpushButton_clicked()
{
    showall();
}

void MainWindow::on_actionaddNew_triggered()
{
    infoDialog->show();
}

void MainWindow::on_actiondelete_triggered()
{
    // 显示删除对话框
    deleteDialog->show();
}

void MainWindow::on_actionstockmanage_triggered()
{
    ma->show();
}

void MainWindow::on_actionsave_triggered()
{
    showall();
}

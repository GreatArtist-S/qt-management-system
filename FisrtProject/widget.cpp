#include "widget.h"
#include "ui_widget.h"
#include "mainwindow.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("127.0.0");
    db.setDatabaseName("first.db");    // 设置数据库名称
    db.setUserName("root");
    db.setPassword("123456");
    db.open();
    if(!db.open())
    {
            QMessageBox::warning(this,"提示","打开数据库失败");
    }


     ui->lineEdit->setEchoMode(QLineEdit::Password);

    // 显示制作者信息
    connect(ui->pushButton_3, &QPushButton::clicked, [this]()
    {
        QMessageBox::information(this, "信息", "制作者：艺术家三三\n默认用户：root\n默认秘钥：123456");
    });

    // 验证密码并做出相应动作
    connect(ui->pushButton, &QPushButton::clicked, [this]()
    {
        QSqlQuery query;
        QString uname = ui->lineEdit_2->text();
        QString pwd = ui->lineEdit->text();
        query.exec("select * from userinfo where username='"+uname+"' and password='"+pwd+"'");

            if(query.next())
            {
                this->close();  // 关闭当前窗口
                MainWindow *m = new MainWindow;  // 创建 MainWindow 对象
                m->show();  // 显示 MainWindow 窗口
            }
            else
            {
                QMessageBox::information(this, "提示", "用户名或密码错误");
            }
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
    this->close();  // 关闭当前窗口
}

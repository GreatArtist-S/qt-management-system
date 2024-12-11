#include "salescorddialog.h"
#include "ui_salescorddialog.h"

SalescordDialog::SalescordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SalescordDialog)
{
    ui->setupUi(this);
}

SalescordDialog::~SalescordDialog()
{
    delete ui;
}

#include "deletesalerecorddialog.h"
#include "ui_deletesalerecorddialog.h"

deletesalerecordDialog::deletesalerecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletesalerecordDialog)
{
    ui->setupUi(this);
}

deletesalerecordDialog::~deletesalerecordDialog()
{
    delete ui;
}

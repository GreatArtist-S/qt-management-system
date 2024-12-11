#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class SalescordDialog;
}

class SalescordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SalescordDialog(QWidget *parent = nullptr);
    ~SalescordDialog();

private:
    Ui::SalescordDialog *ui;
};

#endif // SEARCHDIALOG_H

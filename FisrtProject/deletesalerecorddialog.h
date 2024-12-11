#ifndef DELETESALERECORDDIALOG_H
#define DELETESALERECORDDIALOG_H

#include <QDialog>

namespace Ui {
class deletesalerecordDialog;
}

class deletesalerecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit deletesalerecordDialog(QWidget *parent = nullptr);
    ~deletesalerecordDialog();

private:
    Ui::deletesalerecordDialog *ui;
};

#endif // DELETESALERECORDDIALOG_H

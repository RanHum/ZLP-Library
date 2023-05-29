#ifndef CREATEAUTHORDIALOG_H
#define CREATEAUTHORDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "requests.h"
#include "api_utils.h"

namespace Ui {
class CreateAuthorDialog;
}

class CreateAuthorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAuthorDialog(QWidget *parent = nullptr);
    ~CreateAuthorDialog();

private slots:
    void on_create_author_button_clicked();

private:
    Ui::CreateAuthorDialog *ui;
    void create_author();
};

#endif // CREATEAUTHORDIALOG_H

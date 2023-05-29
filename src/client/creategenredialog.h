#ifndef CREATEGENREDIALOG_H
#define CREATEGENREDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "requests.h"
#include "api_utils.h"

namespace Ui {
class CreateGenreDialog;
}

class CreateGenreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGenreDialog(QWidget *parent = nullptr);
    ~CreateGenreDialog();

private slots:
    void on_create_genre_button_clicked();

private:
    Ui::CreateGenreDialog *ui;
    void create_genre();
};

#endif // CREATEGENREDIALOG_H

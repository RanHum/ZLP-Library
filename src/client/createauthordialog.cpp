#include "createauthordialog.h"
#include "ui_createauthordialog.h"

CreateAuthorDialog::CreateAuthorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAuthorDialog)
{
    ui->setupUi(this);
}

CreateAuthorDialog::~CreateAuthorDialog()
{
    delete ui;
}

void CreateAuthorDialog::create_author() {
    if (!ui->author_input->text().isEmpty()) {
        auto req = makeReqJson("author", "add");
        req.insert("name", ui->author_input->text());
        const auto resp = RequestClass().sendRequest(req);
        if (check_status(resp)) {
            QMessageBox::information(this, "Уведомление", "Автор успешно создан!");
            this->close();
        }
        else {
            QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
        }
    }
}

void CreateAuthorDialog::on_create_author_button_clicked()
{
    create_author();
}

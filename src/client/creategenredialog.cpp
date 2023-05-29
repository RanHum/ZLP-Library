#include "creategenredialog.h"
#include "ui_creategenredialog.h"

CreateGenreDialog::CreateGenreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGenreDialog)
{
    ui->setupUi(this);
}

CreateGenreDialog::~CreateGenreDialog()
{
    delete ui;
}

void CreateGenreDialog::create_genre() {
    if (!ui->genre_input->text().isEmpty()) {
        auto req = makeReqJson("genre", "add");
        req.insert("name", ui->genre_input->text());
        const auto resp = RequestClass().sendRequest(req);
        if (check_status(resp)) {
            QMessageBox::information(this, "Уведомление", "Жанр успешно создан!");
            this->close();
        }
        else {
            QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
        }
    }
}

void CreateGenreDialog::on_create_genre_button_clicked()
{
    create_genre();
}


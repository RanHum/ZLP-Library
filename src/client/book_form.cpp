#include "book_form.h"
#include "ui_book_form.h"

book_form::book_form(QWidget *parent) : QWidget(parent),
                                        ui(new Ui::book_form)
{
    ui->setupUi(this);
}

book_form::~book_form()
{
    delete ui;
}

void book_form::on_add_button_clicked()
{
    const QString name = ui->name_input->text();
    if (name.trimmed().isEmpty()) {
        QMessageBox::critical(this, "Ошибка!", "Введите название книги!");
    }
    else {
        const QString creation_date = ui->date_input->text();
        const QString description = ui->description_input->text();
        const QString page_count = ui->page_count_input->text();
        int author_id = -1;
        int genre_id = -1;
        const QString author_name = ui->author_select->currentText();
        const QString genre_name = ui->genre_select->currentText();
        for (const auto& author : authors) {
            if (author.name == author_name) {
                author_id = author.id;
                break;
            }
        }

        for (const auto& genre : genres) {
            if (genre.name == genre_name) {
                genre_id = genre.id;
                break;
            }
        }
        emit add_book(name, creation_date, description, page_count, author_id, genre_id);
        this->close();
        ui->name_input->clear();
        ui->date_input->clear();
        ui->description_input->clear();
        ui->page_count_input->clear();
        ui->author_select->clear();
        ui->genre_select->clear();
    }
}

void book_form::get_authors() {
    authors.clear();
    auto req = makeReqJson("author", "get_all");
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp)) {
        QJsonArray resp_json_array = resp["result"].toArray();
        qDebug() << resp_json_array;
        for (const QJsonValue &value : resp_json_array)
        {
            Author author;
            author.id = value["author_id"].toInt();
            author.name = value["name"].toString();
            authors.push_back(author);
        }
    }
}

void book_form::get_genres() {
    genres.clear();
    auto req = makeReqJson("genre", "get_all");
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp)) {
        QJsonArray resp_json_array = resp["result"].toArray();
        for (const QJsonValue &value : resp_json_array)
        {
            Genre genre;
            genre.id = value["genre_id"].toInt();
            genre.name = value["name"].toString();
            genres.push_back(genre);
        }
    }
}

void book_form::set_author_select_values() {
    ui->author_select->clear();
    for (const auto& author : authors) {
        ui->author_select->addItem(author.name);
    }
    ui->author_select->setCurrentIndex(-1);
}

void book_form::set_genre_select_values() {
    ui->genre_select->clear();
    for (const auto& genre : genres) {
        ui->genre_select->addItem(genre.name);
    }
    ui->genre_select->setCurrentIndex(-1);
}

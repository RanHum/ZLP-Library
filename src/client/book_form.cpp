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
    const QString creation_date = ui->date_input->text();
    const QString description = ui->description_input->text();
    const QString page_count = ui->page_count_input->text();
    const QString format = ui->format_input->text();
    const QString authors = ui->author_input->text();
    const QString genres = ui->genre_input->text();
    emit add_book(name, creation_date, description, page_count, format, authors, genres);
    this->close();
    ui->name_input->clear();
    ui->date_input->clear();
    ui->description_input->clear();
    ui->page_count_input->clear();
    ui->format_input->clear();
    ui->author_input->clear();
    ui->genre_input->clear();
}

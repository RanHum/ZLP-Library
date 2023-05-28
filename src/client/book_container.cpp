#include "book_container.h"
#include "ui_book_container.h"

BookContainer::BookContainer(const Book* book, QWidget *parent) : QWidget(parent), ui(new Ui::BookContainer), book(book)
{
    ui->setupUi(this);
    ui->verticalLayout->setContentsMargins(10, 10, 10, 10);
//    ui->title_label->setContentsMargins(10, 0, 10, 0);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);
    ui->title_label->setText(book->name);
    set_detail_label();
}

BookContainer::~BookContainer()
{
    delete ui;
}

void BookContainer::set_detail_label() {
    if (!this->book->name.isEmpty()) {
        ui->detail_label->setText("Название: " + this->book->name + '\n');
    }
    if (!this->book->creation_date.isNull()) {
        ui->detail_label->setText(ui->detail_label->text() + "Год написания: " + QString::number(this->book->creation_date.year()) + '\n');
    }
    if (this->book->page_count != NULL) {
        ui->detail_label->setText(ui->detail_label->text() + "Кол-во страниц: " + QString::number(this->book->page_count) + '\n');
    }
    if (!this->book->description.isEmpty()) {
        ui->detail_label->setText(ui->detail_label->text() + "Описание: " + this->book->description + '\n');
    }
}

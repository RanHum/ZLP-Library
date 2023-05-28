#include "full.h"
#include "ui_full.h"

Full::Full(QWidget *parent) : QWidget(parent),
                              ui(new Ui::Full)
{
    ui->setupUi(this);
    show();
}

Full::~Full()
{
    delete ui;
}

void Full::setDesk(const Desk &desk)
{
    this->desk = desk;
    ui->label->setText(this->desk.name);
}

void Full::mousePressEvent(QMouseEvent *event)
{
    emit clicked(this);
    QWidget::mousePressEvent(event);
}

int Full::getDeskId() {
    return this->desk.id;
}

int Full::getOwner() {
    return this->desk.owner;
}

QString Full::getName() {
    return this->desk.name;
}

Desk Full::getDesk() {
    return this->desk;
}

std::map<int, Book> Full::getBooks() {
    return this->desk.books;
}

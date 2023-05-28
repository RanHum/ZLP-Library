#include "add_book_form.h"

#include <QMessageBox>
#include <QThread>
#include <QListWidget>

BookForm::BookForm(QWidget *parent) : QWidget(parent),
                                      ui(new Ui::BookForm)
{
    ui->setupUi(this);
}

BookForm::~BookForm()
{
    delete ui;
}

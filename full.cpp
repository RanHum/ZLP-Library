#include "full.h"
#include "ui_full.h"

Full::Full(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Full)
{
    ui->setupUi(this);
    show();
}

Full::~Full()
{
    delete ui;
}

void Full::setText(const QString& text) {
    ui->label->setText(text);
}

void Full::on_pushButton_clicked()
{
    emit on_close();
    //close();
}


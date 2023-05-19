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
    emit remove_requested(this);
}

void Full::mousePressEvent(QMouseEvent* event)
{
    emit clicked(this);
    QWidget::mousePressEvent(event);
}

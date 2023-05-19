#include "profile.h"
#include "ui_profile.h"

profile::profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);
}

profile::~profile()
{
    delete ui;
}

void profile::setUserName(const QString& name) {
    ui->name->setText(name);
}

void profile::on_back_button_clicked()
{
    this->close();
}


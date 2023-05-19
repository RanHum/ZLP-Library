#include "doska.h"
#include "ui_doska.h"
#include "bigwindow.h"
#include <QMessageBox>
#include <QThread>
#include <QListWidget>
Doska::Doska(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doska)
{
    ui->setupUi(this);
}

Doska::~Doska()
{
    delete ui;
}


void Doska::on_pushButton_clicked()
{
    QString text = ui->lineEdit_2->text();
    emit signal(text);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    this->close();

}



#include "form.h"
#include "ui_form.h"
#include <QMessageBox>
#include "bigwindow.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    this->close();
    emit firstWindow();
}


void Form::on_pushButton_2_clicked()
{
    QString mail= ui->mail->text();
    QString login2= ui->login2->text();
    QString password2= ui->password2->text();
    QString password3= ui->password3->text();
    if (/*mail=="test" && login2== "test" && password2== "test" && password3== "test"*/
            password2== password3)
    {
        this->close();
        QMessageBox::about(this, "Успех", "Вы зарегистрировались!");
        Bigwindow window;
        window.setModal(true);
        window.exec();


    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", "Вы не зарегистрировались");
    }
}


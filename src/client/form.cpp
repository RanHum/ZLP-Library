#include "form.h"
#include "ui_form.h"
#include <QMessageBox>
#include "requests.h"
#include "api_utils.h"
#include "mainwindow.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
    ui->setupUi(this);
}

Form::~Form() {
    delete ui;
}

void Form::on_registerButton_clicked()
{
    QString mail= ui->mail->text();
    QString login= ui->login->text();
    QString password= ui->password->text();
    QString password2= ui->password2->text();
    if (password == password2) {
        auto req = makeReqJson("user", "register");
        req.insert("name", login);
        req.insert("password", password);
        const auto resp = RequestClass().sendRequest(req);
        qDebug() << check_status(resp);
        if (check_status(resp)) {
            this->close();
            QMessageBox::about(this, "Успех", "Вы зарегистрировались!");
            MainWindow window;
            window.show();
        } else {
            qDebug() << req;
            QMessageBox::critical(this, "Ошибка!", "Вы не зарегистрировались!");
        }
    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", "Пароли не совпадают!");
    }
}


void Form::on_haveAccountButton_clicked()
{
    this->close();
    emit firstWindow();
}


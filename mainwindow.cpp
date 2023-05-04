#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "bigwindow.h"
#include <QThread>
MainWindow::MainWindow(QWidget *parent)
    :
      QMainWindow(parent)

    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    form = new Form();
    connect(form, &Form::firstWindow, this, &MainWindow::show);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    form->show();
    this->close();
}


void MainWindow::on_pushButton_2_clicked()
{
    QString login= ui->login->text();
    QString password= ui->password->text();
    if (login== "test" && password== "test")
    {

        //QThread::sleep(2);
        ui->statusbar->showMessage("Вы успешно авторизовались!");
        //this->thread()->sleep(2);
        this->close();
        Bigwindow window;
        window.setModal(true);
        window.exec();

    }
    else
    {
        ui->statusbar->showMessage("Ошибка! Вы не авторизованы.");
    }
}

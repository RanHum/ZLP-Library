#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "bigwindow.h"
#include <QThread>
#include <requests.h>
#include <api_utils.h>

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

void delay(int ms) {
	QTime dieTime = QTime::currentTime().addMSecs(ms);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString login= ui->login->text();
    QString password= ui->password->text();
    Connection::getInstance().setServer("localhost", 33333);
	auto req = makeReqJson("user", "login");
    req.insert("name", login);
    req.insert("password", password);
    const auto resp = RequestClass().sendRequest(req);
	if (resp["status"].toString() == "Success") {
        ui->statusbar->showMessage("Вы успешно авторизовались!");
		UserCredentials::instance().setLogin(login);
		UserCredentials::instance().setPassword(password);
		UserCredentials::instance().setUserId(resp["result"]["user_id"].toInt());
		UserCredentials::instance().setAvatar(resp["result"]["avatar"].toString());
        qDebug() << "logged in as" << UserCredentials::instance().login();
		delay(1000);
        this->close();
        Bigwindow window;
        window.setModal(true);
        window.exec();
	} else {
		ui->statusbar->showMessage("Ошибка! Вы не авторизованы.");
	}
}

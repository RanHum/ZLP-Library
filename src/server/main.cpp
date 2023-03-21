#include "mytcpserver.h"
#include "db_server.h"
#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <QThread>

int main(int argc, char *argv[])
{
    auto a = new QCoreApplication(argc, argv);

    MyTcpServer server;
	while(!DB_Server::get()->init()) QThread::msleep(100);
    qDebug() << "Database connection success!";

	QObject::connect(a, SIGNAL(aboutToQuit()), &server, SLOT(close()));
	QObject::connect(a, SIGNAL(aboutToQuit()), DB_Server::get(), SLOT(close()));

	return a->exec();
}

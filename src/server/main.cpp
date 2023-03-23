#include "mytcpserver.h"
#include "db_server.h"
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

int main(int argc, char *argv[])
{
    auto a = new QCoreApplication(argc, argv);

	while(!DB_Server::get()->init()) QThread::msleep(100);
    qDebug() << "Database connection success!";
    MyTcpServer server;

	QObject::connect(a, SIGNAL(aboutToQuit()), &server, SLOT(close()));
	QObject::connect(a, SIGNAL(aboutToQuit()), DB_Server::get(), SLOT(close()));

	return a->exec();
}

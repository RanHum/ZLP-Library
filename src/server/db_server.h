#ifndef DB_SERVER_H
#define DB_SERVER_H

#include <QSqlQuery>
#include <QObject>
#include <QDebug>
#include <QSqlError>
#include <zlp-commons.h>

class DB_Server : public QObject {
	Q_OBJECT
	static DB_Server *instance;
	QSqlDatabase db;
	QString db_host = "postgres";
	QString db_name = "zlplib";
	QString db_user = "zlplib";
	QString db_pass = "zlplibpass";
	int db_port = 5432;

public:
	static DB_Server *get() {
		return instance ? instance : instance = new DB_Server();
	}
	bool init(
		const QString host = "",
		const int port = 0,
		const QString database_name = "",
		const QString user = "",
		const QString pass = "")
	{
		db = QSqlDatabase::addDatabase("QPSQL");
		db.setHostName(db_host = host.isEmpty() ? db_host : host);
		db.setDatabaseName(db_name = database_name.isEmpty() ? db_name : database_name);
		db.setUserName(db_user = user.isEmpty() ? db_user : user);
		db.setPassword(db_pass = pass.isEmpty() ? db_pass : pass);
		db.setPort(db_port = port ? port : db_port);
		bool status = db.open();
		if (!status)
			qDebug() << db.lastError().text();
		return status;
	}
	QSqlQuery query_simple(const QString q) {
		QSqlQuery query;
		query.exec(q);
		return query;
	}
public slots:
	void close() {
		db.close();
		this->~DB_Server();
		instance = nullptr;
	}
};

#endif // DB_SERVER_H

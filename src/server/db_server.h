#ifndef DB_SERVER_H
#define DB_SERVER_H
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <QDebug>
#include <QSqlError>

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
	static DB_Server *get();
	bool init(
		const QString host = "",
		const int port = 0,
		const QString database_name = "",
		const QString user = "",
		const QString pass = "");

	QSqlQuery query_simple(const QString q);
	QSqlQuery query_prepare(const QString q);
public slots:
	void close();
};

#endif // DB_SERVER_H

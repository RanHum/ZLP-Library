#include <db_server.h>

DB_Server *DB_Server::instance = nullptr;

///doxygen documentation

bool DB_Server::init(
		const QString host,
		const int port,
		const QString database_name,
		const QString user,
		const QString pass) {
  db = QSqlDatabase::addDatabase("QPSQL");
  db.setHostName(db_host = host.isEmpty() ? db_host : host);
  db.setDatabaseName(db_name = database_name.isEmpty() ? db_name : database_name);
  db.setUserName(db_user = user.isEmpty() ? db_user : user);
  db.setPassword(db_pass = pass.isEmpty() ? db_pass : pass);
  db.setPort(db_port = port ? port : db_port);
  if (!db.open() && db.lastError().isValid()) {
    qDebug() << "Error loading database:" << db.lastError();
    return false;
  }
  return true;
}

QSqlQuery DB_Server::query_simple(const QString q) {
  QSqlQuery query;
  query.exec(q);
  return query;
}

QSqlQuery DB_Server::query_prepare(const QString q) {
  QSqlQuery query;
  query.prepare(q);
  return query;
}

static DB_Server *DB_Server::get() {
  return instance ? instance : instance = new DB_Server();
}

void DB_Server::close() {
  db.close();
  this->~DB_Server();
  instance = nullptr;
}

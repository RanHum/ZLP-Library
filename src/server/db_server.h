#ifndef DB_SERVER_H
#define DB_SERVER_H
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QObject>
#include <QDebug>
#include <QSqlError>

/*!
 * \brief The DB_Server class provides an interface for interacting with a database server.
 */
class DB_Server : public QObject
{
	Q_OBJECT
	static DB_Server *instance;
	QSqlDatabase db;
	QString db_host = "postgres";		/*!< The hostname of the database server. */
	QString db_name = "zlplib";			/*!< The name of the database. */
	QString db_user = "zlplib";			/*!< The username for accessing the database. */
	QString db_pass = "zlplibpass"; /*!< The password for accessing the database. */
	int db_port = 5432;							/*!< The port number for the database server. */

public:
	/*!
	 * \brief Retrieves the singleton instance of DB_Server.
	 *
	 * \return A pointer to the DB_Server instance.
	 */
	static DB_Server *get()
	{
		return instance ? instance : instance = new DB_Server();
	}
	/*!
	 * \brief Adds a PostgreSQL database, sets DB parameters, and reports the condition of DB loading.
	 *
	 * \param host The host of the database.
	 * \param port The port of the database.
	 * \param database_name The name of the database.
	 * \param user The username for connecting to the database.
	 * \param pass The password for connecting to the database.
	 *
	 * \return True if the database is successfully loaded, false otherwise.
	 */
	bool init(
			const QString host = "",
			const int port = 0,
			const QString database_name = "",
			const QString user = "",
			const QString pass = "");

	/*!
	 * \brief Makes a simple query to the database.
	 *
	 * \param q The SQL query string.
	 *
	 * \return The QSqlQuery object representing the result of the query.
	 */
	QSqlQuery query_simple(const QString q);
	/*!
	 * \brief Makes a complex query to the database using "prepare" parameter.
	 *
	 * \param q The SQL query string.
	 *
	 * \return The QSqlQuery object representing the prepared query.
	 */
	QSqlQuery query_prepare(const QString q);
public slots:
	/*!
	 * \brief Closes the connection with the database.
	 */
	void close();
};

#endif // DB_SERVER_H

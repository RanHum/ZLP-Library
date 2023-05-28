#pragma once

#include <QTcpSocket>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>

/*!
 * \brief The Connection class represents a TCP connection configuration.
 */
class Connection
{
public:
	/*!
	 * \brief Returns the singleton instance of the Connection class.
	 *
	 * \return The singleton instance of Connection.
	 */
	static Connection &getInstance()
	{
		static Connection instance;
		return instance;
	}

	/*!
	 * \brief Sets the server host name and port for the connection.
	 *
	 * \param hostName The server host name.
	 * \param port The server port.
	 */
	void setServer(const QString &hostName, quint16 port)
	{
		m_hostName = hostName;
		m_port = port;
	}

	/*!
	 * \brief Returns the server host name.
	 *
	 * \return The server host name.
	 */
	QString getHostName() const
	{
		return m_hostName;
	}

	/*!
	 * \brief Returns the server port.
	 *
	 * \return The server port.
	 */
	quint16 getPort() const
	{
		return m_port;
	}

private:
	Connection() {}
	~Connection() {}

	QString m_hostName; /*!< The server host name. */
	quint16 m_port;			/*!< The server port. */
};

/*!
 * \brief The RequestClass class handles sending requests and receiving responses over a TCP socket.
 */
class RequestClass : public QObject
{
	Q_OBJECT

public:
	/*!
	 * \brief Constructs a RequestClass object.
	 *
	 * \param parent The parent object.
	 */

	RequestClass(QObject *parent = nullptr);
	/*!
	 * \brief Destroys the RequestClass object.
	 */
	~RequestClass();

	/*!
	 * \brief Sends a request over the TCP socket and waits for a response.
	 *
	 * \param request The request to send.
	 * \return The response received from the server.
	 */
	QJsonObject sendRequest(const QJsonObject &request);
	/*!
	 * \brief Retrieves the response as a QJsonObject.
	 *
	 * \return The response as a QJsonObject.
	 */
	QJsonObject getResponse();

signals:
	/*!
	 * \brief Signals that the request has finished.
	 */
	void requestFinished();

private slots:
	/*!
	 * \brief Handles the connected signal of the socket.
	 */
	void onConnected();

	/*!
	 * \brief Handles the readyRead signal of the socket.
	 */
	void onReadyRead();

	/*!
	 * \brief Handles socket errors.
	 *
	 * \param socketError The socket error.
	 */
	void onError(QAbstractSocket::SocketError socketError);

private:
	QTcpSocket *m_socket;			 /*!< The TCP socket used for communication. */
	QByteArray m_responseBody; /*!< The response body received from the server. */
};

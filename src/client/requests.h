#pragma once

#include <QTcpSocket>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>

class Connection
{
public:
	static Connection& getInstance()
	{
		static Connection instance;
		return instance;
	}

	void setServer(const QString &hostName, quint16 port)
	{
		m_hostName = hostName;
		m_port = port;
	}

	QString getHostName() const
	{
		return m_hostName;
	}

	quint16 getPort() const
	{
		return m_port;
	}

private:
	Connection() {}
	~Connection() {}

	QString m_hostName;
	quint16 m_port;
};

class RequestClass : public QObject
{
	Q_OBJECT

public:
	RequestClass(QObject *parent = nullptr);
	~RequestClass();

	QJsonObject sendRequest(const QJsonObject &request);
	QJsonObject getResponse();

signals:
	void requestFinished();

private slots:
	void onConnected();
	void onReadyRead();
	void onError(QAbstractSocket::SocketError socketError);

private:
	QTcpSocket *m_socket;
	QByteArray m_responseBody;
};

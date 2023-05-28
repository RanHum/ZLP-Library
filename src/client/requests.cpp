#include "requests.h"

RequestClass::RequestClass(QObject *parent) : QObject(parent)
{
	m_socket = new QTcpSocket(this);
}


RequestClass::~RequestClass()
{
}

QJsonObject RequestClass::sendRequest(const QJsonObject &request)
{
	const QString hostName = Connection::getInstance().getHostName();
	const quint16 port = Connection::getInstance().getPort();

	m_socket->connectToHost(hostName, port);

	if (!m_socket->waitForConnected())
	{
		emit requestFinished();
		return getResponse();
	}

	const QByteArray requestBody = QJsonDocument(request).toJson(QJsonDocument::Compact);
	qDebug() << QString(requestBody);
	m_socket->write(requestBody);

	if (!m_socket->waitForBytesWritten())
	{
		emit requestFinished();
		return getResponse();
	}

	if (!m_socket->waitForReadyRead())
	{
		emit requestFinished();
		return getResponse();
	}

	m_responseBody = m_socket->readAll().trimmed();
	qDebug() << QString(m_responseBody);
	emit requestFinished();
	return getResponse();
}

QJsonObject RequestClass::getResponse()
{
	const QJsonObject response = QJsonDocument::fromJson(m_responseBody).object();
    qDebug() << response;
	return response;
}


void RequestClass::onConnected()
{
}


void RequestClass::onReadyRead()
{
}


void RequestClass::onError(QAbstractSocket::SocketError socketError)
{
}

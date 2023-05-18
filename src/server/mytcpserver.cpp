/*! 
\file 
\brief file with methods for the interaction of the socket and server

In this file realised methods that creates and desctructs TCP server and sockets, also that reads information from socket and converts it to the desired form
*/

#include "mytcpserver.h"
#include "parser.h"
#include <QCoreApplication>

/*!
\brief responsible for tcp connection between socket and server
*/

MyTcpServer::~MyTcpServer()
{
    foreach (int i, SClients.keys()) {
        SClients[i]->close();
        SClients.remove(i);
    }
    mTcpServer->close();
    server_status=0;
}

/*!
\brief responsible for TCPServer's working

It's creates new TCPServer, listens port 33333 and reports about server condition
*/

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "Server failed to start, port is occupied or blocked";
    } else {
        server_status=1;
        qDebug() << "Server started";
    }
}
/*!
\brief creates new slot connection

If server is started, creates a slot connection
*/

void MyTcpServer::slotNewConnection(){
    if(server_status==1) {
        QTcpSocket* clientSocket = mTcpServer->nextPendingConnection();
        int user_socket_id = clientSocket->socketDescriptor();
        SClients[user_socket_id] = clientSocket;
        connect(SClients[user_socket_id], &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(SClients[user_socket_id], &QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
    }
}
/*!
\brief reads byte array from server slot

Reads information (byte array) from clientSocket and writes it in execute_line
*/
void MyTcpServer::slotServerRead(){
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
	QByteArray array;
    while (clientSocket->bytesAvailable() > 0)
		array = clientSocket->readAll().trimmed();
    if (!array.isEmpty()) {
	    clientSocket->write(execute_line(array));
	    clientSocket->write("\r\n");
    }
}
/*!
\brief closes included socket

Closes client's Socket, removes user's socket id
*/
void MyTcpServer::slotClientDisconnected(){
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    int user_socket_id = clientSocket->socketDescriptor();
    clientSocket->close();
    SClients.remove(user_socket_id);
}
/*!
\brief deactivates Server
*/
void MyTcpServer::close() {
    this->~MyTcpServer();
    QCoreApplication::quit();
}

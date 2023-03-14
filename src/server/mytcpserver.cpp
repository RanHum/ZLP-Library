#include "mytcpserver.h"
#include "parser.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>

MyTcpServer::~MyTcpServer()
{
    foreach (int i, SClients.keys()) {
        SClients[i]->close();
        SClients.remove(i);
    }
    mTcpServer->close();
    server_status=0;
}
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
    if(server_status==1){
        QTcpSocket* clientSocket = mTcpServer->nextPendingConnection();
        int user_socket_id = clientSocket->socketDescriptor();
        SClients[user_socket_id] = clientSocket;
        connect(SClients[user_socket_id], &QTcpSocket::readyRead,
                this,&MyTcpServer::slotServerRead);
        connect(SClients[user_socket_id], &QTcpSocket::disconnected,
                this,&MyTcpServer::slotClientDisconnected);
    }
}

void MyTcpServer::slotServerRead(){
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    std::string mystr;
    while(clientSocket->bytesAvailable()>0)
    {
        QByteArray array = clientSocket->readAll();
        mystr = array.trimmed().toStdString();
    }
    parser(mystr, clientSocket);
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    int user_socket_id = clientSocket->socketDescriptor();
    clientSocket->close();
    SClients.remove(user_socket_id);
}

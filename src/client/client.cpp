#include "client.h"

Client::Client(QObject *parent) : QObject(parent){
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket -> connectToHost("127.0.0.1", 33333);
    connect(mTcpSocket, &QTcpSocket::readyRead,
            this, &Client::slotServerRead);

}
Client* Client::getInstance(){
    if (!p_instance)
    {
        p_instance = new Client();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

void Client::send_msg_to_server(QString query){
    mTcpSocket->write(query.toUtf8());
}

void Client::slotServerRead(){
    QString msg = "";
    while(mTcpSocket->bytesAvailable()>0)
    {
        msg.append(mTcpSocket->readAll());
    }
    qDebug()<<msg;

    emit message_from_server(msg);
}


Client::~Client(){
    mTcpSocket->close();
};

Client* Client::p_instance;
ClientDestroyer Client::destroyer;

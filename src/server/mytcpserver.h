/*! 
\file 
\brief header file for mytcpserver.cpp
*/
#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QTcpServer>
#include <QTcpSocket>
/*!
responsible for tcp connection between socket and server
*/
class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void close();
    void slotNewConnection();
    void slotClientDisconnected();

    void slotServerRead();
private:
    QTcpServer * mTcpServer;
    int server_status;
    QMap<int, QTcpSocket*> SClients;
};
#endif // MYTCPSERVER_H

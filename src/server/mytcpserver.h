#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QTcpServer>
#include <QTcpSocket>

/*!
 * \brief The MyTcpServer class represents a TCP server.
 */
class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    /*!
     * \brief Closes the server and quits the application.
     */
    void close();

    /*!
     * \brief Slot for handling new client connections.
     */
    void slotNewConnection();

    /*!
 * \brief Slot for handling client disconnections.
 Closes client's Socket, removes user's socket id
 */
    void slotClientDisconnected();

    /*!
     * \brief Slot for handling data received from clients.
     Reads information (byte array) from clientSocket and writes it in execute_line
     */
    void slotServerRead();

private:
    QTcpServer *mTcpServer;
    int server_status;
    QMap<int, QTcpSocket *> SClients;
};
#endif // MYTCPSERVER_H

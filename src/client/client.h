
#ifndef CLIENT_H
#define CLIENT_H

#include <QDebug>
#include <QObject>
#include <QByteArray>
#include <QString>
#include <QTcpSocket>

class Client;

class ClientDestroyer
{
private:
    Client * p_instance;
public:
    ~ClientDestroyer() { delete p_instance; }
    void initialize(Client * p) { p_instance = p; };
};


class Client : public QObject
{
    Q_OBJECT
private:
    static Client * p_instance;
    static ClientDestroyer destroyer;
    QTcpSocket * mTcpSocket;
protected:
    explicit Client(QObject *parent = nullptr);
    Client(const Client& ) = delete;
    Client& operator = (Client &) = delete;
    ~Client();
    friend class ClientDestroyer;
public:
    static Client* getInstance();
    void send_msg_to_server(QString query);
signals:
    void message_from_server(QString msg);
private slots:
    void slotServerRead();

};

#endif // CLIENT_H

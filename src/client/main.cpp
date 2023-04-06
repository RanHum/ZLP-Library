
#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SingletonClient::getInstance();
    SingletonClient::getInstance()->send_msg_to_server("{\"_domain\":\"user\", \"_intent\":\"register\"}");
    return a.exec();
}

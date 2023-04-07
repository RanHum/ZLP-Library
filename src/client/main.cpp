
#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Client::getInstance()->send_msg_to_server("{\"_domain\":\"user\",\"_intent\":\"get\",\"_as_user_id\":1, \"_with_password\":\"hello kitty\", \"user_id\":1}");
    return a.exec();
}

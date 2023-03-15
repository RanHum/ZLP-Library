
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QTcpSocket>
#include <zlp-commons.h>


std::string authorization(Parameters data);
std::string registration(Parameters data);
std::string send_message(Parameters data);
std::string make_evaluation(Parameters data);
std::string add_bookmark(Parameters data);
std::string create_desk(Parameters data);
std::string delete_desk(Parameters data);
std::string add_book(Parameters data);
std::string delete_book(Parameters data);
std::string invite_user(Parameters data);
std::string kick_user(Parameters data);
std::string accept_invite(Parameters data);
std::string cancel_invite(Parameters data);

bool fields_exist(Parameters data, std::vector<std::string> fields);

#endif // FUNCTIONS_H

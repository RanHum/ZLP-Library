
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <zlp-commons.h>

std::string authorization(std::string command, Parameters data);
std::string registration(std::string command, Parameters data);
std::string send_message(std::string command, Parameters data);
std::string make_evaluation(std::string command, Parameters data);
std::string add_bookmark(std::string command, Parameters data);
std::string create_desk(std::string command, Parameters data);
std::string delete_desk(std::string command, Parameters data);
std::string add_book(std::string command, Parameters data);
std::string delete_book(std::string command, Parameters data);
std::string invite_user(std::string command, Parameters data);
std::string kick_user(std::string command, Parameters data);
std::string accept_invite(std::string command, Parameters data);
std::string cancel_invite(std::string command, Parameters data);

#endif // FUNCTIONS_H


#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <QTcpSocket>

std::string authorization(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string registration(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string send_message(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string make_evaluation(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string add_bookmark(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string create_desk(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string delete_desk(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string add_book(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string delete_book(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string invite_user(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string kick_user(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string accept_invite(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string cancel_invite(std::map<std::string, std::string> data, QTcpSocket *clientSocket);

#endif // FUNCTIONS_H

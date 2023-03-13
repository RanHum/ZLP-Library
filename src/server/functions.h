
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <string>
#include <QTcpSocket>

std::string authorization(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string registration(std::map<std::string, std::string> data, QTcpSocket *clientSocket);
std::string sendMessage(std::map<std::string, std::string> data, QTcpSocket *clientSocket);

#endif // FUNCTIONS_H

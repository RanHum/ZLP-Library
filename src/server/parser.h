
#ifndef PARSER_H
#define PARSER_H

#include <QTcpSocket>

void parser(std::string line, QTcpSocket *clientSocket);
void commandRecognizer(std::vector<std::string> request, QTcpSocket *clientSocket);

#endif // PARSER_H

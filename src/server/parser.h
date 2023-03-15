
#ifndef PARSER_H
#define PARSER_H

#include <QTcpSocket>
#include <api_keywords.h>

void parser(QString line, QTcpSocket *clientSocket);
void commandRecognizer(std::string command, Parameters request, QTcpSocket *clientSocket);


#endif // PARSER_H

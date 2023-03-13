#include <string>
#include <iostream>
#include <functions.h>
#include <api_keywords.h>


void parser(std::string line, QTcpSocket *clientSocket);
void commandRecognizer(std::string command, std::map<std::string, std::string> request, QTcpSocket *clientSocket);


void parser(std::string line, QTcpSocket *clientSocket)
{
    int pos = line.find('?');
    if (line == "") return;
    if (pos == -1)
    {
        clientSocket->write("Invalid data!\r\n");
        return;
    }
    std::string command = line.substr(0, pos);
    line.erase(0, pos + 1);

    std::map<std::string, std::string> req;
    std::string key = "";
    std::string value = "";
    bool isKey = true;
    for (auto i : line)
    {
        if (i == '=') {
            isKey = false;
        }
        else if (i == '&') {
            req.insert(std::make_pair(key, value));
            key = "";
            value = "";
            isKey = true;
        }
        else if (isKey)
        {
            key += i;
        }
        else {
            value += i;
        }
    }
    req.insert(std::make_pair(key, value));
    commandRecognizer(command, req, clientSocket);
}

void commandRecognizer(std::string command, std::map<std::string, std::string> request, QTcpSocket *clientSocket)
{
    if (command == AUTHORIZATION)
    {
        std::string result = authorization(request, clientSocket);
        if (result.size() != 0) clientSocket->write(QByteArray::fromStdString(result));
    }
    else if (command == REGISTRATION)
    {
        std::string result = registration(request, clientSocket);
        if (result.size() != 0) clientSocket->write(QByteArray::fromStdString(result));
    }
    else if (command == SEND_MESSAGE)
    {
        std::string result = sendMessage(request, clientSocket);
        if (result.size() != 0) clientSocket->write(QByteArray::fromStdString(result));
    }
    else
    {
        clientSocket->write("Invalid data!\r\n");
    }
}

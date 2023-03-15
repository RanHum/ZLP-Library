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
    if (command_function_map.find(command) != command_function_map.end()) {
        std::string result = command_function_map.at(command)(request, clientSocket);
        if (result.size() != 0) clientSocket->write(QByteArray::fromStdString(result));
    }
    else
    {
        clientSocket->write("Invalid data!\r\n");
    }
}

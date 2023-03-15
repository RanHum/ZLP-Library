#include <functions.h>
#include <parser.h>
#include <QRegularExpression>


void parser(QString line, QTcpSocket *clientSocket)
{
    int pos = line.indexOf('?');
    if (line.isEmpty()) return;
    if (pos == -1)
    {
        clientSocket->write("Invalid data!\r\n");
        return;
    }
    QRegularExpression command_regex("^[^?]+");
    QRegularExpression params_regex("([^&]+)=([^&]+)");
    QRegularExpressionMatch match = command_regex.match(line);
    QString command;
    if (match.hasMatch()) {
        command = match.captured(0);
    }
    else {
        clientSocket->write("Invalid data!\r\n");
        return;
    }
    QString params_str = line.mid(pos + 1);
    std::map<std::string, std::string> params;
    QRegularExpressionMatchIterator it = params_regex.globalMatch(params_str);
    while (it.hasNext()) {
        match = it.next();
        params.insert(std::make_pair(match.captured(1).toStdString(), match.captured(2).toStdString()));
    }
    commandRecognizer(command.toStdString(), params, clientSocket);
}

void commandRecognizer(std::string command, Parameters request, QTcpSocket *clientSocket)
{
    if (command_function_map.find(command) != command_function_map.end()) {
        std::string result = command_function_map.at(command)(request);
        if (result.size() != 0) clientSocket->write(QByteArray::fromStdString(result));
    }
    else
    {
        clientSocket->write("Invalid data!\r\n");
    }
}

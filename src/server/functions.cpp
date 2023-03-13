#include <functions.h>

std::string authorization(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("login") == data.end() || data.find("password") == data.end()) return "Invalid data!\r\n";
    if (data.at("login").empty() || data.at("password").empty()) return "Invalid data!\r\n";
    clientSocket->write("login: " + QByteArray::fromStdString(data["login"]) + "\r\n");
    clientSocket->write("password: " + QByteArray::fromStdString(data["password"]) + "\r\n");
    return "";
}

std::string registration(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("login") == data.end() || data.find("password") == data.end()) return "Invalid data!\r\n";
    if (data.at("login").empty() || data.at("password").empty()) return "Invalid data!\r\n";
    clientSocket->write("login: " + QByteArray::fromStdString(data["login"]) + "\r\n");
    clientSocket->write("password: " + QByteArray::fromStdString(data["password"]) + "\r\n");
    return "";
}

std::string sendMessage(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("message") == data.end() || data.at("message").empty()) return "Invalid data!\r\n";
    clientSocket->write("message: " + QByteArray::fromStdString(data["message"]) + "\r\n");
    return "";
}

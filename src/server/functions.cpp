#include <functions.h>

std::string authorization(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("login") == data.end() || data.find("password") == data.end())
        return "Invalid data!\r\n";
    if (data.at("login").empty() || data.at("password").empty())
        return "Invalid data!\r\n";
    clientSocket->write("login: " + QByteArray::fromStdString(data["login"]) + "\r\n");
    clientSocket->write("password: " + QByteArray::fromStdString(data["password"]) + "\r\n");
    return "";
}

std::string registration(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("login") == data.end() || data.find("password") == data.end())
        return "Invalid data!\r\n";
    if (data.at("login").empty() || data.at("password").empty())
        return "Invalid data!\r\n";
    clientSocket->write("login: " + QByteArray::fromStdString(data["login"]) + "\r\n");
    clientSocket->write("password: " + QByteArray::fromStdString(data["password"]) + "\r\n");
    return "";
}

std::string send_message(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("message") == data.end() || data.at("message").empty())
        return "Invalid data!\r\n";
    clientSocket->write("message: " + QByteArray::fromStdString(data["message"]) + "\r\n");
    return "";
}

std::string make_evaluation(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("evaluation") == data.end() || data.at("evaluation").empty())
        return "Invalid data!\r\n";
    clientSocket->write("evaluation: " + QByteArray::fromStdString(data["evaluation"]) + " added\r\n");
    return "";
}

std::string add_bookmark(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("book_id") == data.end() || data.at("book_id").empty())
        return "Invalid data!\r\n";
    clientSocket->write("book_id: " + QByteArray::fromStdString(data["book_id"]) + " added to bookmark\r\n");
    return "";
}

std::string create_desk(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("desk_name") == data.end() || data.at("desk_name").empty())
        return "Invalid data!\r\n";
    clientSocket->write("desk_name: " + QByteArray::fromStdString(data["desk_name"]) + " created\r\n");
    return "";
}

std::string delete_desk(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("desk_name") == data.end() || data.at("desk_name").empty())
        return "Invalid data!\r\n";
    clientSocket->write("desk_name: " + QByteArray::fromStdString(data["desk_name"]) + " deleted\r\n");
    return "";
}

std::string add_book(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("book_name") == data.end() || data.at("book_name").empty())
        return "Invalid data!\r\n";
    clientSocket->write("book_name: " + QByteArray::fromStdString(data["book_name"]) + " added\r\n");
    return "";
}

std::string delete_book(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("book_name") == data.end() || data.at("book_name").empty())
        return "Invalid data!\r\n";
    clientSocket->write("book_name: " + QByteArray::fromStdString(data["book_name"]) + " deleted\r\n");
    return "";
}

std::string invite_user(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("user_id") == data.end() || data.at("user_id").empty())
        return "Invalid data!\r\n";
    clientSocket->write("user_id: " + QByteArray::fromStdString(data["user_id"]) + " invited\r\n");
    return "";
}

std::string kick_user(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("user_id") == data.end() || data.at("user_id").empty())
        return "Invalid data!\r\n";
    clientSocket->write("user_id: " + QByteArray::fromStdString(data["user_id"]) + " kicked\r\n");
    return "";
}

std::string accept_invite(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("status") == data.end() || data.at("status").empty())
        return "Invalid data!\r\n";
    clientSocket->write("status: " + QByteArray::fromStdString(data["status"]) + "\r\n");
    return "";
}
std::string cancel_invite(std::map<std::string, std::string> data, QTcpSocket *clientSocket) {
    if (data.find("status") == data.end() || data.at("status").empty())
        return "Invalid data!\r\n";
    clientSocket->write("status: " + QByteArray::fromStdString(data["status"]) + "\r\n");
    return "";
}

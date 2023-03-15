#include <functions.h>


std::string authorization(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"login", "password"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?login=" + (data["login"]) + "&password=" + (data["password"]);
}

std::string registration(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"login", "password"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?login=" + (data["login"]) + "&password=" + (data["password"]);
}

std::string send_message(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"message"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?message=" + (data["message"]);
}

std::string make_evaluation(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"evaluation"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?evaluation=" + (data["evaluation"]);
}

std::string add_bookmark(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"book_id"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?book_id=" + (data["book_id"]);
}

std::string create_desk(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"desk_name"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?desk_name=" + (data["desk_name"]);
}

std::string delete_desk(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"desk_name"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?desk_name=" + (data["desk_name"]);
}

std::string add_book(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"book_name"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?book_name=" + (data["book_name"]);
}

std::string delete_book(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"book_name"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?book_name=" + (data["book_name"]);
}

std::string invite_user(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"user_id"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?user_id=" + (data["user_id"]);
}

std::string kick_user(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"user_id"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?user_id=" + (data["user_id"]);
}

std::string accept_invite(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"status"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?status=" + (data["status"]);
}
std::string cancel_invite(std::map<std::string, std::string> data) {
    std::vector<std::string> fields = {"status"};
    if (!fields_exist(data, fields)) return "error\r\n";
    return "success?status=" + (data["status"]);
}

bool fields_exist(Parameters data, std::vector<std::string> fields) {
    for (auto& field : fields) {
        if (data.find(field) == data.end() || data.at(field).empty())
            return false;
    }
    return true;
}

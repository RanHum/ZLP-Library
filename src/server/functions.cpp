#include <api_keywords.h>
#include <functions.h>
#include <db_server.h>

std::string authorization(std::string command, Parameters data) {
	return "success?user_id=1";
}

std::string registration(std::string command, Parameters data) {
    return "success?login=" + (data["login"]) + "&password=" + (data["password"]);
}

std::string send_message(std::string command, Parameters data) {
    return "success?message=" + (data["message"]);
}

std::string make_evaluation(std::string command, Parameters data) {
    return "success";
}

std::string add_bookmark(std::string command, Parameters data) {
    return "success?book_id=" + (data["book_id"]);
}

std::string create_desk(std::string command, Parameters data) {
    return "success?desk_id=" + (data["desk_id"]);
}

std::string delete_desk(std::string command, Parameters data) {
    return "success";
}

std::string add_book(std::string command, Parameters data) {
    return "success?book_id=" + (data["book_id"]);
}

std::string delete_book(std::string command, Parameters data) {
    return "success?book_id=" + (data["book_id"]);
}

std::string invite_user(std::string command, Parameters data) {
    return "success";
}

std::string kick_user(std::string command, Parameters data) {
    return "success";
}

std::string accept_invite(std::string command, Parameters data) {
    return "success?status=" + (data["status"]);
}
std::string cancel_invite(std::string command, Parameters data) {
    return "success?status=" + (data["status"]);
}


#ifndef API_KEYWORDS_H
#define API_KEYWORDS_H
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <zlp-commons.h>

const std::string
    API_ROUTE_AUTHORIZATION = "auth",
    API_ROUTE_REGISTRATION = "reg",
    API_ROUTE_SEND_MESSAGE = "message",
    API_ROUTE_MAKE_EVALUATION = "evaluation_make",
    API_ROUTE_ADD_BOOKMARK = "bookmark_add",
    API_ROUTE_CREATE_DESK = "desk_create",
    API_ROUTE_DELETE_DESK = "desk_delete",
    API_ROUTE_ADD_BOOK = "book_add",
    API_ROUTE_DELETE_BOOK = "book_delete",
    API_ROUTE_INVITE_USER = "user_invite",
    API_ROUTE_KICK_USER = "user_kick",
    API_ROUTE_ACCEPT_INVITE = "invite_accept",
    API_ROUTE_CANCEL_INVITE = "invite_cancel";

const std::map<std::string, std::vector<std::string>>
	command_requirements_map = {
		{API_ROUTE_AUTHORIZATION, {"login", "password"}},
		{API_ROUTE_REGISTRATION, {"login", "password"}},
		{API_ROUTE_SEND_MESSAGE, {"message", "user_id"}},
		{API_ROUTE_MAKE_EVALUATION, {"evaluation_mark"}},
		{API_ROUTE_ADD_BOOKMARK, {"book_id, desk_id"}},
		{API_ROUTE_CREATE_DESK, {"desk_name"}},
		{API_ROUTE_DELETE_DESK, {"book_id"}},
		{API_ROUTE_ADD_BOOK, {"book_name"}},
		{API_ROUTE_DELETE_BOOK, {"book_id"}},
		{API_ROUTE_INVITE_USER, {"user_id", "desk_id"}},
		{API_ROUTE_KICK_USER, {"user_id", "desk_id"}},
		{API_ROUTE_ACCEPT_INVITE, {"desk_id"}},
		{API_ROUTE_CANCEL_INVITE, {"desk_id"}}};

#endif // API_KEYWORDS_H

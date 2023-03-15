
#ifndef API_KEYWORDS_H
#define API_KEYWORDS_H
#include <functions.h>
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

const std::map<std::string, std::function<std::string(Parameters)>>
    command_function_map = {
        {API_ROUTE_AUTHORIZATION, authorization},
        {API_ROUTE_REGISTRATION, registration},
        {API_ROUTE_SEND_MESSAGE, send_message},
        {API_ROUTE_MAKE_EVALUATION, make_evaluation},
        {API_ROUTE_ADD_BOOKMARK, add_bookmark},
        {API_ROUTE_CREATE_DESK, create_desk},
        {API_ROUTE_DELETE_DESK, delete_desk},
        {API_ROUTE_ADD_BOOK, add_book},
        {API_ROUTE_DELETE_BOOK, delete_book},
        {API_ROUTE_INVITE_USER, invite_user},
        {API_ROUTE_KICK_USER, kick_user},
        {API_ROUTE_ACCEPT_INVITE, accept_invite},
        {API_ROUTE_CANCEL_INVITE, cancel_invite}

};

#endif // API_KEYWORDS_H

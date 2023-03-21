#include <QRegularExpression>
#include <api_keywords.h>
#include <functions.h>
#include <db_server.h>
#include <parser.h>

std::string execute_request(QString line)
{
	const QRegularExpression command_regex("^[^?]+");
	const QRegularExpression params_regex("([^&?]+)=([^&]+)");
	QRegularExpressionMatch match = command_regex.match(line);
    QString command;
    if (match.hasMatch())
        command = match.captured(0);
    else
        return "error?text=Error! Command missing!";
    std::map<std::string, std::string> params;
    QRegularExpressionMatchIterator it = params_regex.globalMatch(line);
    while (it.hasNext()) {
        match = it.next();
        params.insert(std::make_pair(match.captured(1).toStdString(), match.captured(2).toStdString()));
    }
    return commandDispatcher(command.toStdString(), params);
}

std::string check_command_req(std::string command, Parameters data) {
	std::string s;
	for (auto &req_field : command_requirements_map.at(command))
		if (data.find(req_field) == data.end() || data.at(req_field).empty())
			s += " " + req_field;
	return s;
}

const std::map<std::string, std::function<std::string(std::string, Parameters)>>
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
		{API_ROUTE_CANCEL_INVITE, cancel_invite}};

std::string commandDispatcher(std::string command, Parameters request)
{
    if (command_function_map.find(command) != command_function_map.end()) {
		auto req_error = check_command_req(command, request);
		if (!req_error.empty())
			return "error?text=Error! Missings fields! Required:" + req_error;
		std::string result = command_function_map.at(command)(command, request);
		if (!result.empty()) return result;
    }
    else
    {
		// test code for DB
		auto q = DB_Server::get()->query_simple("SELECT table_name, column_name\
        FROM information_schema.columns\
        WHERE table_schema = 'zlplib'\
        ORDER BY table_name, ordinal_position\
        ");
		std::string s = "\n";
		while (q.next()) {
			s += q.value("table_name").toString().toStdString() + "\t";
			s += q.value("column_name").toString().toStdString() + "\n";
		}
		return "error?text=Error! Command Unrecognized!" + s;
	}
}

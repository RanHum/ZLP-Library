#include <QFile>
#include <api_keywords.h>
#include <functions.h>
#include <db_server.h>
#include <parser.h>

const QJsonObject init_api_map() {
	QFile json("api.json");
	json.open(QIODevice::ReadOnly);
	return QJsonDocument::fromJson(json.readAll()).object();
}
const QJsonObject api_map = init_api_map();

QJsonObject get_response(const QString&& error){
	return api_map["responses"].toObject()[error].toObject();
}

bool check_status(const QJsonObject &response) {
	return response["status"].toString() == "Success";
}

QJsonObject check_fields_req(const QJsonObject &req, const QJsonValue &fields_to_test) {
	QJsonArray missing;
	for (const auto &field_tested : fields_to_test.toArray())
		if (!req.contains(field_tested.toString()))
			missing.append(field_tested);
	if (missing.isEmpty())
		return get_response("success");
	auto err = get_response("missing_fields");
	err["fields"] = missing;
	return err;
}

QJsonObject check_auth(const QJsonObject &req) {
	QString db_query_str = "select user_id from users where user_id=:id and password=:pass";
	auto db_query = DB_Server::get()->query_prepare(db_query_str);
	db_query.bindValue(":id", req["_as_user_id"].toInt());
	db_query.bindValue(":pass", req["_with_password"].toString());
	db_query.exec();
	return get_response(db_query.next() ? "success" : "auth_failed");
}

QJsonObject execute_request(const QJsonObject& req) {
	if (req.isEmpty())
		return get_response("request_invalid");
	auto check_result = check_fields_req(req, api_map["intent_fields"]);
	if (!check_status(check_result))
		return check_result;
	auto api_intent = api_map["api"].toObject()
		[req["_domain"].toString()].toObject()
		[req["_intent"].toString()].toObject();
	if (!api_intent["auth_routine"].toBool()) {
		check_result = check_fields_req(req, api_map["auth_fields"]);
		if (!check_status(check_result)) {
			check_result["text"] = check_result["text"].toString().append(" " + get_response("auth_failed")["text"].toString());
			return check_result;
		}
		check_result = check_auth(req);
		if (!check_status(check_result))
			return check_result;
	}
	check_result = check_fields_req(req, api_intent["required"]);
	if (!check_status(check_result))
		return check_result;
	return get_response("username_exists");
	// commandDispatcher(req);
}

QByteArray execute_line(const QByteArray& line) {
	auto result = execute_request(QJsonDocument::fromJson(line).object());
	return QJsonDocument(result).toJson(QJsonDocument::JsonFormat::Compact);
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

// std::string commandDispatcher(std::string command, Parameters request)
// {
//     if (command_function_map.find(command) != command_function_map.end()) {
// 		auto req_error = check_command_req(command, request);
// 		if (!req_error.empty())
// 			return "error?text=Error! Missings fields! Required:" + req_error;
// 		std::string result = command_function_map.at(command)(command, request);
// 		if (!result.empty()) return result;
//     }
//     else
//     {
// 		// test code for DB
// 		auto q = DB_Server::get()->query_simple("SELECT table_name, column_name\
//         FROM information_schema.columns\
//         WHERE table_schema = 'zlplib'\
//         ORDER BY table_name, ordinal_position\
//         ");
// 		std::string s = "\n";
// 		while (q.next()) {
// 			s += q.value("table_name").toString().toStdString() + "\t";
// 			s += q.value("column_name").toString().toStdString() + "\n";
// 		}
// 		return "error?text=Error! Command Unrecognized!" + s;
// 	}
// }

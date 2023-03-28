#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QRegularExpression>
#include <QStringList>
#include <db_server.h>
#include <parser.h>

QJsonObject init_api_map() {
	QFile json("api.json");
	json.open(QIODevice::ReadOnly);
	auto map = QJsonDocument::fromJson(json.readAll()).object();
	if (map.isEmpty())
		qDebug() << "Error opening and parsing api.json!";
	qDebug() << "Processing api.json finighed!";
	return map;
}
const QJsonObject api_map = init_api_map();

QJsonObject db_map;
void init_db_map() {
	auto db_query = DB_Server::get()->query_simple(api_map["db_fields_query"].toString());
	while (db_query.next()) {
		const auto record = db_query.record();
		auto temp = db_map[record.value("table_name").toString()].toArray();
		temp.append(record.value("column_name").toString());
		db_map.insert(record.value("table_name").toString(), temp);
	}
	if (db_map.isEmpty())
		qDebug() << "Error fetching columns from DB!";
	else
		qDebug() << "DB columns fetched:" << db_map;
}

QJsonObject get_response(const QString&& error){
	return api_map["responses"][error].toObject();
}

bool check_status(const QJsonObject &response) {
	return response["status"].toString() == "Success";
}

// check required fields in request
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

// qsl template engine, see api.json examples
QString prepare_query_fields(const QJsonObject &fields_values, const QJsonArray &fields_possible, const QString &sql_template) {
	// get table name from template first
	const QRegularExpression table_regex("<.+>");
	auto table = table_regex.match(sql_template).captured(0);
	table.chop(1);
	table.remove(0, 1);
	if (db_map.isEmpty()) init_db_map();
	QStringList fields;
	// assemble list of requested fields
	for (const auto &field_poss : db_map[table].toArray()) {
		const auto field = field_poss.toString();
		if (fields_values.contains(field))
			fields.append(field + " = :" + field);
	}
	auto sql = sql_template;
	// replace templates with processed data
	sql.replace(table_regex, table);
	sql.replace("|FIELDS|", fields.join(", "));
	qDebug() << "DB template [" << sql_template << "] table <" << table << "> values = (" << fields_values << ") fields = (" << fields_possible << ") =>" << sql;
	return sql;
}

// db query generic sets of fields
QJsonObject db_query_fields(const QJsonObject &fields_values, const QJsonArray &fields_possible, const QString &sql_template, const QString &result_name, const bool multiple_rows = false, const bool fields_template = false) {
	// prepare query with fields - template detection could be done on the flight with regex, actually
	auto db_query = DB_Server::get()->query_prepare(fields_template ? prepare_query_fields(fields_values, fields_possible, sql_template) : sql_template);
	// insert values in prepared query
	for (const auto &field : fields_possible) {
		const auto field_s = field.toString();
		if (fields_values.contains(field_s))
			db_query.bindValue(":" + field_s, fields_values[field_s].toVariant());
	}
	// run query, check and return response errors
	if (!db_query.exec()) {
		auto err = get_response("request_failed");
		err["text"] = err["text"].toString() + " Failed Query [" + db_query.executedQuery() + "] => " + db_query.lastError().text();
		return err;
	}
	// convert records to json
	QJsonArray records;
	while (db_query.next()) {
		QJsonObject recordObject;
		const auto record = db_query.record();
		for (int i = 0; i < record.count(); i++)
			recordObject.insert(record.fieldName(i), QJsonValue::fromVariant(db_query.value(i)));
		records.append(recordObject);
	}
	auto result = get_response("success");
	// unwrap array to single record if needed
	result.insert(result_name, multiple_rows ? records : records.at(0));
	qDebug() << "DB Query [" << db_query.executedQuery() << "] values = (" << fields_values << ") fields = (" << fields_possible << ") =>" << result << db_query.numRowsAffected();
	return result;
}

// just wrap single sql result in template and add default action type
const QJsonObject action_to_object(const QJsonValue &action) {
	if (action.isObject()) {
		auto result = action.toObject();
		if (action["type"].isUndefined())
			result.insert("type", "result");
		return result;
	}
	auto action_new = api_map["intent_action_result"].toObject();
	action_new.insert("sql", action);
	return action_new;
}

// actions engine for intents
QJsonObject actions_dispatcher(const QJsonObject &req, const QJsonObject &api_intent) {
	// prepare all possible fields for request
	auto fields_all = api_intent["optional"].toArray();
	for (const auto &field : api_intent["required"].toArray())
		fields_all += field;
	for (const auto &field : api_map["auth_fields"].toArray())
		fields_all += field;
	// process intent actions
	qDebug() << "===============\nIncoming intent:" << req;
	for (const auto &action : api_intent["actions"].toArray({api_intent["actions"]})) {
		const auto action_o = action_to_object(action);
		const auto type = action_o["type"].toString();
		// make request to db engine
		qDebug() << "----------\nRun intent action [" << type << "]: " << action_o;
		const auto result = db_query_fields(req, fields_all, action_o["sql"].toString(), type, action_o["multiple_rows"].toBool(), action_o["template"].toBool());
		// evaluate request result based on intent settings
		qDebug() << "Intent action result:" << result;
		const bool empty_result = action_o["multiple_rows"].toBool() ? result[type].toArray().isEmpty() : result[type].toObject().isEmpty();
		const bool test_emptiness = !empty_result == action_o["error_when_not_empty"].toBool();
		if (!check_status(result) || (type == "test" || type == "result" && action_o.contains("error")) && test_emptiness)
		{
			auto err = get_response("error");
			// insert data from failed test query result into error response, be careful
			if (type == "test" && !result[type].isUndefined())
				err.insert(type, result[type]);
			err.insert("text", action_o["error"]);
			return err;
		} else if (type == "result")
			return result;
	}
}

// first-hand validating request before dispatching for intent execution, e.g. required fields and auth checking
QJsonObject execute_request(const QJsonObject &req) {
	// test for invalid or empty request
	if (req.isEmpty())
		return get_response("request_invalid");
	// test intent fields
	auto check_result = check_fields_req(req, api_map["intent_fields"]);
	if (!check_status(check_result))
		return check_result;
	// auth check
	const auto api_intent = api_map["api"]
		[req["_domain"].toString()]
		[req["_intent"].toString()].toObject();
	if (!api_intent["auth_routine"].toBool()) {
		check_result = check_fields_req(req, api_map["auth_fields"]);
		if (!check_status(check_result)) {
			check_result["text"] = check_result["text"].toString() + " " + get_response("auth_failed")["text"].toString();
			return check_result;
		}
		check_result = db_query_fields(req, api_map["auth_fields"].toArray(), api_map["auth_sql"].toString(), "auth");
		if (!check_status(check_result) || check_result["auth"].toObject().isEmpty())
			return get_response("auth_failed");
	}
	// check required fields for intent
	check_result = check_fields_req(req, api_intent["required"]);
	if (!check_status(check_result))
		return check_result;
	// run actual command
	return actions_dispatcher(req, api_intent);
}

QByteArray execute_line(const QByteArray& line) {
	auto response = execute_request(QJsonDocument::fromJson(line).object());
	return QJsonDocument(response).toJson(QJsonDocument::JsonFormat::Compact);
}

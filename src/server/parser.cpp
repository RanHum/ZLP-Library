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
	qDebug() << "Processing api.json finished!";
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
		db_map.insert(record.value("table_name").toString() + record.value("column_name").toString(), record.value("column_name").toString() == "integer");
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
QString resolve_query_template(const QJsonObject &fields_values, const QJsonArray &fields_possible, const QJsonObject &sql_template) {
	// get table name from sql_template first
	auto sql = sql_template["template"].toString();
	const auto table_name = QRegularExpression("<(.+)>").match(sql).captured(1);
	// only insert fields if there is a hint to table
	if (!table_name.isEmpty()) {
		// replace hint <table_name> with table_name
		sql.replace("<" + table_name + ">", table_name);
		if (db_map.isEmpty()) init_db_map();
		// prepare list of fields to insert
		QStringList fields;
		// get fields to ignore
		const auto excludes = sql_template["excludes"].toArray();
		for (const auto &field_poss : db_map[table_name].toArray())
			// ignore fields from excludes parameter
			if (fields_values.contains(field_poss.toString()) && !excludes.contains(field_poss.toString()))
				fields.append(field_poss.toString());
		// insert fields if needed
		if (sql.contains("|FIELDS|"))
			sql.replace("|FIELDS|", fields.join(","));
		// insert fields:values if needed
		if (sql.contains("|FIELDS:VALUES|")) {
			QStringList values;
			// assemble list of requested fields:values
			for (const auto &field : fields) {
				auto comparison = sql_template["str_partial_compare"].toBool() ? " ilike " : " = ";
				QString value_template = ":%1";
				if (!db_map[table_name + field].toBool() && comparison != " = ") {
					comparison = " ilike ";
					value_template = "\'%:%1%\'";
				}
				qDebug() << value_template << value_template.arg(field) << comparison << sql_template["str_partial_compare"].toBool();
				values.append(table_name + "." + field + comparison + value_template.arg(field));
			}
			sql.replace("|FIELDS:VALUES|", values.join(sql_template["joining"].toString(",")));
		}
		// insert :values if needed
		if (sql.contains("|VALUES|")) {
			for (auto &field : fields)
				field.prepend(":");
			sql.replace("|VALUES|", fields.join(","));
		}
	}
	// handle explodes
	auto it = QRegularExpression("\\+\\+([^\\+]+)\\+\\+").globalMatch(sql);
	while (it.hasNext()) {
		auto match = it.next();
		const auto array_to_explode = fields_values[match.captured(1)].toArray();
		QStringList prepared;
		if (!array_to_explode.isEmpty())
			for (const auto &value : array_to_explode)
				prepared.append(value.isString() ? "'" + value.toString() + "'" : QString::number(value.toInt()));
		sql.replace(match.captured(), prepared.join(","));
	}
	// insert code to return result fields if not turned off and not sql select. by default return all fields in a row
	if (!sql.startsWith("select", Qt::CaseInsensitive) && (!sql_template.contains("output") || sql_template["output"].toBool(true)))
		sql += " returning " + sql_template["output"].toString("*");
	qDebug() << "DB template [" << sql_template << "] table <" << table_name << "> values = (" << fields_values << ") fields = (" << fields_possible << ") =>" << sql;
	return sql;
}

// db query generic sets of fields
QJsonObject db_query_fields(const QJsonObject &fields_values, const QJsonArray &fields_possible, const QJsonValue &sql, const QString &result_name, const bool multiple_rows = false, const QJsonObject &action_storage = QJsonObject()) {
	// prepare query with fields. via template engine if it's template object
	auto db_query = DB_Server::get()->query_prepare(sql.isObject()? resolve_query_template(fields_values, fields_possible, sql.toObject()) : sql.toString());
	// insert values in prepared query
	for (const auto &field : fields_possible) {
		const auto field_s = field.toString();
		if (fields_values.contains(field_s))
			db_query.bindValue(":" + field_s, fields_values[field_s].toVariant());
	}
	// insert preprocessed values from previous action into prepared query
	for (const auto &field : action_storage.keys())
			db_query.bindValue(":_" + field, action_storage[field].toVariant());
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
	if (action.isObject())
		return action.toObject();
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
	// actions result storage, now stores only one result
	QJsonObject action_storage;
	// process intent actions
	qDebug() << "===============\nIncoming intent:" << req;
	for (const auto &action : api_intent["actions"].toArray({api_intent["actions"]})) {
		const auto action_o = action_to_object(action);
		// next action if there are no locally required fields
		if (action_o.contains("required") && !check_status(check_fields_req(req, action_o["required"])))
			continue;
		const auto type = action_o["type"].toString("result");
		// make request to db engine
		qDebug() << "----------\nRun intent action [" << type << "]: " << action_o;
		const auto result = db_query_fields(req, fields_all, action_o["sql"], type, action_o["multiple_rows"].toBool(), action_storage);
		// evaluate request result based on intent settings
		qDebug() << "Intent action result:" << result;
		const auto &res_v = result[type];
		const bool empty_result = res_v.isArray() ? res_v.toArray().isEmpty() : res_v.toObject().isEmpty();
		// saving returned values in storage for later use
		if (type == "action" && !empty_result)
			action_storage = (res_v.isArray() ? res_v.toArray()[0] : res_v).toObject();
		const bool test_emptiness = !empty_result == action_o["error_when_not_empty"].toBool();
		if (!check_status(result) || (type == "test" || type == "result" && action_o.contains("error")) && test_emptiness)
		{
			auto err = get_response("error");
			// insert data from failed test query result into error response, be careful
			if (type == "test" && !res_v.isUndefined())
				err.insert(type, res_v);
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
		check_result = db_query_fields(req, api_map["auth_fields"].toArray(), api_map["auth_sql"], "auth");
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

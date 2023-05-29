
#ifndef PARSER_H
#define PARSER_H
#include <QByteArray>
#include <QJsonObject>

QByteArray execute_line(const QByteArray &line);
QJsonObject execute_request(const QJsonObject &req);

#endif // PARSER_H

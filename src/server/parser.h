
#ifndef PARSER_H
#define PARSER_H

#include <zlp-commons.h>

std::string execute_request(QString line);
std::string commandDispatcher(std::string command, Parameters request);

#endif // PARSER_H

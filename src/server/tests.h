
#ifndef TESTS_H
#define TESTS_H
#include <vector>
#include <string>
#include <QJsonObject>



class Tests
{
public:
    Tests();
private:
    std::vector<std::string> test_registration();
    std::vector<std::string> test_authorization();
    std::vector<std::string> test_create_desk();
    std::vector<std::string> test_create_book();
    std::vector<std::string> test_invite_user();
    std::vector<std::string> test_results;
};

#endif // TESTS_H

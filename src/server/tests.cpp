
#include "tests.h"
#include "parser.h"

Tests::Tests()
{
    this->test_registration();
    this->test_authorization();
    this->test_create_desk();
    this->test_create_book();
    this->test_invite_user();
    for (const auto& test : this->test_results) {
        qDebug() << QString::fromStdString(test);
    }
}

std::vector<std::string> Tests::test_registration() {
    std::vector<QJsonObject> test_data = {
        QJsonObject{{"name", ""}, {"password", ""}, {"test_result", "Error"}},
        QJsonObject{{"name", ""}, {"password", "     "}, {"test_result", "Error"}},
        QJsonObject{{"name", "      "}, {"password", ""}, {"test_result", "Error"}},
        QJsonObject{{"name", "test"}, {"password", "test"}, {"test_result", "Success"}},
        QJsonObject{{"name", "test"}, {"password", "test"}, {"test_result", "Error"}}
    };
    int test_number = 1;
    for (auto& test : test_data) {
        test.insert("_domain", "user");
        test.insert("_intent", "register");
        const auto resp = execute_request(test);
        if (test["test_result"] != resp["status"]) {
            this->test_results.push_back("Test registration #" + std::to_string(test_number++) + " Fail " + resp["text"].toString().toStdString());
        } else {
            this->test_results.push_back("Test registration #" + std::to_string(test_number++) + " Pass");
        }
    }
    return test_results;
}

std::vector<std::string> Tests::test_authorization() {
    std::vector<QJsonObject> test_data = {
        QJsonObject{{"name", ""}, {"password", ""}, {"test_result", "Error"}},
        QJsonObject{{"name", ""}, {"password", "     "}, {"test_result", "Error"}},
        QJsonObject{{"name", "      "}, {"password", ""}, {"test_result", "Error"}},
        QJsonObject{{"name", "test "}, {"password", "test"}, {"test_result", "Error"}},
        QJsonObject{{"name", "test"}, {"password", "test"}, {"test_result", "Success"}}
    };
    std::vector<std::string> test_results;
    int test_number = 1;
    for (auto& test : test_data) {
        test.insert("_domain", "user");
        test.insert("_intent", "login");
        const auto resp = execute_request(test);
        if (test["test_result"] != resp["status"]) {
            this->test_results.push_back("Test authorization #" + std::to_string(test_number++) + " Fail " + resp["text"].toString().toStdString());
        } else {
            this->test_results.push_back("Test authorization #" + std::to_string(test_number++) + " Pass");
        }
    }
    return test_results;
}

std::vector<std::string> Tests::test_create_desk() {
    std::vector<QJsonObject> test_data = {
        QJsonObject{{"name", ""}, {"test_result", "Error"}},
        QJsonObject{{"name", "    "}, {"test_result", "Error"}},
        QJsonObject{{"name", "newdesk"}, {"_as_user_id", "1"}, {"_with_password", "test"}, {"test_result", "Error"}},
        QJsonObject{{"name", "newdesk"}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Success"}},
        QJsonObject{{"name", "newdesk"}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Error"}},
    };
    std::vector<std::string> test_results;
    int test_number = 1;
    for (auto& test : test_data) {
        test.insert("_domain", "desk");
        test.insert("_intent", "add");
        const auto resp = execute_request(test);
        qDebug() << resp;
        if (test["test_result"] != resp["status"]) {
            this->test_results.push_back("Test create_desk #" + std::to_string(test_number++) + " Fail " + resp["text"].toString().toStdString());
        } else {
            this->test_results.push_back("Test create_desk #" + std::to_string(test_number++) + " Pass");
        }
    }
    return test_results;
}

std::vector<std::string> Tests::test_create_book() {
    std::vector<QJsonObject> test_data = {
        QJsonObject{{"name", ""}, {"test_result", "Error"}},
        QJsonObject{{"name", "    "}, {"test_result", "Error"}},
        QJsonObject{{"name", "   "}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Error"}},
        QJsonObject{{"name", "book1"}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Error"}},
        QJsonObject{{"name", "newbook"}, {"_as_user_id", "20"}, {"_with_password", "1"}, {"test_result", "Error"}},
        QJsonObject{{"name", "newbook"}, {"_as_user_id", "20"}, {"author_id", 1}, {"genre_id", 1}, {"_with_password", "test"}, {"test_result", "Success"}},
        QJsonObject{{"name", "newbook"}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Error"}},
    };
    std::vector<std::string> test_results;
    int test_number = 1;
    for (auto& test : test_data) {
        test.insert("_domain", "book");
        test.insert("_intent", "add");
        const auto resp = execute_request(test);
        if (test["test_result"] != resp["status"]) {
            this->test_results.push_back("Test create_book #" + std::to_string(test_number++) + " Fail " + resp["text"].toString().toStdString());
        } else {
            this->test_results.push_back("Test create_book #" + std::to_string(test_number++) + " Pass");
        }
    }
    return test_results;
}

std::vector<std::string> Tests::test_invite_user() {
    std::vector<QJsonObject> test_data = {
        QJsonObject{{"desk_id", ""}, {"user_id", ""}, {"test_result", "Error"}},
        QJsonObject{{"desk_id", ""}, {"user_id", ""}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Error"}},
        QJsonObject{{"desk_id", "12"}, {"user_id", "20"}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Error"}},
        QJsonObject{{"desk_id", "1"}, {"user_id", "20"}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Error"}},
        QJsonObject{{"desk_id", "12"}, {"user_id", "1"}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Success"}},
        QJsonObject{{"desk_id", "12"}, {"user_id", "9"}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Success"}},
        QJsonObject{{"desk_id", "12"}, {"user_id", "1"}, {"_as_user_id", "20"}, {"_with_password", "test"}, {"test_result", "Error"}},
    };
    std::vector<std::string> test_results;
    int test_number = 1;
    for (auto& test : test_data) {
        test.insert("_domain", "invite");
        test.insert("_intent", "send");
        const auto resp = execute_request(test);
        if (test["test_result"] != resp["status"]) {
            this->test_results.push_back("Test invite_user #" + std::to_string(test_number++) + " Fail " + resp["text"].toString().toStdString());
        } else {
            this->test_results.push_back("Test invite_user #" + std::to_string(test_number++) + " Pass");
        }
    }
    return test_results;
}


#include "api_utils.h"

UserCredentials &UserCredentials::instance()
{
	static UserCredentials instance;
	return instance;
}

QString UserCredentials::login() const { return m_login; }

void UserCredentials::setLogin(const QString &login) { m_login = login; }

QString UserCredentials::avatar() const { return m_avatar; }

void UserCredentials::setAvatar(const QString &avatar) { m_avatar = avatar; }

QString UserCredentials::password() const { return m_password; }

void UserCredentials::setPassword(const QString &password) { m_password = password; }

int UserCredentials::userId() const { return m_userId; }

void UserCredentials::setUserId(int userId) { m_userId = userId; }

UserCredentials::UserCredentials() {}

QJsonObject makeReqJson(const QString &domain, const QString &intent)
{
	return QJsonObject{
			{"_as_user_id", UserCredentials::instance().userId()},
			{"_with_password", UserCredentials::instance().password()},
			{"_domain", domain},
			{"_intent", intent}};
}

bool check_status(const QJsonObject &response)
{
	return response["status"].toString() == "Success";
}
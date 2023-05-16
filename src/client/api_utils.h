#ifndef API_UTILS_H
#define API_UTILS_H

#include <QJsonObject>
#include <QString>

class UserCredentials {
public:
	static UserCredentials &instance();
	QString login() const;
	void setLogin(const QString &login);
	QString avatar() const;
	void setAvatar(const QString &avatar);
	QString password() const;
	void setPassword(const QString &password);
	int userId() const;
	void setUserId(int userId);

private:
	UserCredentials();
	UserCredentials(const UserCredentials &);
	QString m_login = "";
	QString m_avatar = "";
	QString m_password = "";
	int m_userId = 0;
};

QJsonObject makeReqJson(const QString &domain, const QString &intent);
bool check_status(const QJsonObject &response);

#endif
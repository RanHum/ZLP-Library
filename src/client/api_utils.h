#include <QString>
#include <QJsonObject>

class UserCredentials
{
public:
    static UserCredentials& instance()
    {
        static UserCredentials instance;
        return instance;
    }

    QString login() const { return m_login; }
    void setLogin(const QString &login) { m_login = login; }

    QString avatar() const { return m_avatar; }
    void setAvatar(const QString &avatar) { m_avatar = avatar; }

    QString password() const { return m_password; }
    void setPassword(const QString &password) { m_password = password; }

    int userId() const { return m_userId; }
    void setUserId(int userId) { m_userId = userId; }

private:
    UserCredentials() {}
    UserCredentials(const UserCredentials&);

    QString m_login = "";
    QString m_avatar = "";
    QString m_password = "";
    int m_userId = 0;
};

QJsonObject makeReqJson(const QString &domain, const QString &intent) {
	return QJsonObject{
		{"_as_user_id", UserCredentials::instance().userId()},
		{"_with_password", UserCredentials::instance().password()},
		{"_domain", domain},
		{"_intent", intent}};
}

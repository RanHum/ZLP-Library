#ifndef API_UTILS_H
#define API_UTILS_H

#include <QJsonObject>
#include <QString>

/*!
 * \brief The UserCredentials class represents user credentials such as login, avatar, password, and user ID.
 */
class UserCredentials
{
public:
	/*!
	 * \brief Get the instance of UserCredentials singleton.
	 *
	 * \return The instance of UserCredentials.
	 */
	static UserCredentials &instance();

	/*!
	 * \brief Get the login of the user.
	 *
	 * \return The login of the user.
	 */
	QString login() const;

	/*!
	 * \brief Set the login of the user.
	 *
	 * \param login The login of the user.
	 */
	void setLogin(const QString &login);

	/*!
	 * \brief Get the avatar of the user.
	 *
	 * \return The avatar of the user.
	 */
	QString avatar() const;

	/*!
	 * \brief Set the avatar of the user.
	 *
	 * \param avatar The avatar of the user.
	 */
	void setAvatar(const QString &avatar);

	/*!
	 * \brief Get the password of the user.
	 *
	 * \return The password of the user.
	 */
	QString password() const;

	/*!
	 * \brief Set the password of the user.
	 *
	 * \param password The password of the user.
	 */
	void setPassword(const QString &password);

	/*!
	 * \brief Get the user ID.
	 *
	 * \return The user ID.
	 */
	int userId() const;

	/*!
	 * \brief Set the user ID.
	 *
	 * \param userId The user ID.
	 */
	void setUserId(int userId);

private:
	UserCredentials();
	UserCredentials(const UserCredentials &);
	QString m_login = "";
	QString m_avatar = "";
	QString m_password = "";
	int m_userId = 0;
};

/*!
 * \brief Create a JSON object for the request.
 *
 * \param domain The domain of the request.
 * \param intent The intent of the request.
 * \return The JSON object representing the request.
 */
QJsonObject makeReqJson(const QString &domain, const QString &intent);
/*!
 * \brief Check the status of the response.
 *
 * \param response The response JSON object.
 * \return \c true if the status is "Success", \c false otherwise.
 */
bool check_status(const QJsonObject &response);

#endif
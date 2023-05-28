#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QJsonArray>
#include <QMessageBox>
#include <QListWidgetItem>
#include "api_utils.h"
#include "requests.h"

namespace Ui
{
    class profile;
}

/*!
 * \class profile
 * \brief The profile class represents a user profile widget.
 */
class profile : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a profile widget.
     *
     * \param parent The parent widget.
     */
    explicit profile(QWidget *parent = nullptr);
    /*!
     * \brief Destroys the profile widget.
     */
    ~profile();
private slots:
    /*!
     * \brief Handles the click event of the back button.
     */
    void on_back_button_clicked();

public:
    void handleAcceptButtonClicked(QListWidgetItem *invite_list_item);
    void handleCancelButtonClicked(QListWidgetItem *invite_list_item);
signals:
    void joinedInDesk(int desk_id);

private:
    Ui::profile *ui;
    QWidget *createInviteWidget(const int desk_id, const QString &desk_name);
};

#endif // PROFILE_H

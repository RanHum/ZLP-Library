#ifndef DESKADMINPANEL_H
#define DESKADMINPANEL_H

#include <QDialog>
#include <QStringListModel>
#include <QMessageBox>
#include <QJsonArray>
#include <QHBoxLayout>
#include "book.h"
#include "user.h"
#include "api_utils.h"
#include "requests.h"
#include "desk.h"

namespace Ui
{
    class DeskAdminPanel;
}

class DeskAdminPanel : public QDialog
{
    Q_OBJECT

public:
    explicit DeskAdminPanel(
        Desk* desk,
        std::map<int, Book> &desk_books,
        std::map<int, Book> &books,
        std::map<int, User> &users,
        QWidget *parent = nullptr);
    ~DeskAdminPanel();
private slots:
    void onListItemClicked(const QModelIndex &index);
    void onBookListSelectChanged(int index);
    void onBookListAddSelectChanged(int index);
    void onMemberListSelectChanged(int index);
    void on_add_book_button_clicked();

    void on_delete_book_button_clicked();

    void on_invite_user_button_clicked();

    void on_kick_member_button_clicked();

    void on_desk_edit_name_button_clicked();

public slots:
    void handleBookAdded(Book book);
    void handleBookDeleted(Book book);
    void handleUserKicked(User user);
    void handleDeskEdited(Desk desk);
    void unsend_invite(int user_id);
    void delete_invite(int user_id);

private:
    Ui::DeskAdminPanel *ui;
    Desk* desk;
    std::map<int, Book> &desk_books;
    std::map<int, Book> &books;
    std::map<int, User> &users;

    void setComboBoxItems();
    void setInviteList();
signals:
    void add_book_to_desk(Book book);
    void delete_book_from_desk(Book book);
    void invite_user(int user_id);
    void kick_user_from_desk(User user);
    void edit_desk(Desk* desk, QString new_name);

};

#endif // DESKADMINPANEL_H

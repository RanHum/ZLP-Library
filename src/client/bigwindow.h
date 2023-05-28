#ifndef BIGWINDOW_H
#define BIGWINDOW_H
#include <QDialog>
#include <QDate>
#include <QImage>
#include <QMessageBox>
#include <QThread>
#include <QListWidget>
#include <QMainWindow>
#include <QJsonArray>
#include <QJsonValue>
#include <QDate>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <ctime>
#include <cstdlib>

#include "doska.h"
#include "full.h"
#include "book_container.h"
#include "book_form.h"
#include "doska.h"
#include "full.h"
#include "requests.h"
#include "api_utils.h"
#include "profile.h"
#include "desk.h"
#include "book.h"
#include "deskadminpanel.h"

namespace Ui
{
    class Bigwindow;
};

/*!
 * \brief The Bigwindow class represents a dialog window for managing desks and books.
 */
class Bigwindow : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor of the Bigwindow class.
     *
     * \param parent The parent widget.
     */
    explicit Bigwindow(QWidget *parent = nullptr);
    /*!
     * \brief Destructor of the Bigwindow class.
     */
    ~Bigwindow();

private:
    void get_desks();
    Desk get_desk(int desk_id);
    std::map<int, Book> get_desk_books(int desk_id);
    Book get_book(int book_id);
    void add_desk_to_list(Desk desk);
    void get_books();
    std::map<int, User> get_desk_users(int desk_id);
    User get_user(int user_id);
public slots:
    void slot(const QString &text);

private slots:

    void on_label_linkActivated(const QString &link);

    /*!
     * \brief Slot called when a widget is added to the list of desks.
     *
     * \param text The text to be displayed in the added widget.
     */
    void onAddWidget(const QString &text);

    /*!
     * \brief Slot called when the remove button is clicked on a desk item widget.
     *
     * \param deskItemWidget Pointer to the desk item widget to be removed.
     */
    void slot_remove_fullWidget(Full *deskItemWidget);

    /*!
     * \brief Slot called when a desk item is clicked.
     *
     * \param desk Pointer to the clicked desk item widget.
     */
    void on_desk_item_clicked(Full *desk);

    /*!
     * \brief Function to generate book containers and populate them with books.
     *
     * \param desk_id The ID of the desk for which to generate book containers.
     */
    void generate_book_containers(const std::map<int, Book> &books);

    /*!
     * \brief Function to clear the book containers area.
     */
    void clear_book_containers();

    /*!
     * \brief Slot called when the "Close Desk" button is clicked.
     *        Clears the book containers and hides related UI elements.
     */
    void on_close_desk_button_clicked();

    /*!
     * \brief Slot called when the "Delete Desk" button is clicked.
     *        Calls the same functionality as the "Close Desk" button.
     */
    void on_delete_desk_button_clicked();

    /*!
     * \brief Slot called when a book is added through the add book form dialog.
     *
     * \param name        The name/title of the book.
     * \param date        The date of the book.
     * \param description The description of the book.
     * \param page_count  The page count of the book.
     * \param format      The format of the book.
     * \param authors     The author(s) of the book.
     * \param genres      The genre(s) of the book.
     */
    void on_create_book(const QString name,
                        const QString creation_date,
                        const QString description,
                        const QString page_count,
                        const QString format,
                        const QString authors,
                        const QString genres);

    /*!
     * \brief Slot called when the profile button is clicked.
     *        Opens the profile window.
     */
    void on_profile_button_clicked();

    /*!
     * \brief Slot called when the add desk button is clicked.
     */
    void on_add_desk_button_clicked();

    /*!
     * \brief Slot called when the avatar button is clicked.
     */
    void on_avatar_button_clicked();

    void on_create_book_button_clicked();

    void on_admin_desk_button_clicked();

    void add_book_to_desk(Book book);

    void delete_book_from_desk(Book book);

    void send_invite_to_user(int user_id);

    void kick_user_from_desk(User user);
    void joinInDesk(int desk_id);
signals:
    void addedBook(const Book &book);
    void deletedBook(const Book &book);
    void kickedUser(const User &user);

private:
    Ui::Bigwindow *ui;      /*!< The user interface of the Bigwindow. */
    Doska *deskForm;        /*!< The form for adding desks. */
    QListWidget *desksList; /*!< The list widget to store desk item widgets. */
    Full *deskWidget;       /*!< The widget for displaying desk details. */
    book_form *addBookForm; /*!< The form for adding books. */
    std::map<int, Desk> user_desks;
    std::map<int, Book> books;
};

#endif // BIGWINDOW_H

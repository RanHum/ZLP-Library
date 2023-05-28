#ifndef BOOK_FORM_H
#define BOOK_FORM_H

#include <QWidget>

namespace Ui
{
    class book_form;
}

/*!
 * \brief The book_form class represents a form for adding a book.
 */
class book_form : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a book_form widget.
     *
     * \param parent The parent widget.
     */
    explicit book_form(QWidget *parent = nullptr);
    ~book_form();

private slots:
    /*!
     * \brief Handles the click event of the add button.
     */
    void on_add_button_clicked();

private:
    Ui::book_form *ui;

signals:
    /*!
     * \brief Signal emitted when a book is added.
     *
     * \param name The name of the book.
     * \param date The date of the book.
     * \param description The description of the book.
     * \param page_count The page count of the book.
     * \param format The format of the book.
     * \param authors The author(s) of the book.
     * \param genres The genre(s) of the book.
     */
    void add_book(
        const QString name,
        const QString creation_date,
        const QString description,
        const QString page_count,
        const QString format,
        const QString authors,
        const QString genres);
};

#endif // BOOK_FORM_H

#ifndef DOSKA_H
#define DOSKA_H
#include <QtWidgets>
#include <QWidget>

namespace Ui
{
    class BookForm;
}

/*!
 * \brief The BookForm class represents a form widget for adding a book.
 */
class BookForm : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor of the BookForm class.
     *
     * \param parent The parent widget.
     */
    explicit BookForm(QWidget *parent = nullptr);
    /*!
     * \brief Destructor of the BookForm class.
     */
    ~BookForm();

private slots:
    /*!
     * \brief Slot called when the submit button is clicked.
     */
    void on_pushButton_clicked();

private:
    Ui::BookForm *ui; /*!< The user interface for the BookForm widget. */
signals:
    /*!
     * \brief Signal emitted when the form is submitted.
     *
     * \param text The text entered in the form.
     */
    void signal(const QString &text);
};

#endif // DOSKA_H

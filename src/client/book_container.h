#ifndef BOOKCONTAINER_H
#define BOOKCONTAINER_H

#include <QWidget>
#include "book.h"

namespace Ui
{
    class BookContainer;
};

/*!
 * \brief The BookContainer class represents a container widget for displaying book information.
 *        It contains a title label and an author label.
 */
class BookContainer : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a BookContainer object.
     *
     * \param parent The parent widget.
     */
    explicit BookContainer(const Book* book, QWidget *parent = nullptr);
    ~BookContainer();

private:
    Ui::BookContainer *ui;
    const Book* book;
    void set_detail_label();
};

#endif // BOOKCONTAINER_H

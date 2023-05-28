#ifndef FULL_H
#define FULL_H

#include <QWidget>
#include <QLabel>
#include <QListWidgetItem>
#include "desk.h"
namespace Ui
{
    class Full;
}

/*!
 * \class Full
 * \brief The Full class represents a full widget.
 */

class Full : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a Full widget.
     *
     * \param parent The parent widget.
     */
    explicit Full(QWidget *parent = nullptr);
    Full(const Desk &desk, QWidget *parent = nullptr);
    /*!
     * \brief Destroys the Full widget.
     */
    ~Full();
    QListWidgetItem *item;
    /*!
     * \brief Sets the text of the label in the Full widget.
     *
     * \param text The text to set.
     */
    void setDesk(const Desk &text);
    int getDeskId();
    int getOwner();
    QString getName();
    Desk getDesk();
    std::map<int, Book> getBooks();


protected:
    /*!
     * \brief Handles the mouse press event.
     *
     * \param event The mouse event.
     */
    void mousePressEvent(QMouseEvent *event) override;
private slots:
//    /*!
//     * \brief Handles the click event of the push button.
//     */
//    void on_pushButton_clicked();

private:
    Ui::Full *ui;
    Desk desk;
signals:
//    /*!
//     * \brief Signal emitted when the remove button is clicked in the Full widget.
//     *
//     * \param widget A pointer to the Full widget emitting the signal.
//     */
//    void remove_requested(Full *widget);
    /*!
     * \brief Signal emitted when the Full widget is clicked.
     *
     * \param widget A pointer to the Full widget emitting the signal.
     */
    void clicked(Full *widget);
};

#endif // FULL_H

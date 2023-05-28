#ifndef DOSKA_H
#define DOSKA_H
#include <QtWidgets>
#include <QWidget>

namespace Ui
{
    class Doska;
}

/*!
 * \brief The Doska class represents a widget for a "Doska".
 */
class Doska : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a Doska widget.
     *
     * \param parent The parent widget.
     */
    explicit Doska(QWidget *parent = nullptr);
    /*!
     * \brief Destroys the Doska widget.
     */
    ~Doska();

private slots:
    /*!
     * \brief Handles the click event of the push button.
     */
    void on_pushButton_clicked();

private:
    Ui::Doska *ui;

signals:
    /*!
     * \brief Signal emitted when a text is entered.
     *
     * \param text The entered text.
     */
    void signal(const QString &text);
};

#endif // DOSKA_H

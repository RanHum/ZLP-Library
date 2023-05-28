#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui
{
    class Form;
}

/*!
 * \brief The Form class represents a registration form widget.
 */
class Form : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a Form widget.
     *
     * \param parent The parent widget.
     */
    explicit Form(QWidget *parent = nullptr);

    /*!
     * \brief Destroys the Form widget.
     */
    ~Form();

signals:
    /*!
     * \brief Signal emitted when the user wants to go back to the previous window.
     */
    void firstWindow();
private slots:
    /*!
     * \brief Handles the click event of the register button.
     */
    void on_registerButton_clicked();
    /*!
     * \brief Handles the click event of the "Already have an account" button.
     */
    void on_haveAccountButton_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H

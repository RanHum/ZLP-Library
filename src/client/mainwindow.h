#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <form.h>
#include <QMessageBox>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/*!
 * \brief The MainWindow class represents the main window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Constructs a MainWindow.
     *
     * \param parent The parent widget.
     */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * \brief Destroys the MainWindow.
     */
    ~MainWindow();

private slots:
    /*!
     * \brief Handles the click event of the push button.
     */
    void on_pushButton_clicked();

    /*!
     * \brief Handles the click event of the second push button.
     */
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui; /*!< The UI object for the MainWindow. */
    Form *form;         /*!< The Form object for registration. */

    /*!
     * \brief Delays the execution by the given number of milliseconds.
     *
     * \param ms The number of milliseconds to delay.
     */
    void delay(int ms);
};
#endif // MAINWINDOW_H

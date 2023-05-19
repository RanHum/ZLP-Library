#ifndef BOOK_FORM_H
#define BOOK_FORM_H

#include <QWidget>

namespace Ui {
class book_form;
}

class book_form : public QWidget
{
    Q_OBJECT

public:
    explicit book_form(QWidget *parent = nullptr);
    ~book_form();

private slots:
    void on_add_button_clicked();

private:
    Ui::book_form *ui;

signals:
    void add_book(
        const QString& name,
        const QString& date,
        const QString& description,
        const QString& page_count,
        const QString& format,
        const QString& authors,
        const QString& genres
        );
};

#endif // BOOK_FORM_H

#ifndef BIGWINDOW_H
#define BIGWINDOW_H
#include <QDialog>
#include <doska.h>
#include <full.h>
#include "book_container.h"
#include "book_form.h"
namespace Ui {
class Bigwindow;
}

class Bigwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Bigwindow(QWidget *parent = nullptr);
    ~Bigwindow();

public slots:
    void slot(const QString& text);

private slots:

    void on_label_linkActivated(const QString &link);

    void onAddWidget(const QString& text);

    void slot_remove_fullWidget(Full* deskItemWidget);

    void on_desk_item_clicked(Full* desk);

    void generate_book_containers(const QString& desk_id);

    void clear_book_containers();

    void on_close_desk_button_clicked();

    void on_delete_desk_button_clicked();

    void on_add_book_button_clicked();

    void onAddBook(const QString& name,
                   const QString& date,
                   const QString& description,
                   const QString& page_count,
                   const QString& format,
                   const QString& authors,
                   const QString& genres);

    void on_profile_button_clicked();

    void on_add_desk_button_clicked();

private:
    Ui::Bigwindow *ui;
    Doska * deskForm;
    QListWidget* desksList; // QListWidget для хранения виджетов Full
    Full * deskWidget;
    book_form * addBookForm;
};

#endif // BIGWINDOW_H

#ifndef DOSKA_H
#define DOSKA_H
#include <QtWidgets>
#include <QWidget>

namespace Ui {
class BookForm;
}

class BookForm : public QWidget
{
    Q_OBJECT

public:
    explicit BookForm(QWidget *parent = nullptr);
    ~BookForm();



private slots:
    void on_pushButton_clicked();

private:
    Ui::BookForm *ui;

signals:
    void signal(const QString& text);
};

#endif // DOSKA_H

#ifndef BIGWINDOW_H
#define BIGWINDOW_H
#include <QDialog>
#include <doska.h>
#include <full.h>
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
    void on_pushButton_clicked();

    void on_label_linkActivated(const QString &link);

    void on_pushButton_25_clicked();

    void on_pushButton_3_clicked();

    void onAddWidget(const QString& text);

    void slot_remove_fullWidget();

private:
    Ui::Bigwindow *ui;
    Doska *doska;
QListWidget* widgetList; // QListWidget для хранения виджетов Full
Full *fullWidget;
};

#endif // BIGWINDOW_H

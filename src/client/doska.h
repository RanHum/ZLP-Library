#ifndef DOSKA_H
#define DOSKA_H
#include <QtWidgets>
#include <QWidget>

namespace Ui {
class Doska;
}

class Doska : public QWidget
{
    Q_OBJECT

public:
    explicit Doska(QWidget *parent = nullptr);
    ~Doska();



private slots:
    void on_pushButton_clicked();

private:
    Ui::Doska *ui;

signals:
    void signal(const QString& text);
};

#endif // DOSKA_H

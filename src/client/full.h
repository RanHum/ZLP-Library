#ifndef FULL_H
#define FULL_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class Full;
}

class Full : public QWidget
{
    Q_OBJECT

public:
    explicit Full(QWidget *parent = nullptr);
    Full(const QString& text, QWidget *parent = nullptr);
    ~Full();

void setText(const QString& text);

private slots:
void on_pushButton_clicked();

private:
    Ui::Full *ui;
    //QLabel *m_label;
signals:
    void on_close();
};

#endif // FULL_H

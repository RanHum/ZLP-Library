#ifndef FULL_H
#define FULL_H

#include <QWidget>
#include <QLabel>
#include <QListWidgetItem>
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
    QListWidgetItem * item;

    void setText(const QString& text);

protected:
    void mousePressEvent(QMouseEvent* event) override;
private slots:
    void on_pushButton_clicked();

private:
    Ui::Full *ui;
signals:
    void remove_requested(Full* widget);
    void clicked(Full* widget);
};

#endif // FULL_H

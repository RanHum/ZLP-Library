#ifndef BOOKCONTAINER_H
#define BOOKCONTAINER_H

#include <QWidget>
#include <QLabel>

class BookContainer : public QWidget
{
    Q_OBJECT

public:
    explicit BookContainer(QWidget *parent = nullptr);
    void setTitle(const QString& title);
    void setAuthor(const QString& author);

private:
    QLabel *titleLabel;
    QLabel *authorLabel;
};

#endif // BOOKCONTAINER_H

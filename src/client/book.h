
#ifndef BOOK_H
#define BOOK_H
#include <QString>
#include <QDate>

struct Book {
    int id;
    QString name;
    int book_cover;
    QString description;
    int page_count;
    int format;
    int locator;
    int owner;
    QDate creation_date;
};

#endif // BOOK_H

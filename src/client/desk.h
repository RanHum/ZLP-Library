
#ifndef DESK_H
#define DESK_H
#include <QString>
#include <QImage>
#include "book.h"
#include "user.h"

struct Desk
{
    int id;
    QString name;
    int owner;
    QImage background;
    int sort;
    std::map<int, Book> books;
    std::map<int, User> users;
};

#endif // DESK_H

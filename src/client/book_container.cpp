#include "book_container.h"
#include <QHBoxLayout>

BookContainer::BookContainer(QWidget *parent) : QWidget(parent)
{
    titleLabel = new QLabel(this);
    authorLabel = new QLabel(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(authorLabel);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setAlignment(Qt::AlignCenter);
}

void BookContainer::setTitle(const QString& title)
{
    titleLabel->setText(title);
}

void BookContainer::setAuthor(const QString& author)
{
    authorLabel->setText(author);
}

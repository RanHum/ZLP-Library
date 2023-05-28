#include "deskadminpanel.h"
#include "qstackedwidget.h"
#include "ui_deskadminpanel.h"

DeskAdminPanel::DeskAdminPanel(std::map<int, Book> &desk_books,
                               std::map<int, Book> &books,
                               std::map<int, User> &users,
                               QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::DeskAdminPanel),
                                                  desk_books(desk_books),
                                                  books(books),
                                                  users(users)
{
    ui->setupUi(this);
    QStringListModel *model = new QStringListModel(this);
    QStringList itemList;
    itemList << "Книги"
             << "Участники";
    model->setStringList(itemList);
    ui->listView->setModel(model);
    connect(ui->listView, &QListView::clicked, this, &DeskAdminPanel::onListItemClicked);
    connect(ui->book_list_select, SIGNAL(currentIndexChanged(int)), this, SLOT(onBookListSelectChanged(int)));
    connect(ui->book_list_to_add_select, SIGNAL(currentIndexChanged(int)), this, SLOT(onBookListAddSelectChanged(int)));
    connect(ui->member_list_select, SIGNAL(currentIndexChanged(int)), this, SLOT(onMemberListSelectChanged(int)));
    ui->add_book_button->hide();
    ui->kick_member_button->hide();
    ui->delete_book_button->hide();
    setComboBoxItems();
    ui->stackedWidget->setCurrentIndex(0);
}

void DeskAdminPanel::onListItemClicked(const QModelIndex &index)
{
    QString selectedItem = index.data().toString();
    if (selectedItem == "Книги")
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (selectedItem == "Участники")
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

DeskAdminPanel::~DeskAdminPanel()
{
    delete ui;
}

void DeskAdminPanel::onBookListSelectChanged(int index)
{
    if (index == -1)
    {
        ui->delete_book_button->hide();
        ui->book_info->setText("");
    }
    else
    {
        ui->delete_book_button->show();
        int index;
        for (const auto& bookTemp : desk_books) {
            if (bookTemp.second.name == ui->book_list_select->currentText()) {
                index = bookTemp.second.id;
            }
        }
        ui->book_info->setText("Информация о книге:\n");
        if (!this->books[index].name.isEmpty()) {
            ui->book_info->setText(ui->book_info->text() + "Название: " + this->books[index].name + '\n');
        }
        if (!this->books[index].creation_date.isNull()) {
            ui->book_info->setText(ui->book_info->text() + "Год написания: " + QString::number(this->books[index].creation_date.year()) + '\n');
        }
        if (this->books[index].page_count != NULL) {
            ui->book_info->setText(ui->book_info->text() + "Кол-во страниц: " + QString::number(this->books[index].page_count) + '\n');
        }
        if (!this->books[index].description.isEmpty()) {
            ui->book_info->setText(ui->book_info->text() + "Описание: " + this->books[index].description + '\n');
        }
    }
}

void DeskAdminPanel::onBookListAddSelectChanged(int index)
{
    if (index == -1)
    {
        ui->add_book_button->hide();
        ui->book_add_info->setText("");
    }
    else
    {
        ui->add_book_button->show();
        int index;
        for (const auto& bookTemp : books) {
            if (bookTemp.second.name == ui->book_list_to_add_select->currentText()) {
                index = bookTemp.second.id;
            }
        }
        ui->book_add_info->setText("Информация о книге:\n");
        if (!this->books[index].name.isEmpty()) {
            ui->book_add_info->setText(ui->book_add_info->text() + "Название: " + this->books[index].name + '\n');
        }
        if (!this->books[index].creation_date.isNull()) {
            ui->book_add_info->setText(ui->book_add_info->text() + "Год написания: " + QString::number(this->books[index].creation_date.year()) + '\n');
        }
        if (this->books[index].page_count != NULL) {
            ui->book_add_info->setText(ui->book_add_info->text() + "Кол-во страниц: " + QString::number(this->books[index].page_count) + '\n');
        }
        if (!this->books[index].description.isEmpty()) {
            ui->book_add_info->setText(ui->book_add_info->text() + "Описание: " + this->books[index].description + '\n');
        }
    }
}

void DeskAdminPanel::onMemberListSelectChanged(int index)
{
    if (index == -1)
    {
        ui->kick_member_button->hide();
        ui->user_info->clear();
    }
    else
    {
        ui->kick_member_button->show();
        int index;
        for (const auto& user : users) {
            if (user.second.name == ui->member_list_select->currentText()) {
                index = user.second.id;
            }
        }
        ui->user_info->setText("Информация о пользователе:\n");
        if (this->users[index].id) {
            ui->user_info->setText(ui->user_info->text() + "Идентификатор: " + QString::number(this->users[index].id) + '\n');
        }
        if (!this->users[index].name.isEmpty()) {
            ui->user_info->setText(ui->user_info->text() + "Никнейм: " + this->users[index].name + '\n');
        }
    }
}

void DeskAdminPanel::setComboBoxItems()
{
    for (const auto &book : desk_books)
    {
        ui->book_list_select->addItem(book.second.name);
    }
    for (const auto &book : books)
    {
        bool isBookInDeskBooks = false;
        for (const auto &deskBook : desk_books)
        {
            if (book.second.name == deskBook.second.name)
            {
                isBookInDeskBooks = true;
                break;
            }
        }
        if (!isBookInDeskBooks)
        {
            ui->book_list_to_add_select->addItem(book.second.name);
        }
    }

    for (const auto &user : users)
    {
        ui->member_list_select->addItem(user.second.name);
    }
    ui->book_list_select->setCurrentIndex(-1);
    ui->book_list_to_add_select->setCurrentIndex(-1);
    ui->member_list_select->setCurrentIndex(-1);
}

void DeskAdminPanel::on_add_book_button_clicked()
{
    int id;
    QString selectedBook = ui->book_list_to_add_select->currentText();

    for (const auto &bookTemp : books)
    {
//        qDebug() << bookTemp.name << bookTemp.id;
        if (bookTemp.second.name == selectedBook)
        {
            id = bookTemp.second.id;
            break;
        }
    }
    emit add_book_to_desk(books[id]);
}

void DeskAdminPanel::handleBookAdded(Book book)
{
    ui->book_list_select->addItem(book.name);
    ui->book_list_to_add_select->removeItem(ui->book_list_to_add_select->currentIndex());
    ui->book_list_select->setCurrentIndex(-1);
}

void DeskAdminPanel::on_delete_book_button_clicked()
{
    int id;
    QString selectedBook = ui->book_list_select->currentText();
    for (const auto &bookTemp : desk_books)
    {
//        qDebug() << bookTemp.name << bookTemp.id;
        if (bookTemp.second.name == selectedBook)
        {
            id = bookTemp.second.id;
            break;
        }
    }
    emit delete_book_from_desk(desk_books[id]);
}

void DeskAdminPanel::handleBookDeleted(Book book)
{
    ui->book_list_to_add_select->addItem(book.name);
    ui->book_list_select->removeItem(ui->book_list_select->currentIndex());
    ui->book_list_to_add_select->setCurrentIndex(-1);
}

void DeskAdminPanel::on_invite_user_button_clicked()
{
    emit invite_user(ui->member_invite_input->text().toInt());
}

void DeskAdminPanel::on_kick_member_button_clicked()
{
    User user;
    QString selectedUser = ui->member_list_select->currentText();
    for (const auto &userTemp : users)
    {
        if (userTemp.second.name == selectedUser)
        {
            user = userTemp.second;
            break;
        }
    }
    qDebug() << user.id << UserCredentials::instance().userId();
    if (user.id == UserCredentials::instance().userId())
    {
        QMessageBox::critical(this, "Ошибка!", "Нельзя кикнуть самого себя!");
    }
    else
    {
        emit kick_user_from_desk(user);
    }
}

void DeskAdminPanel::handleUserKicked(User user)
{
    ui->member_list_select->removeItem(ui->member_list_select->currentIndex());
    ui->member_list_select->setCurrentIndex(-1);
}

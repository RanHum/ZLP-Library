#include "bigwindow.h"
#include "ui_bigwindow.h"

Bigwindow::Bigwindow(QWidget *parent) : QDialog(parent), ui(new Ui::Bigwindow)
{
    ui->setupUi(this);
    deskForm = new Doska();
    ui->verticalLayoutWidget->setVisible(false);

    desksList = new QListWidget(this);
    connect(deskForm, &Doska::signal, this, &Bigwindow::onAddWidget);

    addBookForm = new book_form();
    connect(addBookForm, &book_form::add_book, this, &Bigwindow::on_create_book);

    ui->bookScrollArea->setVisible(false);
    ui->bookScrollArea->setWidgetResizable(true);
    ui->bookScrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(ui->bookContainerLayout);
    ui->admin_desk_button->setVisible(false);
    ui->close_desk_button->setVisible(false);
    ui->delete_desk_button->setVisible(false);
    get_desks();
    get_books();
    qDebug() << books.size();
}

void Bigwindow::get_desks()
{
    auto req = makeReqJson("desk", "get_all");
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        QJsonArray resp_json_array = resp["result"].toArray();
        for (const QJsonValue &value : resp_json_array)
        {
            add_desk_to_list(get_desk(value.toObject()["desk_id"].toInt()));
        }
    }
}

Desk Bigwindow::get_desk(int desk_id)
{
    auto req = makeReqJson("desk", "get");
    req.insert("desk_id", desk_id);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        Desk desk;
        desk.id = desk_id;
        desk.name = resp["result"]["name"].toString();
        desk.owner = resp["result"]["owner"].toInt();
        desk.background = QImage(resp["result"]["background"].toString());
        return desk;
    }
    return {};
}

std::map<int, Book> Bigwindow::get_desk_books(int desk_id)
{
    auto req = makeReqJson("desk", "list_books");
    req.insert("desk_id", desk_id);
    const auto resp = RequestClass().sendRequest(req);
    std::map<int, Book> books;
    if (check_status(resp))
    {
        QJsonArray resp_json_array = resp["result"].toArray();
        for (const QJsonValue &value : resp_json_array)
        {
            int book_id = value.toObject()["book_id"].toInt();
            books[book_id] = get_book(book_id);
        }
    }
    return books;
}

Book Bigwindow::get_book(int book_id)
{
    auto req = makeReqJson("book", "get");
    req.insert("book_id", book_id);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        Book book;
        book.id = book_id;
        book.name = resp["result"]["name"].toString();
        book.book_cover = resp["result"]["book_cover"].toInt();
        book.description = resp["result"]["description"].toString();
        book.page_count = resp["result"]["page_count"].toInt();
        book.format = resp["result"]["format"].toInt();
        book.locator = resp["result"]["locator"].toInt();
        book.owner = resp["result"]["owner"].toInt();
        book.creation_date = QDate::fromString(resp["result"]["creation_date"].toString(), "yyyy-MM-dd");
        return book;
    }
    return {};
}

void Bigwindow::get_books()
{
    auto req = makeReqJson("book", "get_all");
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        QJsonArray resp_json_array = resp["result"].toArray();
        for (const QJsonValue &value : resp_json_array)
        {
            qDebug() << value;
            Book book;
            book.id = value["book_id"].toInt();
            book.name = value["name"].toString();
            book.book_cover = value["book_cover"].toInt();
            book.description = value["description"].toString();
            book.page_count = value["page_count"].toInt();
            book.format = value["format"].toInt();
            book.locator = value["locator"].toInt();
            book.owner = value["owner"].toInt();
            book.creation_date = QDate::fromString(value["creation_date"].toString(), "yyyy-mm-dd");
            books[book.id] = book;
        }
    }
    qDebug() << "books:" << books.size();
}

std::map<int, User> Bigwindow::get_desk_users(int desk_id)
{
    auto req = makeReqJson("desk", "get_users");
    req.insert("desk_id", desk_id);
    const auto resp = RequestClass().sendRequest(req);
    std::map<int, User> users;
    if (check_status(resp))
    {
        QJsonArray resp_json_array = resp["result"].toArray();
        for (const QJsonValue &value : resp_json_array)
        {
            users[value["user_id"].toInt()] = get_user(value["user_id"].toInt());
        }
    }
    return users;
}

User Bigwindow::get_user(int user_id)
{
    auto req = makeReqJson("user", "get");
    req.insert("user_id", user_id);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        User user;
        user.id = user_id;
        user.name = resp["result"]["name"].toString();
        user.avatar = resp["result"]["avatar"].toInt();
        return user;
    }
    return {};
}

Bigwindow::~Bigwindow()
{
    delete ui;
}

void Bigwindow::slot(const QString &text)
{
}

void Bigwindow::on_label_linkActivated(const QString &link)
{
}

void Bigwindow::on_add_desk_button_clicked()
{
    deskForm->setWindowModality(Qt::WindowModal);
    deskForm->show();
}

void Bigwindow::add_desk_to_list(Desk desk)
{
    user_desks[desk.id] = desk;

    Full *fullWidget = new Full;
    fullWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    fullWidget->setDesk(desk);
    QVariantMap desk_data;
    desk_data["id"] = desk.id;
    desk_data["name"] = desk.name;
    desk_data["owner"] = desk.owner;
    desk_data["background"] = desk.background;
    desk_data["sort"] = desk.sort;

    QListWidgetItem *item = new QListWidgetItem();
    int additionalHeight = 230;
    QSize sizeHint = fullWidget->sizeHint();
    sizeHint.setHeight(sizeHint.height() + additionalHeight);
    item->setSizeHint(sizeHint);
    item->setData(Qt::UserRole, QVariant::fromValue(desk));
    desksList->addItem(item);
    desksList->setItemWidget(item, fullWidget);
    fullWidget->item = item;
    connect(fullWidget, &Full::clicked, this, &Bigwindow::on_desk_item_clicked);
}

void Bigwindow::onAddWidget(const QString &text)
{
    auto req = makeReqJson("desk", "add");
    req.insert("name", text);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        Desk desk;
        desk.id = resp["result"]["desk_id"].toInt();
        desk.background = QImage(resp["result"]["background"].toString());
        desk.name = resp["result"]["name"].toString();
        desk.sort = resp["result"]["sort"].toInt();
        desk.owner = UserCredentials::instance().userId();
        desk.users = get_desk_users(desk.id);
        add_desk_to_list(desk);
    }
    else
    {
        qDebug() << resp;
        QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
    }
}

void Bigwindow::slot_remove_fullWidget(Full *deskItemWidget)
{
    delete desksList->takeItem(desksList->row(deskItemWidget->item));
    delete deskItemWidget;
}

void Bigwindow::on_desk_item_clicked(Full *desk_list_item)
{
    int desk_id = desk_list_item->getDeskId();
    user_desks[desk_id].books = get_desk_books(desk_id);
    user_desks[desk_id].users = get_desk_users(desk_id);
    generate_book_containers(user_desks[desk_list_item->getDeskId()].books);

    ui->close_desk_button->setVisible(true);
    if (desk_list_item->getOwner() == UserCredentials::instance().userId())
    {
        ui->delete_desk_button->setText("Удалить доску");
        ui->admin_desk_button->setVisible(true);
    }
    else
    {
        ui->delete_desk_button->setText("Выйти из доски");
        ui->admin_desk_button->setVisible(false);
    }
    ui->delete_desk_button->setVisible(true);
}

void Bigwindow::generate_book_containers(const std::map<int, Book> &books)
{
    clear_book_containers();
    int row = 0;
    int column = 0;

    ui->bookScrollArea->show();
    int availableWidth = ui->bookScrollArea->width();
    int containerWidth = 232;
    int numColumns = availableWidth / containerWidth;

    for (const auto &book : books)
    {
        BookContainer *bookContainer = new BookContainer(&(book.second));

        ui->bookContainerLayout->addWidget(bookContainer, row, column);

        column++;
        if (column >= numColumns)
        {
            column = 0;
            row++;
        }
    }
}

void Bigwindow::clear_book_containers()
{
    QLayoutItem *item;
    while ((item = ui->bookContainerLayout->takeAt(0)) != nullptr)
    {
        delete item->widget(); // Удаление контейнера
        delete item;           // Удаление элемента разметки
    }
}

void Bigwindow::on_close_desk_button_clicked()
{
    clear_book_containers();
    ui->bookScrollArea->setVisible(false);
    ui->admin_desk_button->setVisible(false);
    ui->close_desk_button->setVisible(false);
    ui->delete_desk_button->setVisible(false);
}

void Bigwindow::on_delete_desk_button_clicked()
{
    on_close_desk_button_clicked();
    QListWidgetItem *currentItem = desksList->currentItem();
    if (currentItem == nullptr)
    {
        return;
    }

    QJsonObject resp;
    QJsonObject req;
    auto desk_data = currentItem->data(Qt::UserRole).value<Desk>();
    if (desk_data.owner == UserCredentials::instance().userId())
    {
        req = makeReqJson("desk", "delete");
    }
    else
    {
        req = makeReqJson("user", "leave_desk");
    }
    req.insert("desk_id", desk_data.id);
    resp = RequestClass().sendRequest(req);
    qDebug() << req << resp;
    if (check_status(resp))
    {
        user_desks.erase(desk_data.id);
        desksList->takeItem(desksList->row(currentItem));
        delete currentItem;
    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
    }
}

void Bigwindow::on_create_book(const QString name,
                               const QString creation_date,
                               const QString description,
                               const QString page_count,
                               const QString format,
                               const QString authors,
                               const QString genres)
{
    auto req = makeReqJson("book", "add");
    if (!name.isEmpty())
        req.insert("name", name);
    if (!description.isEmpty())
        req.insert("description", description);
    if (!page_count.isEmpty())
        req.insert("page_count", page_count);
    if (!format.isEmpty())
        req.insert("format", format);
    QRegularExpression dateRegex("\\d{2}\\.\\d{2}\\.\\d{4}");
    QRegularExpressionMatch match = dateRegex.match(creation_date);
    QDate date;
    if (match.hasMatch())
    {
        date = QDate::fromString(creation_date, "dd.MM.yyyy");
    }
    else
    {
        bool ok;
        int year = creation_date.toInt(&ok);
        if (ok)
        {
            date = QDate(year, 1, 1);
        }
    }

    if (date.isValid())
    {
        QString formattedDate = date.toString("dd.MM.yyyy");
        req.insert("creation_date", formattedDate);
    }
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        Book book;
        book.id = resp["result"]["book_id"].toInt();
        book.name = resp["result"]["name"].toString();
        book.creation_date = QDate::fromString(resp["result"]["creation_date"].toString());
        book.book_cover = resp["result"]["book_cover"].toInt();
        book.description = resp["result"]["description"].toString();
        book.page_count = resp["result"]["page_count"].toInt();
        book.format = resp["result"]["format"].toInt();
        book.locator = resp["result"]["locator"].toInt();
        book.owner = resp["result"]["owner"].toInt();
        books[book.id] = book;
    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
    }
}

void Bigwindow::on_profile_button_clicked()
{
    profile *window = new profile();
    window->setWindowModality(Qt::WindowModal);
    window->show();
    connect(window, &profile::joinedInDesk, this, &Bigwindow::joinInDesk);
}

void Bigwindow::on_avatar_button_clicked()
{
    if (ui->verticalLayoutWidget->isVisible())
        ui->verticalLayoutWidget->setVisible(false);
    else
        ui->verticalLayoutWidget->setVisible(true);
}

void Bigwindow::on_create_book_button_clicked()
{
    addBookForm->setWindowModality(Qt::WindowModal);
    addBookForm->show();
}

void Bigwindow::on_admin_desk_button_clicked()
{
    QListWidgetItem *currentItem = desksList->currentItem();
    if (currentItem == nullptr)
    {
        return;
    }
    auto desk_id = currentItem->data(Qt::UserRole).value<Desk>().id;

    DeskAdminPanel adminPanel = DeskAdminPanel(user_desks[desk_id].books, books, user_desks[desk_id].users, this);
    connect(&adminPanel, SIGNAL(add_book_to_desk(Book)), this, SLOT(add_book_to_desk(Book)));
    connect(&adminPanel, SIGNAL(delete_book_from_desk(Book)), this, SLOT(delete_book_from_desk(Book)));
    connect(&adminPanel, SIGNAL(kick_user_from_desk(User)), this, SLOT(kick_user_from_desk(User)));
    connect(this, &Bigwindow::addedBook, &adminPanel, &DeskAdminPanel::handleBookAdded);
    connect(this, &Bigwindow::deletedBook, &adminPanel, &DeskAdminPanel::handleBookDeleted);
    connect(this, &Bigwindow::kickedUser, &adminPanel, &DeskAdminPanel::handleUserKicked);
    connect(&adminPanel, &DeskAdminPanel::invite_user, this, &Bigwindow::send_invite_to_user);
    adminPanel.exec();
}

void Bigwindow::add_book_to_desk(Book book)
{
    auto req = makeReqJson("desk", "add_book");
    Desk desk = desksList->currentItem()->data(Qt::UserRole).value<Desk>();
    req.insert("desk_id", desk.id);
    req.insert("book_id", book.id);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        user_desks[desk.id].books[book.id] = book;
        generate_book_containers(user_desks[desk.id].books);
        emit addedBook(book);
    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
    }
}

void Bigwindow::delete_book_from_desk(Book book)
{
    auto req = makeReqJson("desk", "delete_book");
    Desk desk = desksList->currentItem()->data(Qt::UserRole).value<Desk>();
    req.insert("desk_id", desk.id);
    req.insert("book_id", book.id);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        user_desks[desk.id].books.erase(book.id);
        generate_book_containers(user_desks[desk.id].books);
        emit deletedBook(book);
    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
    }
}

void Bigwindow::send_invite_to_user(int user_id)
{
    auto req = makeReqJson("invite", "send");
    Desk desk = desksList->currentItem()->data(Qt::UserRole).value<Desk>();
    req.insert("desk_id", desk.id);
    req.insert("user_id", user_id);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        QMessageBox::information(this, "Уведомление", "Приглашение успешно отправлено!");
    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
    }
}

void Bigwindow::kick_user_from_desk(User user)
{
    auto req = makeReqJson("desk", "kick_user");
    req.insert("desk_id", desksList->currentItem()->data(Qt::UserRole).value<Desk>().id);
    req.insert("user_id", user.id);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        emit kickedUser(user);
    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
    }
}

void Bigwindow::joinInDesk(int desk_id) {
    add_desk_to_list(get_desk(desk_id));
}

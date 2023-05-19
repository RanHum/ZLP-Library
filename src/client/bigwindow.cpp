#include "bigwindow.h"
#include "ui_bigwindow.h"
#include <QMessageBox>
#include <QThread>
#include <QListWidget>
#include <QMainWindow>
#include "doska.h"
#include "full.h"
#include "requests.h"
#include "api_utils.h"
#include <ctime>
#include <cstdlib>
#include "profile.h"

struct BookInfo
{
    QString title;
    QString author;
    // Другие поля книги
};

auto received_book_date = std::vector<BookInfo>();

Bigwindow::Bigwindow(QWidget *parent) : QDialog(parent), ui(new Ui::Bigwindow) {
    ui->setupUi(this);
    deskForm = new Doska();
    ui->verticalLayoutWidget->setVisible(false);
    desksList = new QListWidget(this);
    connect(deskForm, &Doska::signal, this, &Bigwindow::onAddWidget);
    addBookForm = new book_form();
    connect(addBookForm, &book_form::add_book, this, &Bigwindow::onAddBook);
    ui->bookScrollArea->setVisible(false);
    ui->add_book_button->setVisible(false);
    ui->close_desk_button->setVisible(false);
    ui->delete_desk_button->setVisible(false);
}

Bigwindow::~Bigwindow()
{
    delete ui;
}


void Bigwindow::slot(const QString& text)
{

}
void Bigwindow::on_profile_button_clicked()
{
    // push on circle button
    if(  ui->verticalLayoutWidget->isVisible())
        ui->verticalLayoutWidget->setVisible(false);
    else
          ui->verticalLayoutWidget->setVisible(true);
}

void Bigwindow::on_label_linkActivated(const QString &link)
{

}

void Bigwindow::on_add_desk_button_clicked()
{
    deskForm->setWindowModality(Qt::WindowModal);
    deskForm->show();
}


void Bigwindow::onAddWidget(const QString& text) {
//    auto req = makeReqJson("desk", "add");
//    req.insert("name", text);
//    const auto resp = RequestClass().sendRequest(req);
//    if (check_status(resp)) {
          Full* fullWidget = new Full;
 fullWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
          // Установка текста в виджете Full
          fullWidget->setText(text);

          // Создание нового элемента QListWidgetItem и добавление виджета Full в него
          QListWidgetItem* item = new QListWidgetItem();
          int additionalHeight = 230;
          QSize sizeHint = fullWidget->sizeHint();
          sizeHint.setHeight(sizeHint.height() + additionalHeight);
          item->setSizeHint(sizeHint);
//          item->setSizeHint(QSize(fullWidget->sizeHint().width(), fullWidget->sizeHint().height() + 130));
          desksList->addItem(item);
          desksList->setItemWidget(item, fullWidget);
          fullWidget->item = item;

          connect(fullWidget,&Full::remove_requested,this, &Bigwindow::slot_remove_fullWidget);
          connect(fullWidget,&Full::clicked,this, &Bigwindow::on_desk_item_clicked);
//    }
//    else {
//          qDebug() << resp;
//          QMessageBox::critical(this, "Ошибка!", "Не удалось создать доску!");
//    }

}

void Bigwindow::slot_remove_fullWidget(Full* deskItemWidget)
{
          delete desksList->takeItem(desksList->row(deskItemWidget->item));
          delete deskItemWidget;
}

void Bigwindow::on_desk_item_clicked(Full* desk)
{
          // Очистка предыдущей области с контейнерами (если есть)
          clear_book_containers();

          // Получение идентификатора выбранной доски (возможно, его нужно сохранить в QListWidgetItem)
          QString desk_id = desk->item->data(Qt::UserRole).toString();

          // Генерация контейнеров и заполнение их книгами для выбранной доски
          generate_book_containers(desk_id);
          ui->add_book_button->setVisible(true);
          ui->close_desk_button->setVisible(true);
          ui->delete_desk_button->setVisible(true);
}

// Функция для генерации контейнеров и заполнения их книгами
void Bigwindow::generate_book_containers(const QString& desk_id)
{
          // Выполнить запрос к API для получения информации о книгах для выбранной доски

          // Создайте контейнеры и заполните их книгами
          int row = 0;
          int column = 0;
          srand(static_cast<unsigned>(time(nullptr)));
          received_book_date.clear();

          for (int i = 0; i < 20; ++i)
          {
              BookInfo bookInfo;
              bookInfo.title = "Book Title " + QString::number(i);
              bookInfo.author = "Author " + QString::number(i);
              // Другие поля книги

              // Добавление сгенерированной книги в receivedBookData
              received_book_date.push_back(bookInfo);
          }

          ui->bookScrollArea->show();
          ui->bookScrollArea->updateGeometry();
          int availableWidth = ui->bookScrollArea->width();
          int containerWidth = 200;
          int numColumns = availableWidth / containerWidth;

          for (const auto& bookInfo : received_book_date)
          {
              BookContainer* bookContainer = new BookContainer;
              bookContainer->setTitle(bookInfo.title);
              bookContainer->setAuthor(bookInfo.author);
          // Другие настройки контейнера книги

          // Добавьте контейнер в область с контейнерами с использованием QGridLayout
              ui->bookContainerLayout->addWidget(bookContainer, row, column);

              // Увеличиваем индексы строки и столбца для следующего контейнера
              column++;
              if (column >= numColumns)
              {
                  column = 0;
                  row++;
              }
          }
}

// Функция для очистки области с контейнерами
void Bigwindow::clear_book_containers()
{
          QLayoutItem* item;
          while ((item = ui->bookContainerLayout->takeAt(0)) != nullptr)
          {
          delete item->widget(); // Удаление контейнера
          delete item; // Удаление элемента разметки
          }
}

void Bigwindow::on_close_desk_button_clicked()
{
        clear_book_containers();
        ui->bookScrollArea->setVisible(false);
        ui->add_book_button->setVisible(false);
        ui->close_desk_button->setVisible(false);
        ui->delete_desk_button->setVisible(false);
}


void Bigwindow::on_delete_desk_button_clicked()
{
        on_close_desk_button_clicked();
}


void Bigwindow::on_add_book_button_clicked()
{
        addBookForm->setWindowModality(Qt::WindowModal);
        addBookForm->show();
}

void Bigwindow::onAddBook(const QString& name,
                          const QString& date,
                          const QString& description,
                          const QString& page_count,
                          const QString& format,
                          const QString& authors,
                          const QString& genres) {
        received_book_date.push_back({name, authors});
        BookContainer* bookContainer = new BookContainer;
        bookContainer->setTitle(name);
        bookContainer->setAuthor(authors);
        ui->bookContainerLayout->addWidget(bookContainer);
}


void Bigwindow::on_profile_button_clicked()
{
        profile* window = new profile();
        window->setUserName(UserCredentials::instance().login());
        window->setWindowModality(Qt::WindowModal);
        window->show();
}

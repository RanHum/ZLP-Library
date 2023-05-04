#include "bigwindow.h"
#include "ui_bigwindow.h"
#include <QMessageBox>
#include <QThread>
#include <QListWidget>
#include <QMainWindow>
#include "doska.h"
#include "full.h"
Bigwindow::Bigwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bigwindow)
{
    ui->setupUi(this);
    doska = new Doska();
    ui->verticalLayoutWidget->setVisible(false);
    connect(doska, &Doska::signal, this, &Bigwindow::slot);
    widgetList = new QListWidget(this);

        connect(doska, &Doska::signal, this, &Bigwindow::onAddWidget);
}

Bigwindow::~Bigwindow()
{
    delete ui;
}


void Bigwindow::slot(const QString& text)
{
    //onAddWidget(text);
    ui->label->setText(text);
}
void Bigwindow::on_pushButton_clicked()
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



void Bigwindow::on_pushButton_25_clicked()
{

}


void Bigwindow::on_pushButton_3_clicked()
{
 doska->setWindowModality(Qt::WindowModal);
 doska->show();
 //this->close();


}

void Bigwindow::onAddWidget(const QString& text) {
    // Создание нового экземпляра виджета Full
       Full* fullWidget = new Full;
        fullWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
       // Установка текста в виджете Full
       fullWidget->setText(text);

  /*     // установка менеджера компоновки и добавление виджета на форму Doska
           QVBoxLayout* layout = new QVBoxLayout(this);
           layout->addWidget(fullWidget);
           setLayout(layout);

          // создание и настройка кнопки для удаления виджета
              QPushButton* button = new QPushButton("Remove");
              button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
              button->setFixedWidth(80);

              // добавление кнопки на форму Bigwindow
                  QHBoxLayout* hbox = new QHBoxLayout(fullWidget);
                  hbox->addStretch(1);
                  hbox->addWidget(button);

                  // соединение сигнала нажатия на кнопку со слотом удаления виджета
                     connect(button, &QPushButton::clicked, fullWidget, &QWidget::deleteLater);
*/
       // Создание нового элемента QListWidgetItem и добавление виджета Full в него
       QListWidgetItem* item = new QListWidgetItem();
       item->setSizeHint(fullWidget->sizeHint());
       widgetList->addItem(item);
       widgetList->setItemWidget(item, fullWidget);

       connect(fullWidget,&Full::on_close,this,&Bigwindow::slot_remove_fullWidget);
}

void Bigwindow::slot_remove_fullWidget()
{
    QListWidgetItem* item = (QListWidgetItem*)sender();
    delete widgetList->takeItem(widgetList->row(item));
    //widgetList->removeItemWidget(item);
    delete item;
}

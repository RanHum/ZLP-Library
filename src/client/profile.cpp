#include "profile.h"
#include "ui_profile.h"

profile::profile(QWidget *parent) : QWidget(parent),
                                    ui(new Ui::profile)
{
    ui->setupUi(this);
    ui->user_id->setText(ui->user_id->text() + " " + QString::number(UserCredentials::instance().userId()));
    ui->username->setText(ui->username->text() + " " + UserCredentials::instance().login());
    auto req = makeReqJson("invite", "list");
    req.insert("status", 1);
    const auto resp = RequestClass().sendRequest(req);
    ui->invite_list->setContentsMargins(0, 0, 0, 0);
    ui->invite_list->setStyleSheet("QListWidget::item { padding-top: 5px; padding-bottom: 5px; }"
                                   "QWidget { display: flex; align-items: center; }");
    if (check_status(resp))
    {
        QJsonArray resp_json_array = resp["result"].toArray();
        for (const QJsonValue &value : resp_json_array)
        {
            auto desk_req = makeReqJson("desk", "get");
            desk_req.insert("desk_id", value["desk_id"].toInt());
            const auto desk_resp = RequestClass().sendRequest(desk_req);
            if (check_status(desk_resp))
            {
                QWidget *item = createInviteWidget(value["desk_id"].toInt(), desk_resp["result"]["name"].toString());
                //                item->setFixedSize(item->sizeHint().width(), item->sizeHint().height());
                QListWidgetItem *invite_list_item = new QListWidgetItem(ui->invite_list);
                invite_list_item->setSizeHint(item->sizeHint());
                invite_list_item->setData(Qt::UserRole, value["desk_id"]);
                ui->invite_list->addItem(invite_list_item);
                ui->invite_list->setItemWidget(invite_list_item, item);
                QPushButton *accept_button = item->findChild<QPushButton *>("accept_button");
                QPushButton *decline_button = item->findChild<QPushButton *>("decline_button");
                QList<QWidget *> children = item->findChildren<QWidget *>();
                for (QWidget *child : children)
                {
                    qDebug() << "Child widget: " << child;
                }
                if (accept_button && decline_button)
                {
                    qDebug() << "qq";
                    connect(accept_button, &QPushButton::clicked, this, [=]()
                            { handleAcceptButtonClicked(invite_list_item); });

                    connect(decline_button, &QPushButton::clicked, this, [=]()
                            { handleCancelButtonClicked(invite_list_item); });
                }
            }
        }
    }
}

QWidget *profile::createInviteWidget(const int desk_id, const QString &desk_name)
{
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(widget);
    QLabel *desk_title = new QLabel(desk_name);
    QPushButton *accept_button = new QPushButton("Принять");
    accept_button->setObjectName("accept_button");
    QPushButton *decline_button = new QPushButton("Отменить");
    decline_button->setObjectName("decline_button");
    layout->addWidget(desk_title);
    layout->addWidget(accept_button);
    layout->addWidget(decline_button);
    widget->setLayout(layout);

    return widget;
}

profile::~profile()
{
    delete ui;
}

void profile::on_back_button_clicked()
{
    this->close();
}

void profile::handleAcceptButtonClicked(QListWidgetItem *invite_list_item)
{
    qDebug() << "clicked";
    int desk_id = invite_list_item->data(Qt::UserRole).toInt();
    auto req = makeReqJson("invite", "accept");
    req.insert("desk_id", desk_id);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        QMessageBox::information(this, "Уведомление", "Приглашение успешно принято");
        ui->invite_list->takeItem(ui->invite_list->row(invite_list_item));
        delete invite_list_item;
        emit joinedInDesk(desk_id);
    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
    }
}

void profile::handleCancelButtonClicked(QListWidgetItem *invite_list_item)
{
    int desk_id = invite_list_item->data(Qt::UserRole).toInt();
    auto req = makeReqJson("invite", "decline");
    req.insert("desk_id", desk_id);
    const auto resp = RequestClass().sendRequest(req);
    if (check_status(resp))
    {
        QMessageBox::information(this, "Уведомление", "Приглашение успешно отменено");
        ui->invite_list->takeItem(ui->invite_list->row(invite_list_item));
        delete invite_list_item;
    }
    else
    {
        QMessageBox::critical(this, "Ошибка!", resp["text"].toString());
    }
}

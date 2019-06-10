#include "requestdelegate.h"
#include <QDebug>
#include <QJsonObject>

RequestDelegate::RequestDelegate(QWidget *parent) : QStyledItemDelegate (parent)
{

}

void RequestDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 1)
        return;
    //all to do
    QFont font;
    QPen pen;
    pen.setColor(QColor(Qt::black));


    painter->setRenderHint(QPainter::Antialiasing);
    QJsonObject jsonObject = index.data().toJsonObject();
    if (option.state & QStyle::State_HasFocus) {
        //pen.setColor(QColor(Qt::white));
    }
    else {
        //painter->drawImage(option.rect, QImage("://resources/background-cement-concrete-242236-2.jpg"));
    }

    painter->setPen(pen);
    font.setPointSize(12);
    painter->setFont(font);
    QRectF nameRect(option.rect.x() + 4, option.rect.y() + 4, option.rect.width(), 30);
    painter->drawText(nameRect, Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap | Qt::TextJustificationForced, jsonObject["name"].toString());

    QRectF countryRect(nameRect.x() + 2, nameRect.bottomLeft().y() + 2, option.rect.width() / 2, 30);
    font.setPointSize(8);
    painter->setFont(font);
    painter->drawText(countryRect, "Country: " + jsonObject["country"].toString());
    QRectF bitRateRect(countryRect.bottomRight().x(), countryRect.topRight().y(), option.rect.width() - countryRect.width(), 20);
    painter->drawText(bitRateRect, Qt::AlignCenter | Qt::TextWordWrap, "Bitrate: " + jsonObject["bitrate"].toString());
    //painter->drawLine(option.rect.bottomLeft().x(), option.rect.bottomLeft().y(),
    //                  option.rect.bottomRight().x(), option.rect.bottomRight().y());

    qDebug() << jsonObject["favorite"].toBool();
    if (jsonObject["favorite"].toBool() == true) {
        qDebug() << "it is true";
        QIcon starIcon("://resources/baseline-star-24px.svg");
        painter->drawPixmap(option.rect.x() + option.rect.width() - 40, option.rect.y(), 32, 32, starIcon.pixmap(QSize(32, 32)));
    }
    else {
        QIcon starIcon("://resources/baseline-star_border-24px.svg");
        painter->drawPixmap(option.rect.x() + option.rect.width() - 40, option.rect.y(), 32, 32, starIcon.pixmap(QSize(32, 32)));
    }

}

QSize RequestDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QRect rect(option.rect.x(), option.rect.y(), option.rect.width(), 60);
    return rect.size();
}

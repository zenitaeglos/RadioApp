#include "requestdelegate.h"
#include <QDebug>
#include <QJsonObject>

RequestDelegate::RequestDelegate(QWidget *parent) : QStyledItemDelegate (parent)
{

}

void RequestDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //all to do
    QFont font;


    painter->setRenderHint(QPainter::Antialiasing);
    //painter->setPen(QPen(Qt::black, 0.2));
    painter->setPen(Qt::NoPen);
    painter->drawRect(option.rect);
    QJsonObject jsonObject = index.data().toJsonObject();

    painter->setPen(QPen(Qt::white));
    font.setPointSize(12);
    painter->setFont(font);
    QRectF nameRect(option.rect.x() + 2, option.rect.y() + 2, option.rect.width(), 30);
    painter->drawText(nameRect, Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap | Qt::TextJustificationForced, jsonObject["name"].toString());

    QRectF countryRect(nameRect.x() + 2, nameRect.bottomLeft().y() + 2, option.rect.width() / 2, 30);
    font.setPointSize(10);
    painter->setFont(font);
    painter->drawText(countryRect, "Country: " + jsonObject["country"].toString());
    QRectF bitRateRect(countryRect.bottomRight().x(), countryRect.topRight().y(), option.rect.width() - countryRect.width(), 20);
    painter->drawText(bitRateRect, Qt::AlignCenter | Qt::TextWordWrap, "Bitrate: " + jsonObject["bitrate"].toString());
    painter->drawLine(option.rect.bottomLeft().x(), option.rect.bottomLeft().y(), option.rect.bottomRight().x(), option.rect.bottomRight().y());
}

QSize RequestDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QRect rect(option.rect.x(), option.rect.y(), option.rect.width(), 60);
    return rect.size();
}

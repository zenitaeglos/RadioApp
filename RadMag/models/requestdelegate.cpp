#include "requestdelegate.h"
#include <QDebug>
#include <QJsonObject>

RequestDelegate::RequestDelegate(QWidget *parent) : QStyledItemDelegate (parent)
{

}

void RequestDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //all to do

    QRectF square(option.rect.x(), option.rect.y(), option.rect.width(), 120);

    painter->drawRect(square);
    QJsonObject jsonObject = index.data().toJsonObject();

    painter->drawText(square, Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap, jsonObject["name"].toString());
    painter->drawText(square, Qt::AlignBottom | Qt::AlignLeft | Qt::TextWordWrap, jsonObject["country"].toString());
    painter->drawText(square, Qt::AlignCenter | Qt::TextWordWrap, jsonObject["biterate"].toString());



}

QSize RequestDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect(option.rect.x(), option.rect.y(), option.rect.width(), 120);
    return rect.size();
}

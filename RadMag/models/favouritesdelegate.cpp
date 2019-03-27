#include "favouritesdelegate.h"

FavouritesDelegate::FavouritesDelegate(QWidget *parent) : QStyledItemDelegate (parent)
{

}

void FavouritesDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QJsonObject jsonObject = index.data().toJsonObject();
    QFont font;

    font.setPointSize(10);

    painter->setFont(font);

    QRectF nameRect(option.rect.x() + 2, option.rect.y() + 2, option.rect.width(), option.rect.height());


    painter->drawText(nameRect, Qt::AlignCenter, jsonObject["name"].toString());
}

QSize FavouritesDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    return option.rect.size();
}

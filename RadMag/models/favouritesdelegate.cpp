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

    QRectF nameRect(option.rect.x() + 12, option.rect.y(), option.rect.width() - 40, option.rect.height());


    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, jsonObject["name"].toString());
    QIcon removeIcon("://resources/baseline-remove_circle_outline-24px.svg");
    painter->drawPixmap(option.rect.width() - 24, option.rect.y() + 4, 20, 20, removeIcon.pixmap(QSize(24, 24)));
}

QSize FavouritesDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    return option.rect.size();
}

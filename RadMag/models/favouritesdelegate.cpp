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


    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, jsonObject[RadioStation::getType(RadioStation::Name)].toString());
    QIcon removeIcon(DataSource::resource(DataSource::RemoveWhite));
    painter->drawPixmap(option.rect.width() - 24, option.rect.y() + 4, 20, 20, removeIcon.pixmap(QSize(24, 24)));
}

QSize FavouritesDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    return option.rect.size();
}

bool FavouritesDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(model);
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouse = static_cast<QMouseEvent*>(event);
        emit currentIndexChanged(index.row());
        if (mouse->pos().x() > option.rect.width() - 20 && mouse->pos().y() < option.rect.y() + 20) {
            emit removeClicked(index.row());
        }
    }
    if (event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent* mouse = static_cast<QMouseEvent*>(event);
        if (mouse->pos().x() < option.rect.width() - 20)
            emit playFavoriteClicked();
    }
    return true;
}

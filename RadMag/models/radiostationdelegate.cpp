#include "radiostationdelegate.h"
#include <QDebug>
#include <QJsonObject>

RadioStationDelegate::RadioStationDelegate(QWidget *parent) : QStyledItemDelegate (parent)
{

}

void RadioStationDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QFont font;
    QPen pen;
    pen.setColor(QColor(Qt::white));


    painter->setRenderHint(QPainter::Antialiasing);
    QJsonObject jsonObject = index.data().toJsonObject();

    painter->setPen(pen);
    font.setPointSize(12);
    painter->setFont(font);
    QRectF nameRect(option.rect.x() + 4, option.rect.y() + 4, option.rect.width(), 30);
    painter->drawText(nameRect, Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap | Qt::TextJustificationForced,
                      jsonObject[RadioStation::getType(RadioStation::Name)].toString());

    QRectF countryRect(nameRect.x() + 2, nameRect.bottomLeft().y() + 2, option.rect.width() / 2, 30);
    font.setPointSize(8);
    painter->setFont(font);
    painter->drawText(countryRect, tr("Country: ") + jsonObject[RadioStation::getType(RadioStation::Country)].toString());
    QRectF bitRateRect(countryRect.bottomRight().x(), countryRect.topRight().y(), option.rect.width() - countryRect.width() - 60, 20);
    int bitrateValue = jsonObject[RadioStation::getType(RadioStation::Bitrate)].toInt();
    painter->drawText(bitRateRect,
                      Qt::AlignCenter | Qt::TextWordWrap, tr("Bitrate: ") + QString::number(bitrateValue));

    //set the icon to only be border or complete, depending if it belongs to favorites or not.
    if (jsonObject["favorite"].toBool() == true) {
        QIcon starIcon(DataSource::resource(DataSource::Star));
        painter->drawPixmap(option.rect.x() + option.rect.width() - 60, option.rect.y(), 32, 32, starIcon.pixmap(QSize(32, 32)));
    }
    else {
        QIcon starIcon(DataSource::resource(DataSource::StarBorder));
        painter->drawPixmap(option.rect.x() + option.rect.width() - 60, option.rect.y(), 32, 32, starIcon.pixmap(QSize(32, 32)));
    }

}

QSize RadioStationDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    QRect rect(option.rect.x(), option.rect.y(), option.rect.width(), 60);
    return rect.size();
}

bool RadioStationDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouse = static_cast<QMouseEvent*>(event);
        if (mouse->pos().x() > option.rect.width() - 50 && mouse->pos().y() < option.rect.y() + 30 &&
                mouse->pos().x() < option.rect.width() - 30) {
            QJsonObject jsonObject = model->data(index).toJsonObject();
            bool favorite = true;
            if (jsonObject[RadioStation::getType(RadioStation::IsFavorite)].toBool())
                favorite = false;
            emit starClickedMouse(index.row(), favorite, option.rect.y() + 16);
        }
        else {
            emit currentIndexChanged(index.row());
        }
    }
    if (event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent* mouse = static_cast<QMouseEvent*>(event);
        if (mouse->pos().x() < option.rect.width() - 30)
            emit doubleClickPressed();
    }
    return true;
}


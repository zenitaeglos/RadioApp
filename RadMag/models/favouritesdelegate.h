#ifndef FAVOURITESDELEGATE_H
#define FAVOURITESDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QJsonObject>

class FavouritesDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FavouritesDelegate(QWidget *parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:

public slots:
};

#endif // FAVOURITESDELEGATE_H

#ifndef FAVOURITESDELEGATE_H
#define FAVOURITESDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QJsonObject>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include "../requests/radiostation.h"
#include "datasource/datasource.h"

class FavouritesDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FavouritesDelegate(QWidget *parent = nullptr);

    void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;


    //catch mouse clicks to add or remove favorites
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

signals:
    //delete an element from favorites
    void removeClicked(int position);
    // double click signal to play favorite
    void playFavoriteClicked();
    //set current index
    void currentIndexChanged(int index);

public slots:
};

#endif // FAVOURITESDELEGATE_H

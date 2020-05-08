#ifndef REQUESTDELEGATE_H
#define REQUESTDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include "../requests/radiostation.h"
#include "datasource/datasource.h"

class RadioStationDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit RadioStationDelegate(QWidget *parent = nullptr);


    void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //catch mouse clicks to add or remove favorites
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

signals:
    //change type of star to show whether it is a favorite or not
    void starClicked(int delegatePosition, bool favorite);
    void starClickedMouse(int delegatePosition, bool favorite, int yMousePosition);

    void currentIndexChanged(int index);
    void doubleClickPressed();

public slots:
};

#endif // REQUESTDELEGATE_H

#ifndef REQUESTDELEGATE_H
#define REQUESTDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QStyledItemDelegate>
#include <QPainter>


class RequestDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit RequestDelegate(QWidget *parent = nullptr);


   void paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:

public slots:
};

#endif // REQUESTDELEGATE_H

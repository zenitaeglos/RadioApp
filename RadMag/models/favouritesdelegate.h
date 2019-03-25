#ifndef FAVOURITESDELEGATE_H
#define FAVOURITESDELEGATE_H

#include <QObject>
#include <QWidget>
#include <QStyledItemDelegate>

class FavouritesDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FavouritesDelegate(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // FAVOURITESDELEGATE_H

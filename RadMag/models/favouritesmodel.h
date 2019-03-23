#ifndef FAVOURITESMODEL_H
#define FAVOURITESMODEL_H

#include <QObject>
#include <QAbstractTableModel>

class FavouritesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FavouritesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

signals:

public slots:
};

#endif // FAVOURITESMODEL_H

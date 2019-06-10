#ifndef FAVOURITESMODEL_H
#define FAVOURITESMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "requests/radiostation.h"

class FavouritesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FavouritesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    void setFavourites(QList<RadioStation*> favList);
    void addFavourite(int position, RadioStation* newFavourite);
    void removeFavourite(int position);

    RadioStation* dataInstance(int row);

private:
    QList<RadioStation*> favouritesList;
};

#endif // FAVOURITESMODEL_H

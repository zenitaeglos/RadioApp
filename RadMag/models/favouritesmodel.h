#ifndef FAVOURITESMODEL_H
#define FAVOURITESMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "requests/requestsdata.h"

class FavouritesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FavouritesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    void setFavourites(QList<RequestsData*> favList);
    void addFavourite(int position, RequestsData* newFavourite);
    void removeFavourite(int position);


private:
    QList<RequestsData*> favouritesList;
};

#endif // FAVOURITESMODEL_H

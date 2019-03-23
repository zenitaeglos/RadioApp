#include "favouritesmodel.h"

FavouritesModel::FavouritesModel(QObject *parent) : QAbstractTableModel (parent)
{

}

int FavouritesModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int FavouritesModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant FavouritesModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant FavouritesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return "Playlists";
        }
    }
    return QVariant();
}

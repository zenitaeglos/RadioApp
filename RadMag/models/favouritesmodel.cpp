#include "favouritesmodel.h"

FavouritesModel::FavouritesModel(QObject *parent) : QAbstractTableModel (parent)
{

}

int FavouritesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return favouritesList.size();
}

int FavouritesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant FavouritesModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return favouritesList.at(index.row())->getObject();
    }
    return QVariant();
}

QVariant FavouritesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return tr("Favorites");
        }
    }
    return QVariant();
}

void FavouritesModel::setFavourites(QList<RadioStation *> favList)
{
    beginResetModel();
    favouritesList = favList;
    endResetModel();
}

void FavouritesModel::addFavourite(int position, RadioStation *newFavourite)
{
    beginInsertRows(QModelIndex(), position, position);
    favouritesList.insert(position, newFavourite);
    endInsertRows();
}

void FavouritesModel::removeFavourite(int position)
{
    beginRemoveRows(QModelIndex(), position, position);
    favouritesList.removeAt(position);
    endRemoveRows();
}

RadioStation *FavouritesModel::dataInstance(int row)
{
    return favouritesList.at(row);
}


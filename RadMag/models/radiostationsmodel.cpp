#include "radiostationsmodel.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QSize>

RadioStationsModel::RadioStationsModel(QObject *parent) : QAbstractTableModel (parent)
{

}

int RadioStationsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return radioStations.size();
}

int RadioStationsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant RadioStationsModel::data(const QModelIndex &index, int role) const
{
    if (radioStations.size() == 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return radioStations.at(index.row())->getObject();
    }
    return QVariant();
}

QVariant RadioStationsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal)
            return "Radios";
    }

    else if (role == Qt::SizeHintRole) {
        if (orientation == Qt::Horizontal) {
            QSize size(0, 40);
            switch (section) {
            case 0:
                size.setWidth(300);
                return QVariant(size);
            case 1:
                size.setWidth(10);
                return QVariant(size);
            default:
                return QVariant(size);
            }

        }
    }

    return QVariant();
}

void RadioStationsModel::setRequestedData(QList<RadioStation *> newRequest)
{
    beginResetModel();
    radioStations = newRequest;
    endResetModel();
}

RadioStation *RadioStationsModel::dataInstance(int row)
{
    return radioStations.at(row);
}

void RadioStationsModel::updateModelFavorite(int position, bool favorite)
{
    RadioStation* radio = dataInstance(position);
    radio->setFavorite(favorite);
    QModelIndex index = createIndex(position, 0);
    emit dataChanged(index, index);
}



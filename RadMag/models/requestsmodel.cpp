#include "requestsmodel.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QSize>

RequestsModel::RequestsModel(QObject *parent) : QAbstractTableModel (parent)
{

}

int RequestsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return requestsData.size();
}

int RequestsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant RequestsModel::data(const QModelIndex &index, int role) const
{
    if (requestsData.size() == 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return requestsData.at(index.row())->getObject();
    }
    return QVariant();
}

QVariant RequestsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal)
            switch (section) {
                case 0:
                    return "Radios";
                case 1:
                    return  "Favorite";
                default:
                    return "";
            }
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

void RequestsModel::setRequestedData(QList<RequestsData *> newRequest)
{
    beginResetModel();
    requestsData = newRequest;
    endResetModel();
}

RequestsData *RequestsModel::dataInstance(int row)
{
    return requestsData.at(row);
}

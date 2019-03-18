#include "requestsmodel.h"
#include <QJsonArray>
#include <QJsonObject>

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

        QJsonObject jsonForDelegate;
        jsonForDelegate["name"] = requestsData.at(index.row())->getName();
        jsonForDelegate["biterate"] = requestsData.at(index.row())->getBitrate();
        jsonForDelegate["country"] = requestsData.at(index.row())->getCountry();
        return jsonForDelegate;
    }
    return QVariant();
}

QVariant RequestsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal)
            return "Radios";
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

#include "requestsmodel.h"

requestsmodel::requestsmodel(QObject *parent) : QAbstractTableModel (parent)
{

}

int requestsmodel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return requestsData.size();
}

int requestsmodel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant requestsmodel::data(const QModelIndex &index, int role) const
{
    if (requestsData.size() == 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return requestsData.at(index.row())->getName();
    }
    return QVariant();
}

void requestsmodel::setRequestedData(QList<RequestsData *> newRequest)
{
    beginResetModel();
    requestsData = newRequest;
    endResetModel();
}

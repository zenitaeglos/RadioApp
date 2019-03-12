#ifndef REQUESTSMODEL_H
#define REQUESTSMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "requests/requestsdata.h"

class requestsmodel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit requestsmodel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //set our own custom data for this table model
    void setRequestedData(QList<RequestsData*> newRequest);


private:
    QList<RequestsData*> requestsData;
};

#endif // REQUESTSMODEL_H

#ifndef RADIOSTATIONSMODEL_H
#define RADIOSTATIONSMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QMap>
#include "requests/radiostation.h"

class RadioStationsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RadioStationsModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //set our own custom data for this table model
    void setRequestedData(QList<RadioStation*> newRequest);

    RadioStation* dataInstance(int row);
private:
    QList<RadioStation*> radioStations;
};

#endif // RADIOSTATIONSMODEL_H

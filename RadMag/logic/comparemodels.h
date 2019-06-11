#ifndef COMPAREMODELS_H
#define COMPAREMODELS_H

#include <QObject>
#include <QDebug>
#include <QAbstractTableModel>
#include "../requests/radiostation.h"
#include "../models/favouritesmodel.h"
#include "../models/radiostationsmodel.h"

class CompareModels
{
public:
    CompareModels();

    bool static findRadioStationInModel(RadioStation* radioStation, QAbstractTableModel* model);
    int static removeRadioFromModel(RadioStation* radioStation, FavouritesModel* model);
};

#endif // COMPAREMODELS_H

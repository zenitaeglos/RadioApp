#ifndef COMPAREMODELS_H
#define COMPAREMODELS_H

#include <QObject>
#include <QDebug>
#include "../requests/radiostation.h"
#include "../models/favouritesmodel.h"

class CompareModels
{
public:
    CompareModels();

    bool static findRadioStationInModel(RadioStation* radioStation, FavouritesModel* model);
    int static removeRadioFromModel(RadioStation* radioStation, FavouritesModel* model);
};

#endif // COMPAREMODELS_H

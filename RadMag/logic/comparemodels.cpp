#include "comparemodels.h"

CompareModels::CompareModels()
{

}

bool CompareModels::findRadioStationInModel(RadioStation *radioStation, FavouritesModel *model)
{
    bool isAdded = false;
    for (int i = 0; i < model->rowCount(QModelIndex()); i++) {
        RadioStation* favRadioStation = model->dataInstance(i);
        if (radioStation->getValue(RadioStation::Url) == favRadioStation->getValue(RadioStation::Url)) {
            isAdded = true;
            break;
        }
    }
    return isAdded;
}

void CompareModels::removeRadioFromModel(RadioStation *radioStation, FavouritesModel *model)
{
    for (int i = 0; i < model->rowCount(QModelIndex()); i++) {
        RadioStation* radioFavorite = model->dataInstance(i);
        if (radioStation->getValue(RadioStation::Url) == radioFavorite->getValue(RadioStation::Url)) {
            model->removeFavourite(i);
            break;
        }
    }
}

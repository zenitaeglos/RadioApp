#include "comparemodels.h"

CompareModels::CompareModels()
{

}

bool CompareModels::findRadioStationInModel(RadioStation *radioStation, QAbstractTableModel *model)
{
    FavouritesModel* favModel = dynamic_cast<FavouritesModel*>(model);
    RadioStationsModel* radioModel = dynamic_cast<RadioStationsModel*>(model);
    bool isAdded = false;
    for (int i = 0; i < model->rowCount(QModelIndex()); i++) {
        RadioStation* favRadioStation = nullptr;
        if (favModel)
            favRadioStation = favModel->dataInstance(i);
        else if (radioModel)
            favRadioStation = radioModel->dataInstance(i);

        if (radioStation->getValue(RadioStation::Url) == favRadioStation->getValue(RadioStation::Url)) {
            isAdded = true;
            break;
        }
    }
    return isAdded;
}

int CompareModels::removeRadioFromModel(RadioStation *radioStation, FavouritesModel *model)
{
    for (int i = 0; i < model->rowCount(QModelIndex()); i++) {
        RadioStation* radioFavorite = model->dataInstance(i);
        if (radioStation->getValue(RadioStation::Url) == radioFavorite->getValue(RadioStation::Url)) {
            model->removeFavourite(i);
            return i;
        }
    }
    return -1;
}

#include "comparemodels.h"

CompareModels::CompareModels()
{

}

int CompareModels::findRadioStationInModel(RadioStation *radioStation, QAbstractTableModel *model)
{
    int position = -1;
    FavouritesModel* favModel = dynamic_cast<FavouritesModel*>(model);
    RadioStationsModel* radioModel = dynamic_cast<RadioStationsModel*>(model);

    for (int i = 0; i < model->rowCount(QModelIndex()); i++) {
        RadioStation* favRadioStation = nullptr;
        if (favModel)
            favRadioStation = favModel->dataInstance(i);
        else if (radioModel)
            favRadioStation = radioModel->dataInstance(i);

        if (radioStation->getValue(RadioStation::Url) == favRadioStation->getValue(RadioStation::Url)) {
            position = i;
            break;
        }
    }
    return position;
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

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

        if (radioStation->getValue(RadioStation::StationuuID) == favRadioStation->getValue(RadioStation::StationuuID)) {
            position = i;
            break;
        }
    }
    return position;
}

int CompareModels::removeRadioFromModel(RadioStation *radioStation, FavouritesModel *model)
{
    int position = findRadioStationInModel(radioStation, model);
    if (position > -1)
        model->removeFavourite(position);
    return position;
}

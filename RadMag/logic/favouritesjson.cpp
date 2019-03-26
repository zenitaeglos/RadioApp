#include "favouritesjson.h"
#include <QDebug>

FavouritesJson::FavouritesJson()
{
    jsonFile.setFileName("favourites.json");
}

QList<RequestsData *> FavouritesJson::jsonLoadElements()
{
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        return QList<RequestsData*>();
    }
    QByteArray data = jsonFile.readAll();

    QJsonDocument document = QJsonDocument::fromJson(data);
    QList<RequestsData*> dataForModel;

    QJsonArray array = document.array();


    //add link to access the webpage

    for (int i = 0; i < array.size(); i++) {
        RequestsData* data = new RequestsData(array.at(i).toObject());
        dataForModel.append(data);
    }

    jsonFile.close();
    return dataForModel;
}

void FavouritesJson::addJsonObjectToFile(QJsonObject jsonObject, int position)
{
    if (jsonFile.open(QIODevice::ReadWrite)) {
        QByteArray data = jsonFile.readAll();
        if (data.size() == 0) {
            QJsonDocument document;
            QJsonArray array;
            array.append(jsonObject);
            document.setArray(array);
            jsonFile.write(document.toJson(QJsonDocument::Indented));
        }
        else {
            QJsonDocument document = QJsonDocument::fromJson(data);
            QJsonArray array;
            array = document.array();
            array.insert(position, jsonObject);
            document.setArray(array);
            jsonFile.resize(0);

            jsonFile.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
        }
    }
    jsonFile.close();
}

void FavouritesJson::removeJsonObjectFromFile(int position)
{
    if (jsonFile.open(QIODevice::ReadWrite)) {
        QByteArray data = jsonFile.readAll();
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonArray array = document.array();
        array.removeAt(position);

        jsonFile.resize(0);
        jsonFile.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
    }

    jsonFile.close();
}



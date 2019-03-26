#ifndef FAVOURITESJSON_H
#define FAVOURITESJSON_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <requests/requestsdata.h>

class FavouritesJson
{

public:
    explicit FavouritesJson();

    QList<RequestsData*> jsonLoadElements();
    void addJsonObjectToFile(QJsonObject jsonObject, int position);
    void removeJsonObjectFromFile(int position);



private:
    QFile jsonFile;


};

#endif // FAVOURITESJSON_H

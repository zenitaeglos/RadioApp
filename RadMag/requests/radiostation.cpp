#include "radiostation.h"
#include <QDebug>

RadioStation::RadioStation(QJsonObject jsonObject, bool favorite /*false*/) :
    jsonObject(jsonObject)
{
    //add new key and value with favorite element
    jsonObject.insert("favorite", favorite);
}

QJsonObject RadioStation::getObject() const
{
    return jsonObject;
}

QString RadioStation::getValue(RadioStation::ObjectKeys key) const
{
    return jsonObject[getType(key)].toString();
}

QString RadioStation::getType(RadioStation::ObjectKeys key)
{
    switch (key) {
        case Name:
            return "name";
        case Url:
            return "url";
        case Bitrate:
            return "bitrate";
        case Country:
            return "country";
        case IsFavorite:
            return "favorite";
        case StationuuID:
            return "stationuuid";
    }
}

void RadioStation::setFavorite(bool favorite)
{
    jsonObject["favorite"] = favorite;
}

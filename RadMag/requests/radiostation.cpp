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
    switch (key) {
    case Name:
        return jsonObject["name"].toString();
    case Url:
        return jsonObject["url"].toString();
    case Bitrate:
        return jsonObject["bitrate"].toString();
    case Country:
        return jsonObject["country"].toString();
    case IsFavorite:
        return jsonObject["favorite"].toString();
    }
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
    }
}

void RadioStation::setFavorite(bool favorite)
{
    jsonObject["favorite"] = favorite;
}

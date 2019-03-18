#include "requestsdata.h"


RequestsData::RequestsData(QJsonObject jsonObject) :
    jsonObject(jsonObject)
{

}

QJsonObject RequestsData::getObject() const
{
    return jsonObject;
}

QString RequestsData::getValue(RequestsData::ObjectKeys key)
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
    }
}

#include "requestsdata.h"

RequestsData::RequestsData()
{

}

QString RequestsData::getName() const
{
    return name;
}

QString RequestsData::getUrl() const
{
    return urlName;
}

QString RequestsData::getBitrate() const
{
    return bitrate;
}

QString RequestsData::getCountry() const
{
    return country;
}

void RequestsData::setName(const QString &newName)
{
    name = newName;
}

void RequestsData::setUrlName(const QString &newUrlName)
{
    urlName = newUrlName;
}

void RequestsData::setBitrate(const QString &newBitrate)
{
    bitrate = newBitrate;
}

void RequestsData::setCountry(const QString &newCountry)
{
    country = newCountry;
}

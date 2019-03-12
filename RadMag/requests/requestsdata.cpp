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

void RequestsData::setName(const QString &newName)
{
    name = newName;
}

void RequestsData::setUrlName(const QString &newUrlName)
{
    urlName = newUrlName;
}

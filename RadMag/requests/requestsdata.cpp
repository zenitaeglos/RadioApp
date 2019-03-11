#include "requestsdata.h"

RequestsData::RequestsData(QObject *parent) : QObject(parent)
{

}

QString RequestsData::getName() const
{
    return name;
}

void RequestsData::setName(const QString &newName)
{
    name = newName;
}

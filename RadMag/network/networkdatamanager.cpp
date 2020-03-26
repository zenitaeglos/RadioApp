#include "networkdatamanager.h"

NetworkDataManager::NetworkDataManager(QObject *parent) : QObject(parent),
    delegate(nullptr),
    manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkDataManager::replyDataFromNetwork);
}

void NetworkDataManager::fetchData(QString urlString) const
{
    manager->get(QNetworkRequest(QUrl(urlString)));
}

void NetworkDataManager::setDelegate(NetworkDelegate *newDelegate)
{
    delegate = newDelegate;
}

void NetworkDataManager::replyDataFromNetwork(QNetworkReply *networkReply)
{
    QByteArray byteArray = networkReply->readAll();

    if (byteArray.isEmpty())
        delegate->didNotReceiveData("The server might have problems and no connection was possible");
    else if (byteArray == "[]")
        delegate->didNotReceiveData("There is no result for this search");
    else
        delegate->didReceiveData(byteArray);
}

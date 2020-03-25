#ifndef NETWORKDATAMANAGER_H
#define NETWORKDATAMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "networkdelegate.h"

class NetworkDataManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkDataManager(QObject *parent = nullptr);

    void fetchData(QString urlString) const;
    void setDelegate(NetworkDelegate* newDelegate);

signals:

public slots:
    void replyDataFromNetwork(QNetworkReply* networkReply);

private:
    NetworkDelegate* delegate;
    QNetworkAccessManager* manager;

};

#endif // NETWORKDATAMANAGER_H

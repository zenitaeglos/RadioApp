#ifndef REQUESTSDATA_H
#define REQUESTSDATA_H

#include <QObject>
#include <QJsonObject>

class RequestsData
{

public:
    enum ObjectKeys {
        Name,
        Url,
        Bitrate,
        Country
    };
    explicit RequestsData(QJsonObject jsonObject);

    //getters
    QJsonObject getObject() const;
    QString getValue(ObjectKeys key);



private:
    QJsonObject jsonObject;
};

#endif // REQUESTSDATA_H

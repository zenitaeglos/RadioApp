#ifndef REQUESTSDATA_H
#define REQUESTSDATA_H

#include <QObject>

class RequestsData
{

public:
    explicit RequestsData();

    //getters
    QString getName() const;
    QString getUrl() const;
    QString getBitrate() const;
    QString getCountry() const;
    //setters
    void setName(const QString &newName);
    void setUrlName(const QString &newUrlName);
    void setBitrate(const QString &newBitrate);
    void setCountry(const QString &newCountry);


private:
    QString name;
    QString urlName;
    QString bitrate;
    QString country;
};

#endif // REQUESTSDATA_H

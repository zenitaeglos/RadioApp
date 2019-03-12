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
    //setters
    void setName(const QString &newName);
    void setUrlName(const QString &newUrlName);

private:
    QString name;
    QString urlName;
};

#endif // REQUESTSDATA_H

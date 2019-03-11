#ifndef REQUESTSDATA_H
#define REQUESTSDATA_H

#include <QObject>

class RequestsData : public QObject
{
    Q_OBJECT
public:
    explicit RequestsData(QObject *parent = nullptr);

    QString getName() const;

    void setName(const QString &newName);

private:
    QString name;
};

#endif // REQUESTSDATA_H

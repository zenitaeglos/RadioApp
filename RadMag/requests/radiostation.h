#ifndef RADIOSTATION_H
#define RADIOSTATION_H

#include <QObject>
#include <QJsonObject>

class RadioStation
{

public:
    enum ObjectKeys {
        Name,
        Url,
        Bitrate,
        Country,
        IsFavorite,
        StationuuID,
        Favicon
    };
    explicit RadioStation(QJsonObject jsonObject, bool favorite = false);

    //getters
    QJsonObject getObject() const;
    QString getValue(ObjectKeys key) const;
    QString static getType(ObjectKeys key);

    //setter
    void setFavorite(bool favorite);



private:
    QJsonObject jsonObject;
};

#endif // RADIOSTATION_H

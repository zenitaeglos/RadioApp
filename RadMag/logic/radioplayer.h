#ifndef RADIOPLAYER_H
#define RADIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QUrl>
#include "../notifications/popupnotifications.h"

/*!
 * \brief The RadioPlayer class
 * \class RadioPlayer: QObject
 * \title RadioPlayer with metadata and playlists information
*/


class RadioPlayer : public QObject
{
    Q_OBJECT

public:
    explicit RadioPlayer();
    ~RadioPlayer();
    void play();
    void stop();

    void addMedia(QUrl newMedia);
    void addMedia(QByteArray data);
    void setVolume(int value);
    void clearPlayList();
    QMediaPlayer* player() const;

private slots:
    void fireMediaStatusChanged();

signals:
    void mediaStatusChanged(QString title);

private:
    QMediaPlayer* mediaPlayer;
    QMediaPlaylist* mediaPlayList;


};

#endif // RADIOPLAYER_H

#ifndef RADIOPLAYER_H
#define RADIOPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QUrl>


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

signals:
void mediaStatusChanged(QString title);

private slots:
    void fireMediaStatusChanged();

private:
    QMediaPlayer* mediaPlayer;
    QMediaPlaylist* mediaPlayList;


};

#endif // RADIOPLAYER_H

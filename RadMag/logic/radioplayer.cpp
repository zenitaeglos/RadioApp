#include "radioplayer.h"

RadioPlayer::RadioPlayer() :
    mediaPlayer(new QMediaPlayer()),
    mediaPlayList(new QMediaPlaylist())
{
    mediaPlayer->setPlaylist(mediaPlayList);
}

RadioPlayer::~RadioPlayer()
{
    delete mediaPlayer;
    delete mediaPlayList;
}

void RadioPlayer::play()
{
    mediaPlayer->play();
}

void RadioPlayer::stop()
{
    mediaPlayer->stop();
}

void RadioPlayer::addMedia(QUrl newMedia)
{
    mediaPlayList->addMedia(newMedia);
}

void RadioPlayer::addMedia(QByteArray data)
{
    QList<QByteArray> listByte = data.split('\n');
    for (QByteArray byteArray : listByte) {
        mediaPlayList->addMedia(QUrl(byteArray));
    }
}

void RadioPlayer::setVolume(int value)
{
    mediaPlayer->setVolume(value);
}

void RadioPlayer::clearPlayList()
{
    mediaPlayList->clear();
}

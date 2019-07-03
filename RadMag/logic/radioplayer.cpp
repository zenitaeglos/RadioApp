#include "radioplayer.h"

RadioPlayer::RadioPlayer() :
    mediaPlayer(new QMediaPlayer()),
    mediaPlayList(new QMediaPlaylist())
{
    mediaPlayer->setPlaylist(mediaPlayList);
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &RadioPlayer::fireMediaStatusChanged);
    connect(mediaPlayer, SIGNAL(metaDataChanged()), this, (SLOT(fireMediaStatusChanged())));
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

QMediaPlayer *RadioPlayer::player() const
{
    return  mediaPlayer;
}

void RadioPlayer::fireMediaStatusChanged()
{
    qDebug() << mediaPlayer->isMetaDataAvailable();
    qDebug() << mediaPlayer->metaData(QMediaMetaData::Title).toString();
    QString mediaInfo = QString();
    if (mediaPlayer->metaData(QMediaMetaData::Title).toString().size() > 0)
        PopUpNotifications::showPopUpNotification(mediaPlayer->metaData((QMediaMetaData::Publisher)).toString(),
                                              mediaPlayer->metaData(QMediaMetaData::Title).toString());
    mediaInfo.append("<b>" + mediaPlayer->metaData(QMediaMetaData::Publisher).toString() + "</b><br/>");
    mediaInfo.append(mediaPlayer->metaData(QMediaMetaData::Title).toString() + "<br/>");
    emit mediaStatusChanged(mediaInfo);
}

#ifndef POPUPNOTIFICATIONS_H
#define POPUPNOTIFICATIONS_H

#include <QObject>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>

class PopUpNotifications
{
public:
    PopUpNotifications();

    static void showPopUpNotification(QString titleNotification, QString textNotification);

    //static variables for title and body for notification
    static QString titleNotification;
    static QString textNotification;
};

#endif // POPUPNOTIFICATIONS_H

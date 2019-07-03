#ifndef POPUPNOTIFICATIONS_H
#define POPUPNOTIFICATIONS_H

#include <QObject>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>

class PopUpNotifications
{
public:
    PopUpNotifications();

    static void showPopUpNotification(QString title, QString text);
};

#endif // POPUPNOTIFICATIONS_H

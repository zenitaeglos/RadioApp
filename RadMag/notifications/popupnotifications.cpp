#include "popupnotifications.h"

QString PopUpNotifications::titleNotification = "";
QString PopUpNotifications::textNotification = "";

PopUpNotifications::PopUpNotifications()
{

}

void PopUpNotifications::showPopUpNotification(QString title, QString text)
{
    if (text != textNotification && title.size() > 0) {
        titleNotification = title;
        textNotification = text;
        QDBusConnection bus = QDBusConnection::sessionBus();
        QDBusInterface interNot("org.freedesktop.Notifications",
                                "/org/freedesktop/Notifications",
                                "org.freedesktop.Notifications", bus);
        if (interNot.isValid()) {
            QStringList stringList;
            QVariantMap variantMap;
            QDBusMessage ms = interNot.call("Notify", "test app", uint(0),
                                            "/usr/share/icons/gnome/256x256/apps/radiow48.png",
                                            title, text, stringList,
                variantMap, 5000);
        }
    }

}

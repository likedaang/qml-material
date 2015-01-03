#include "qmldesktop_plugin.h"
#include "mprisconnection.h"
#include "notification.h"
#include "notificationserver.h"
#include "mpris2player.h"

#include <qqml.h>

void DesktopPlugin::registerTypes(const char *uri)
{
    // @uri Material.Desktop
    qmlRegisterType<MprisConnection>(uri, 0, 1, "MprisConnection");
    qmlRegisterType<NotificationServer>(uri, 0, 1, "NotificationServer");
    qmlRegisterUncreatableType<Mpris2Player>(uri, 0, 1, "Mpris2Player", "Player class");
    qmlRegisterUncreatableType<Notification>(uri, 0, 1, "Notifiation", "For NotificationServer");
}



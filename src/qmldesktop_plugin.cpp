#include "qmldesktop_plugin.h"
#include "mprisconnection.h"
#include "notification.h"
#include "notificationserver.h"
#include "upowerconnection.h"
#include "upowerdevicetype.h"
#include "upowerdevicestate.h"
#include "upowerdevice.h"
#include "mpris2player.h"

#include <qqml.h>

void DesktopPlugin::registerTypes(const char *uri)
{
    // @uri Material.Desktop
    qmlRegisterType<MprisConnection>(uri, 0, 1, "MprisConnection");
    qmlRegisterType<NotificationServer>(uri, 0, 1, "NotificationServer");
    qmlRegisterType<UPowerConnection>(uri, 0, 1, "UPowerConnection");
    qmlRegisterUncreatableType<Mpris2Player>(uri, 0, 1, "Mpris2Player", "Player class");
    qmlRegisterUncreatableType<Notification>(uri, 0, 1, "Notification", "For NotificationServer");
    qmlRegisterUncreatableType<UPowerDevice>(uri, 0, 1, "UPowerDevice", "For UPower");
    qmlRegisterUncreatableType<UPowerDeviceType>(uri, 0, 1, "UPowerDeviceType", "Enum class for type");
    qmlRegisterUncreatableType<UPowerDeviceState>(uri, 0, 1, "UPowerDeviceState", "Enum class for state");
}



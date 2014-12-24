#include "qmldesktop_plugin.h"
#include "mprisconnection.h"
#include "mpris2player.h"

#include <qqml.h>

void DesktopPlugin::registerTypes(const char *uri)
{
    // @uri Material.Desktop
    qmlRegisterType<MprisConnection>(uri, 0, 1, "MprisConnection");
    qmlRegisterUncreatableType<Mpris2Player>(uri, 0, 1, "Mpris2Player", "Player class");
}



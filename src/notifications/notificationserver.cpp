#include "notificationserver.h"
#include "notificationadaptor.h"

NotificationServer::NotificationServer(QQuickItem *parent) : QQuickItem(parent) {
    adaptor = new NotificationAdaptor(parent, this);
    QDBusConnection::sessionBus().registerObject("/org/freedesktop/Notifications", parent);
    QDBusConnection::sessionBus().registerService("org.freedesktop.Notifications");
}

void NotificationServer::closeNotification(int id) {
    adaptor->closeNotification(id);
}

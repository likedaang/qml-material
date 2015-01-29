#include "notificationserver.h"
#include "notificationadaptor.h"

NotificationServer::NotificationServer(QQuickItem *parent) : QQuickItem(parent) {
    adaptor = new NotificationAdaptor(parent, this);
    qDebug() << "Registering object: " << QDBusConnection::sessionBus().registerObject("/org/freedesktop/Notifications", parent);
    qDebug() << "Registering service: " << QDBusConnection::sessionBus().registerService("org.freedesktop.Notifications");
}

void NotificationServer::closeNotification(int id) {
    adaptor->closeNotification(id);
}

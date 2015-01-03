#ifndef NOTIFICATIONSERVER_H
#define NOTIFICATIONSERVER_H

#include <QQuickItem>
#include <QQmlListProperty>
#include <QList>
#include <QDBusConnection>
#include <QObject>
#include "notification.h"
#include "notificationadaptor.h"

class NotificationServer : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(NotificationServer)
    Q_PROPERTY(QQmlListProperty<Notification> notifications READ notifications NOTIFY notificationsChanged)

public:
    explicit NotificationServer(QQuickItem *parent = new QQuickItem()) : QQuickItem(parent) {
        adaptor = new NotificationAdaptor(parent);
        QDBusConnection::sessionBus().registerObject("/org/freedesktop/Notifications", parent);
        QDBusConnection::sessionBus().registerService("org.freedesktop.Notifications");
        QObject::connect(adaptor, SIGNAL(notificationsChanged()), this, SLOT(emitNotificationsChanged()));
    }
    QQmlListProperty<Notification> notifications() {
        return QQmlListProperty<Notification>(this, adaptor->notifications);
    }
private:
    NotificationAdaptor* adaptor;
private slots:
    void emitNotificationsChanged(){
        emit notificationsChanged();
    }

signals:
    void notificationsChanged();
};

#endif // NOTIFICATIONSERVER_H

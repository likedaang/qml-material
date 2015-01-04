#ifndef NOTIFICATIONSERVER_H
#define NOTIFICATIONSERVER_H

#include <QQuickItem>
#include <QQmlListProperty>
#include <QList>
#include <QDBusConnection>
#include <QObject>
#include "notification.h"

class NotificationAdaptor;

class NotificationServer : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(NotificationServer)

public:
    explicit NotificationServer(QQuickItem *parent = new QQuickItem());

public slots:
    void closeNotification(int id);

private:
    NotificationAdaptor* adaptor;

signals:
    void notificationUpdated(int id, QVariant notification);
    void notificationAdded(int id, QVariant notification);
    void notificationRemoved(int id);
};

#endif // NOTIFICATIONSERVER_H

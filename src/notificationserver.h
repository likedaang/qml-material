/*
 * QML Desktop - Set of tools written in C++ for QML
 * Copyright (C) 2014 Bogdan Cuza <bogdan.cuza@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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

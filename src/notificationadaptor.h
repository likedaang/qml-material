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

#ifndef NOTIFICATIONADAPTOR_H
#define NOTIFICATIONADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QStringList>
#include <QTimer>
#include <QSignalMapper>
#include <QList>
#include "notification.h"

class NotificationAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")
public:
    NotificationAdaptor(QObject *parent) : QDBusAbstractAdaptor(parent), availableId(1) {}
    QList<Notification*> notifications;
public slots:
    QStringList GetCapabilities() {
        return QStringList() << "body";
    }
    void CloseNotification(uint id) {
        for (int i = 0; i < notifications.length(); i++){
            if (notifications[i]->m_id == id) {
                notifications.removeAt(i);
            }
        }
        emit notificationsChanged();
        emit NotificationClosed(id, 3);
    }
    void GetServerInformation(QString &name, QString &vendor, QString &version, QString &spec_version){
        name = "Quantum OS Notification Server";
        vendor = "Quantum OS";
        version = "0.1";
        //not sure, I think so
        spec_version = "1.2";
    }
    uint Notify(QString app_name, uint replaces_id, QString app_icon, QString summary, QString body, QStringList actions, QVariantMap hints, int expire_timeout) {
        Notification *notification = new Notification(app_name, (replaces_id == 0 ? availableId++ : replaces_id), app_icon, summary, body, actions, hints, expire_timeout);
        if (replaces_id != 0) {
            for (int i = 0; i < notifications.length(); i++){
                if (notifications[i]->m_id == replaces_id) {
                    notifications.replace(i, notification);
                    if (expire_timeout != -1 && expire_timeout != 0) {
                        QSignalMapper *mapper = new QSignalMapper(this);
                        QObject::connect(mapper, SIGNAL(mapped(QString)), this, SLOT(forTimer(QString)));
                        QTimer *timer = new QTimer(this);
                        QObject::connect(timer, SIGNAL(timeout()), mapper, SLOT(map()));
                        mapper->setMapping(timer, QVariant(replaces_id).toString());
                        timer->setSingleShot(true);
                        timer->start(expire_timeout);
                    }
                    emit notificationsChanged();
                }
            }
        } else {
            notifications << notification;
            if (expire_timeout != -1 && expire_timeout != 0){
                QSignalMapper *mapper = new QSignalMapper(this);
                QObject::connect(mapper, SIGNAL(mapped(QString)), this, SLOT(forTimer(QString)));
                QTimer *timer = new QTimer(this);
                QObject::connect(timer, SIGNAL(timeout()), mapper, SLOT(map()));
                mapper->setMapping(timer, QVariant(availableId-1).toString());
                timer->setSingleShot(true);
                timer->start(expire_timeout);
            }
            emit notificationsChanged();
        }
        return (replaces_id == 0 ? availableId-1 : replaces_id);
    }
signals:
    void NotificationClosed(uint id, uint reason);
    void ActionInvoked(uint id, QString action_key);
    void notificationsChanged();
private:
    uint availableId;
private slots:
    void forTimer(QString id) {
        for (int i = 0; i < notifications.length(); i++){
            if (notifications[i]->m_id == QVariant(id).toUInt()) {
                notifications.removeAt(i);
                emit NotificationClosed(QVariant(id).toUInt(), 1);
                emit notificationsChanged();
            }
        }
    }
};

#endif // NOTIFICATIONADAPTOR_H

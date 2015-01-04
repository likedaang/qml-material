#ifndef NOTIFICATIONADAPTOR_H
#define NOTIFICATIONADAPTOR_H

#include <QDBusAbstractAdaptor>
#include <QStringList>
#include <QTimer>
#include <QSignalMapper>
#include <QList>
#include "notification.h"
#include <QDebug>
#include <QQmlListProperty>
#include <notificationserver.h>

class NotificationAdaptor : public QDBusAbstractAdaptor
{

    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Notifications")
public:

    enum CloseReason {
        Expired = 1,
        Dismissed = 2,
        Requested = 3,
        Unknown = 4
    };

    NotificationAdaptor(QObject *parent, NotificationServer *server) : QDBusAbstractAdaptor(parent), availableId(1) {
        this->server = server;
        qDebug() << "Adapter ready!";
    }

public slots:
    QStringList GetCapabilities() {
        return QStringList() << "body";
    }
    void CloseNotification(uint id) {
        server->notificationRemoved(id);

        emit NotificationClosed(id, Requested);
    }
    void GetServerInformation(QString &name, QString &vendor, QString &version, QString &spec_version){
        name = "Quantum OS Notification Server";
        vendor = "Quantum OS";
        version = "0.1";
        //not sure, I think so
        spec_version = "1.2";
    }

    uint Notify(QString app_name, uint replaces_id, QString app_icon, QString summary, QString body, QStringList actions, QVariantMap hints, int expire_timeout) {

        qDebug() << "Notification" << app_name << summary << body << replaces_id;

        Notification *notification = new Notification(app_name, (replaces_id == 0 ? availableId++ : replaces_id), app_icon, summary, body, actions, hints, expire_timeout);

        if (expire_timeout == 0) {
            expire_timeout = 2500;
        }

        if (expire_timeout != -1) {
            qDebug() << "Expiring in" << expire_timeout << "milliseconds";

            QSignalMapper *mapper = new QSignalMapper(this);
            QObject::connect(mapper, SIGNAL(mapped(QString)), this, SLOT(forTimer(QString)));
            QTimer *timer = new QTimer(this);
            QObject::connect(timer, SIGNAL(timeout()), mapper, SLOT(map()));
            mapper->setMapping(timer, QVariant(notification->m_id).toString());
            timer->setSingleShot(true);
            timer->start(expire_timeout);
        } else {
            qDebug() << "Notification doesn't time out!";
        }

        if (replaces_id != 0) {
            server->notificationUpdated(replaces_id, QVariant(QMetaType::QObjectStar, &notification));
        } else {
            server->notificationAdded(notification->m_id, QVariant(QMetaType::QObjectStar, &notification));
        }

        return notification->m_id;
    }

    void closeNotification(int id) {
        server->notificationRemoved(id);
        emit NotificationClosed(id, Dismissed);
    }

signals:
    void NotificationClosed(uint id, uint reason);
    void ActionInvoked(uint id, QString action_key);

private slots:

    void forTimer(QString id) {
        server->notificationRemoved(id.toInt());
        emit NotificationClosed(QVariant(id).toUInt(), Expired);
    }

private:

    uint availableId;
    NotificationServer *server;
};

#endif // NOTIFICATIONADAPTOR_H

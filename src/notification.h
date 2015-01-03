#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include <QStringList>
#include <QVariantMap>

class Notification : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appName MEMBER m_app_name)
    Q_PROPERTY(uint id MEMBER m_id)
    Q_PROPERTY(QString appIcon MEMBER m_app_icon)
    Q_PROPERTY(QString summary MEMBER m_summary)
    Q_PROPERTY(QString body MEMBER m_body)
    Q_PROPERTY(QStringList actions MEMBER m_actions)
    Q_PROPERTY(QVariantMap hints MEMBER m_hints)
    Q_PROPERTY(int expireTimeout MEMBER m_expire_timeout)
    Q_ENUMS(Urgency)
public:
    enum Urgency {
        Low, Normal, Critical
    };
    explicit Notification(QString &app_name, uint id, QString &app_icon, QString &summary, QString &body, QStringList actions, QVariantMap &hints, int &expire_timeout, QObject *parent = 0) : QObject(parent){
        m_app_name = app_name;
        m_id = id;
        m_app_icon = app_icon;
        m_summary = summary;
        m_body = body;
        m_actions = actions;
        m_hints = hints;
        m_expire_timeout = expire_timeout;
    }
    QString m_app_name;
    uint m_id;
    QString m_app_icon;
    QString m_summary;
    QString m_body;
    QStringList m_actions;
    QVariantMap m_hints;
    int m_expire_timeout;
};

#endif // NOTIFICATION_H

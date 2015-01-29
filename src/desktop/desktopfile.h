#ifndef DESKTOPFILE_H
#define DESKTOPFILE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QSettings>

class DesktopFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(QVariant icon MEMBER m_icon)
    Q_PROPERTY(QString exec MEMBER m_exec)
    Q_PROPERTY(QVariant darkColor MEMBER m_darkColor)
    Q_PROPERTY(QString location MEMBER m_location WRITE setLocation NOTIFY locationChanged)
public:
    explicit DesktopFile(QString location = "", QObject *parent = 0);
    static QString locationFromFile(QString desktopName);
    static QString getEnvVar(int pid);
    void setLocation(QString location);

    QString m_name;
    QVariant m_icon;
    QString m_exec;
    QString m_location;
    QVariant m_darkColor;

signals:
    void locationChanged();

private:
    void processLocation(const QString &location);
};

#endif // DESKTOPFILE_H

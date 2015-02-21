/* 
 * QML Desktop - Set of tools written in C++ for QML
 * 
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

#ifndef DESKTOPFILE_H
#define DESKTOPFILE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QLocale>

class DesktopFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(QVariant localizedName MEMBER m_localizedName)
    Q_PROPERTY(QVariant icon MEMBER m_icon)
    Q_PROPERTY(QVariant comment MEMBER m_comment)
    Q_PROPERTY(QString exec MEMBER m_exec)
    Q_PROPERTY(QVariant darkColor MEMBER m_darkColor)
    Q_PROPERTY(QVariant localizedComment MEMBER m_localizedComment)
    Q_PROPERTY(QString location MEMBER m_location WRITE setLocation NOTIFY locationChanged)
public:
    explicit DesktopFile(QString location = "", QObject *parent = 0);
    static QString locationFromFile(QString desktopName);
    static QString getEnvVar(int pid);
    void setLocation(QString location);

    QString m_name;
    QVariant m_localizedName;
    QVariant m_icon;
    QString m_exec;
    QString m_location;
    QVariant m_darkColor;
    QVariant m_comment;
    QVariant m_localizedComment;

signals:
    void locationChanged();

private:
    void processLocation(const QString &location);
};

#endif // DESKTOPFILE_H

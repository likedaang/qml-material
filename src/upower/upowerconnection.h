/*
 * QML Desktop - Set of tools written in C++ for QML
 * 
 * Copyright (C) 2014 Bogdan Cuza <bogdan.cuza@hotmail.com>
 *               2015 Michael Spencer <sonrisesoftware@gmail.com>
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

#ifndef UPOWERCONNECTION
#define UPOWERCONNECTION

#include <QQuickItem>
#include <QDBusInterface>
#include <QQmlListProperty>
#include <QDBusArgument>
#include "upowerdevice.h"

class UPowerConnection : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<UPowerDevice> devices READ devices NOTIFY devicesChanged)

public:
    explicit UPowerConnection(QQuickItem *parent = 0);

    QQmlListProperty<UPowerDevice> devices() {
        return QQmlListProperty<UPowerDevice>(this, deviceList);
    }

signals:
    void devicesChanged();

private slots:
   void reloadDevices();

private:
   QDBusInterface iface;
   QList<UPowerDevice*> deviceList;
};

#endif // UPOWERCONNECTION

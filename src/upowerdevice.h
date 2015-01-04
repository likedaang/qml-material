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

#ifndef UPOWERDEVICE
#define UPOWERDEVICE

#include <QObject>
#include <QDBusInterface>
#include "upowerdevicetype.h"

class UPowerDevice : public QObject
{
    Q_OBJECT
    //we're using variants not because I am lazy, but because they will return an undefined and it will be idiomatic JavaScript :D
    Q_PROPERTY(UPowerDeviceType::Type type MEMBER m_type)
    Q_PROPERTY(bool powerSupply MEMBER m_powerSupply)
    Q_PROPERTY(QVariant online MEMBER m_online)
    Q_PROPERTY(QVariant energy MEMBER m_energy NOTIFY changed)
    Q_PROPERTY(QVariant energyFull MEMBER m_energyFull)
    Q_PROPERTY(QVariant energyEmpty MEMBER m_energyEmpty)
    Q_PROPERTY(double voltage MEMBER m_voltage NOTIFY changed)
    Q_PROPERTY(QVariant energyRate MEMBER m_energyRate NOTIFY changed)
    Q_PROPERTY(QVariant timeToEmpty MEMBER m_timeToEmpty NOTIFY changed)
    Q_PROPERTY(QVariant timeToFull MEMBER m_timeToFull NOTIFY changed)
    Q_PROPERTY(QVariant percentage MEMBER m_percentage NOTIFY changed)
    Q_PROPERTY(QVariant state MEMBER m_state NOTIFY changed)
    Q_PROPERTY(QVariant isRechargeable MEMBER m_isRechargeable)
    Q_PROPERTY(QVariant capacity MEMBER m_capacity)

public:
    explicit UPowerDevice(QString path, QObject *parent = 0) : QObject(parent), iface("org.freedesktop.UPower", path, "org.freedesktop.UPower.Device", QDBusConnection::systemBus()){
        QDBusConnection::systemBus().connect(iface.service(), iface.path(), iface.interface(), "Changed", this, SIGNAL(changed()));
        m_type = static_cast<UPowerDeviceType::Type>(iface.property("Type").toInt());
        if (m_type == UPowerDeviceType::LinePower) {
            m_online = iface.property("Online");
        }
        if (m_type == UPowerDeviceType::Battery) {
            m_energy = iface.property("Energy");
            m_energyFull = iface.property("EnergyFull");
            m_energyEmpty = iface.property("EnergyEmpty");
            m_energyRate = iface.property("EnergyRate");
            m_timeToEmpty = iface.property("TimeToEmpty");
            m_timeToFull = iface.property("TimeToFull");
            m_percentage = iface.property("Percentage");
            m_state = iface.property("State");
            m_isRechargeable = iface.property("IsRechargeable");
            m_capacity = iface.property("Capacity");
        }
        m_voltage = iface.property("Voltage").toBool();
        m_powerSupply = iface.property("PowerSupply").toBool();
    }

    UPowerDeviceType::Type m_type;
    bool m_powerSupply;
    QVariant m_online;
    QVariant m_energy;
    QVariant m_energyEmpty;
    QVariant m_energyFull;
    double m_voltage;
    QVariant m_energyRate;
    QVariant m_timeToEmpty;
    QVariant m_timeToFull;
    QVariant m_percentage;
    QVariant m_state;
    QVariant m_isRechargeable;
    QVariant m_capacity;
signals:
    void changed();
private:
    QDBusInterface iface;
};

#endif // UPOWERDEVICE


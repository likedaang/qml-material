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
    explicit UPowerConnection(QQuickItem *parent = 0) : QQuickItem(parent), iface("org.freedesktop.UPower", "/org/freedesktop/UPower", "org.freedesktop.UPower", QDBusConnection::systemBus()){
        QDBusConnection::systemBus().connect(iface.service(), iface.path(), iface.interface(), "DeviceAdded", this, SLOT(reloadDevices()));
        QDBusConnection::systemBus().connect(iface.service(), iface.path(), iface.interface(), "DeviceRemoved", this, SLOT(reloadDevices()));
        QDBusConnection::systemBus().connect(iface.service(), iface.path(), iface.interface(), "DeviceChanged", this, SLOT(reloadDevices()));

        reloadDevices();
    }
    QQmlListProperty<UPowerDevice> devices() {
        return QQmlListProperty<UPowerDevice>(this, deviceList);
    }
signals:
    void devicesChanged();

private slots:
   void reloadDevices(){
       qDebug() << "Devices changed!";

       QDBusMessage msg = iface.call("EnumerateDevices");
       const QDBusArgument &arg = msg.arguments().at(0).value<QDBusArgument>();
       deviceList.clear();

       arg.beginArray();
       while (!arg.atEnd()) {
           QDBusObjectPath path;
           arg >> path;
           UPowerDevice *device =  new UPowerDevice(path.path());
           deviceList << device;
       }
       arg.endArray();

       emit devicesChanged();
   }

private:
   QDBusInterface iface;
   QList<UPowerDevice*> deviceList;
};

#endif // UPOWERCONNECTION


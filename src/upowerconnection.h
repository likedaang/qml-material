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
        QDBusConnection::systemBus().connect(iface.service(), iface.path(), iface.interface(), "DeviceAdded", this, SLOT(notifyFromDBus()));
        QDBusConnection::systemBus().connect(iface.service(), iface.path(), iface.interface(), "DeviceRemoved", this, SLOT(notifyFromDBus()));
        QDBusConnection::systemBus().connect(iface.service(), iface.path(), iface.interface(), "DeviceChanged", this, SLOT(notifyFromDBus()));
        QDBusMessage msg = iface.call("EnumerateDevices");
        const QDBusArgument &arg = msg.arguments().at(0).value<QDBusArgument>();
        arg.beginArray();
        while (!arg.atEnd()) {
            QDBusObjectPath path;
            arg >> path;
            UPowerDevice *device =  new UPowerDevice(path.path());
            deviceList << device;
        }
        arg.endArray();
    }
    QQmlListProperty<UPowerDevice> devices() {
        return QQmlListProperty<UPowerDevice>(this, deviceList);
    }
signals:
    void devicesChanged();
private slots:
   void notifyFromDBus(){
       emit devicesChanged();
   }

private:
   QDBusInterface iface;
   QList<UPowerDevice*> deviceList;
};

#endif // UPOWERCONNECTION


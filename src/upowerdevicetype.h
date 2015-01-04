#ifndef UPOWERDEVICETYPE
#define UPOWERDEVICETYPE

#include <QObject>

class UPowerDeviceType : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
public:
    enum Type {
        Unknown = 0, LinePower, Battery, Ups, Monitor, Mouse, Keyboard, Pda, Phone
    };
};

#endif // UPOWERDEVICETYPE


#ifndef UPOWERDEVICESTATE
#define UPOWERDEVICESTATE

#include <QObject>

class UPowerDeviceState : public QObject {
    Q_OBJECT
    Q_ENUMS(State)
public:
    enum State {
        Unknown = 0, Charging, Discharging, Empty, FullyCharged, PendingCharge, PendingDischarge
    };
};

#endif // UPOWERDEVICESTATE


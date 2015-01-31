TEMPLATE = lib
TARGET = MaterialDesktop
QT += qml quick dbus
CONFIG += qt plugin c++11 link_pkgconfig
PKGCONFIG += glib-2.0

TARGET = $$qtLibraryTarget($$TARGET)
uri = Material.Desktop

INCLUDEPATH = src /usr/include/glib-2.0 /usr/lib/glib-2.0/include/
LIBS += -lpulse -lpulse-mainloop-glib

# Input
SOURCES += \
    src/qmldesktop_plugin.cpp \
    src/mpris/mprisconnection.cpp \
    src/mpris/mpris2player.cpp \
    src/upower/upowerconnection.cpp \
    src/upower/upowerdevice.cpp \
    src/notifications/notificationserver.cpp \
    src/mixer/sound.cpp \
    src/mixer/alsamixer.cpp \
    src/mixer/pulseaudiomixer.cpp \
    src/keyeventfilter/keyeventfilter.cpp \
    src/qquicklist/qobjectlistmodel.cpp \
    src/desktop/desktopfile.cpp \
    src/desktop/desktopscrobbler.cpp

HEADERS += \
    src/mpris/mprisconnection.h \
    src/mpris/mpris2player.h \
    src/qmldesktop_plugin.h \
    src/notifications/notification.h \
    src/notifications/notificationserver.h \
    src/notifications/notificationadaptor.h \
    src/upower/upowerconnection.h \
    src/upower/upowerdevice.h \
    src/upower/upowerdevicetype.h \
    src/upower/upowerdevicestate.h \
    src/mixer/sound.h \
    src/mixer/alsamixer.h \
    src/mixer/pulseaudiomixer.h \
    src/keyeventfilter/keyeventfilter.h \
    src/qquicklist/qobjectlistmodel.h \
    src/qquicklist/qquicklist.h \
    src/desktop/desktopfile.h \
    src/desktop/desktopscrobbler.h

OTHER_FILES = src/qmldir

qmldir.files = src/qmldir

installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
qmldir.path = $$installPath
target.path = $$installPath
INSTALLS += target qmldir

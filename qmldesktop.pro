TEMPLATE = lib
TARGET = MaterialDesktop
QT += qml quick dbus
CONFIG += qt plugin c++11

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

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/src/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = src/qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

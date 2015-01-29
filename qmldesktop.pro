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
    src/mprisconnection.cpp \
    src/mpris2player.cpp \
    src/upowerconnection.cpp \
    src/upowerdevice.cpp \
    src/notificationserver.cpp \
    src/mixer/sound.cpp \
    src/mixer/alsamixer.cpp \
    src/mixer/pulseaudiomixer.cpp \
    src/keyeventfilter.cpp

HEADERS += \
    src/mprisconnection.h \
    src/mpris2player.h \
    src/qmldesktop_plugin.h \
    src/notification.h \
    src/notificationserver.h \
    src/notificationadaptor.h \
    src/upowerconnection.h \
    src/upowerdevice.h \
    src/upowerdevicetype.h \
    src/upowerdevicestate.h \
    src/upowerdevice.cpp \
    src/notificationserver.cpp \
    src/mixer/sound.h \
    src/mixer/alsamixer.h \
    src/mixer/pulseaudiomixer.h \
    src/keyeventfilter.h

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

TEMPLATE = lib
TARGET = MaterialDesktop
QT += qml quick dbus
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = Material.Desktop

INCLUDEPATH = src

# Input
SOURCES += \
    src/qmldesktop_plugin.cpp \
    src/mprisconnection.cpp

HEADERS += \
    src/mprisconnection.h \
    src/mpris2player.h \
    src/qmldesktop_plugin.h \
    src/notification.h \
    src/notificationserver.h \
    src/notificationadaptor.h

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


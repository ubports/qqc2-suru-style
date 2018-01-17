TARGET = qtquickcontrols2surustyleplugin
TARGETPATH = QtQuick/Controls.2/Suru
IMPORT_VERSION = 2.2

uri = QtQuick.Controls.Suru

QT += qml quick
QT_PRIVATE += core-private gui-private qml-private quick-private quicktemplates2-private quickcontrols2-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

include(suru.pri)

OTHER_FILES += \
    qmldir \
    $$QML_FILES

SOURCES += \
    $$PWD/qtquickcontrols2surustyleplugin.cpp

RESOURCES += \
    $$PWD/qtquickcontrols2surustyleplugin.qrc

!static: CONFIG += qmlcache
CONFIG += no_cxx_module
load(qml_plugin)



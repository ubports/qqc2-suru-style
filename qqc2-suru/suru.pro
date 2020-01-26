TARGET = qtquickcontrols2surustyleplugin
TARGETPATH = QtQuick/Controls.2/Suru
IMPORT_VERSION = 2.2

uri = QtQuick.Controls.Suru

QT += gui qml quick
QT_PRIVATE += quickcontrols2-private quick-private quicktemplates2-private

DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII

include(suru.pri)

OTHER_FILES += \
    qmldir \
    $$QML_FILES

SOURCES += \
    $$PWD/qtquickcontrols2surustyleplugin.cpp

RESOURCES += \
    $$PWD/qtquickcontrols2surustyleplugin.qrc

# Qt 5.9 does not install *.qml files with the flags required for newer Qt versions
equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 12) {
    !static: CONFIG += qmlcache
    CONFIG += no_cxx_module
} else {
    CONFIG += no_cxx_module install_qml_files builtin_resources qtquickcompiler
}
load(qml_plugin)

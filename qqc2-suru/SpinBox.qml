/****************************************************************************
**
** Copyright (C) 2017, 2018 Stefano Verzegnassi <stefano@ubports.com>
** Copyright (C) 2017 The Qt Company Ltd.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
****************************************************************************/

import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.impl 2.3
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Suru 2.2

T.SpinBox {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + 16 +
                            (up.indicator ? up.indicator.implicitWidth : 0) +
                            (down.indicator ? down.indicator.implicitWidth : 0))
    implicitHeight: Math.max(contentItem.implicitHeight + topPadding + bottomPadding,
                             background ? background.implicitHeight : 0,
                             up.indicator ? up.indicator.implicitHeight : 0,
                             down.indicator ? down.indicator.implicitHeight : 0)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: control.Suru.units.gu(0.5)
    spacing: control.Suru.units.gu(1.5)
    leftPadding: padding + (control.mirrored ? (up.indicator ? up.indicator.width : 0) : (down.indicator ? down.indicator.width : 0))
    rightPadding: padding - 4 + (control.mirrored ? (down.indicator ? down.indicator.width : 0) : (up.indicator ? up.indicator.width : 0))

    validator: IntValidator {
        locale: control.locale.name
        bottom: Math.min(control.from, control.to)
        top: Math.max(control.from, control.to)
    }

    contentItem: TextInput {
        text: control.textFromValue(control.value, control.locale)

        font: control.font
        selectionColor: control.Suru.highlightColor
        selectedTextColor: "white"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: TextInput.AlignVCenter

        readOnly: !control.editable
        validator: control.validator
        inputMethodHints: control.inputMethodHints
    }

    up.indicator: Item {
        implicitWidth: control.Suru.units.gu(3)
        height: parent.height
        x: control.mirrored ? 0 : parent.width - width

        Rectangle {
            x: 2; y: 4
            width: parent.width - 4
            height: parent.height - 8
            color: control.activeFocus ? control.Suru.activeFocusColor :
                   control.up.pressed ? Qt.darker(control.Suru.backgroundColor, 1.2) :
                   control.up.hovered ? Qt.darker(control.Suru.backgroundColor, 1.1) : control.Suru.backgroundColor
            visible: control.up.pressed || control.up.hovered
            opacity: control.activeFocus && !control.up.pressed ? 0.5 : 1.0


            Behavior on color {
                ColorAnimation {
                    duration: control.Suru.animations.FastDuration  
                    easing: control.Suru.animations.EasingIn
                }
            }
        }

        ColorImage {
            anchors.centerIn: parent
            width: 16; height: width
            color: control.Suru.foregroundColor
            source: "qrc:/qt-project.org/imports/QtQuick/Controls.2/Suru/assets/" + (control.mirrored ? "left" : "right") + "arrow.png"
            sourceSize.width: width
            sourceSize.height: height
        }
    }

    down.indicator: Item {
        implicitWidth: control.Suru.units.gu(3)
        height: parent.height
        x: control.mirrored ? parent.width - width : 0

        Rectangle {
            x: 2; y: 4
            width: parent.width - 4
            height: parent.height - 8
            color: control.activeFocus ? control.Suru.activeFocusColor :
                   control.down.pressed ? Qt.darker(control.Suru.backgroundColor, 1.2) :
                   control.down.hovered ? Qt.darker(control.Suru.backgroundColor, 1.1) : control.Suru.backgroundColor
            visible: control.down.pressed || control.down.hovered
            opacity: control.activeFocus && !control.down.pressed ? 0.5 : 1.0

            Behavior on color {
                ColorAnimation {
                    duration: control.Suru.animations.FastDuration  
                    easing: control.Suru.animations.EasingIn
                }
            }
        }

        ColorImage {
            anchors.centerIn: parent
            width: control.Suru.units.gu(2); height: width
            color: control.Suru.foregroundColor
            source: "qrc:/qt-project.org/imports/QtQuick/Controls.2/Suru/assets/" + (control.mirrored ? "right" : "left") + "arrow.png"
            sourceSize.width: width
            sourceSize.height: height
        }
    }

    background: Rectangle {
        implicitWidth: control.Suru.units.gu(20)
        implicitHeight: control.Suru.units.gu(4)

        radius: control.Suru.units.dp(2)
        border.width: control.Suru.units.dp(1)

        border.color: control.activeFocus
                      ? control.Suru.highlightColor
                      : control.Suru.neutralColor

        color: control.hovered && !control.up.hovered && !control.down.hovered
               ? Qt.darker(control.Suru.backgroundColor, 1.1)
               : control.Suru.backgroundColor

        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration  
                easing: control.Suru.animations.EasingIn
            }
        }
    }
}

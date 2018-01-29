/****************************************************************************
**
** Copyright (C) 2017, 2018 Stefano Verzegnassi <stefano@ubports.com>
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
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Suru 2.2

Item {
    property Item control

    implicitWidth: control.Suru.units.gu(5)
    implicitHeight: control.Suru.units.gu(2.5)

    Rectangle {
        width: parent.width
        height: parent.height

        radius: control.Suru.units.dp(4)
        color: control.checked ? control.Suru.highlightColor : control.Suru.neutralColor

        border.width: control.Suru.units.dp(1)
        border.color: control.checked
                      ? Qt.darker(control.Suru.highlightColor, 1.1)
                      : Qt.darker(control.Suru.neutralColor, 1.1)

        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }

        Behavior on border.color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }
    }

    Row {
        width: parent.width
        height: parent.height

        Label {
            width: parent.width * 0.5
            height: parent.height
            text: "I"
            color: control.Suru.backgroundColor
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter
        }

        Label {
            width: parent.width * 0.5
            height: parent.height
            text: "O"
            color: Qt.darker(control.Suru.neutralColor, 1.5)
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter
        }
    }

    Rectangle {
        width: control.Suru.units.gu(2.5)
        height: control.Suru.units.gu(2.5)
        radius: control.Suru.units.dp(4)

        color: control.Suru.backgroundColor

        border.width: control.Suru.units.dp(1)
        border.color: control.Suru.secondaryBackgroundColor

        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: control.enabled ? 2 : 1
        }

        x: Math.max(0, Math.min(parent.width - width,
                                control.visualPosition * parent.width - (width / 2)))
        y: (parent.height - height) / 2

        Behavior on x {
            enabled: !control.pressed
            NumberAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingInOut
            }
        }
    }
}

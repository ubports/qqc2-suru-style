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
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Suru 2.2
import QtGraphicalEffects 1.0

T.Dial {
    id: control

    implicitWidth: control.Suru.units.gu(24)
    implicitHeight: control.Suru.units.gu(24)

    opacity: control.enabled ? 1.0 : 0.5

    background: Rectangle {
        x: control.width / 2 - width / 2
        y: control.height / 2 - height / 2

        width: Math.max(64, Math.min(control.width, control.height))
        height: width; radius: width / 2

        color: "transparent"
        border.color: control.Suru.neutralColor
        border.width: control.Suru.units.dp(3)

        // http://stackoverflow.com/questions/22873550/how-to-create-a-circular-progress-bar-in-pure-qmljs
        ConicalGradient {
            source: control.background
            anchors.fill: parent
            antialiasing: true

            // Get ConicalGradient starting from the right position
            angle: -140

            gradient: control.position == 1.0 ? pos100Gradient : stdGradient
            Gradient {
                id: stdGradient
                GradientStop { position: 0.00; color: control.Suru.highlightColor }
                GradientStop { position: control.position * 280 / 360; color: control.Suru.highlightColor }
                GradientStop { position: control.position * 280 / 360 + 0.0000000000001; color: "transparent" }
                GradientStop { position: 1.00 * 280 / 360; color: "transparent" }
            }

            Gradient {
                id: pos100Gradient
                GradientStop { position: 0.00; color: control.Suru.highlightColor }
                GradientStop { position: control.position * 280 / 360; color: control.Suru.highlightColor }
                GradientStop { position: control.position * 280 / 360 + 0.0000000000001; color: "transparent" }
                GradientStop { position: 1.00; color: "transparent" }
            }
        }
    }

    handle: Rectangle {
        implicitWidth: control.Suru.units.gu(2)
        implicitHeight: control.Suru.units.gu(2)
        radius: width * 0.5

        x: background.x + background.width / 2 - handle.width / 2
        y: background.y + background.height / 2 - handle.height / 2

        color: control.pressed ? control.Suru.highlightColor
                               : Qt.darker(control.Suru.neutralColor, control.hovered ? 1.1 : 1.0)

        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }

        transform: [
            Translate {
                y: -Math.min(background.width, background.height) * 0.4 + handle.height / 2
            },
            Rotation {
                angle: control.angle
                origin.x: handle.width / 2
                origin.y: handle.height / 2
            }
        ]

        Rectangle {
            anchors { fill: parent; margins: -4 }
            radius: width * 0.5
            visible: control.visualFocus
            border.width: control.Suru.units.dp(2)
            border.color: control.Suru.activeFocusColor
            color: "transparent"
        }
    }
}

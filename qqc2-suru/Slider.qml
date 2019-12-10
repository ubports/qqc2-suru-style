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

T.Slider {
    id: control

    readonly property bool horizontal: control.orientation === Qt.Horizontal

    implicitWidth: horizontal ? control.Suru.units.gu(32) : control.Suru.units.gu(5)
    implicitHeight: horizontal ? control.Suru.units.gu(5) : control.Suru.units.gu(32)

    padding: control.Suru.units.gu(1)
    opacity: control.enabled ? 1.0 : 0.5

    property bool useSystemFocusVisuals: true

    handle: Rectangle {
        implicitHeight: control.Suru.units.gu(2)
        implicitWidth: control.Suru.units.gu(2)

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        x: control.leftPadding + (horizontal ? control.visualPosition * (control.availableWidth - width) : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : control.visualPosition * (control.availableHeight - height))

        border.width: control.Suru.units.dp(1)
        border.color: control.Suru.neutralColor
        radius: control.Suru.units.dp(4)
        color: control.pressed
               ? Qt.darker(control.Suru.secondaryBackgroundColor, 1.1)
               : control.hovered ? control.Suru.secondaryBackgroundColor : control.Suru.backgroundColor
        opacity: control.enabled ? 1.0 : 0.5


        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }

        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: !control.pressed ? 2 : 3
        }
    }

    background: Item {
        implicitWidth: horizontal ? control.Suru.units.gu(5) : control.Suru.units.gu(2)
        implicitHeight: horizontal ? control.Suru.units.gu(2) : control.Suru.units.gu(5)

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        x: control.leftPadding + (horizontal ? 0 : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : 0)
        width: horizontal ? control.availableWidth : implicitWidth
        height: horizontal ? implicitHeight : control.availableHeight

        scale: horizontal && control.mirrored ? -1 : 1

        Rectangle {
            x: parent.horizontal ? 0 : (parent.width - width) / 2
            y: parent.horizontal ? (parent.height - height) / 2 : 0
            width: parent.horizontal ? parent.width : 2
            height: !parent.horizontal ? parent.height : 2

            color: control.Suru.neutralColor
        }

        Rectangle {
            x: parent.horizontal ? 0 : (parent.width - width) / 2
            y: parent.horizontal ? (parent.height - height) / 2 : control.visualPosition * parent.height
            width: parent.horizontal ? control.position * parent.width : 2
            height: !parent.horizontal ? control.position * parent.height : 2

            color: control.Suru.highlightColor
        }
    }
}

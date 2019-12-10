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

T.RangeSlider {
    id: control

    readonly property bool horizontal: control.orientation === Qt.Horizontal

    implicitWidth: horizontal ? control.Suru.units.gu(32) : control.Suru.units.gu(5)
    implicitHeight: horizontal ? control.Suru.units.gu(5) : control.Suru.units.gu(32)

    padding: control.Suru.units.gu(1)
    opacity: control.enabled ? 1.0 : 0.5

    first.handle: Rectangle {
        implicitHeight: control.Suru.units.gu(2)
        implicitWidth: control.Suru.units.gu(2)

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        x: control.leftPadding + (horizontal ? control.first.visualPosition * (control.availableWidth - width) : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : control.first.visualPosition * (control.availableHeight - height))

        border.width: activeFocus ? control.Suru.units.dp(2) : control.Suru.units.dp(1)   //(first.pressed ? 1 : 0)
        border.color: activeFocus ? control.Suru.activeFocusColor : control.Suru.neutralColor
        radius: control.Suru.units.dp(4)
        color: first.pressed
               ? Qt.darker(control.Suru.secondaryBackgroundColor, 1.1)
               : first.hovered ? control.Suru.secondaryBackgroundColor : control.Suru.backgroundColor

        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }

        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: !first.pressed ? 2 : 3
        }
    }

    second.handle: Rectangle {
        implicitHeight: control.Suru.units.gu(2)
        implicitWidth: control.Suru.units.gu(2)

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        x: control.leftPadding + (horizontal ? control.second.visualPosition * (control.availableWidth - width) : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : control.second.visualPosition * (control.availableHeight - height))

        border.width: activeFocus ? control.Suru.units.dp(2) : control.Suru.units.dp(1)       //(second.pressed ? 1 : 0)
        border.color: activeFocus ? control.Suru.activeFocusColor : control.Suru.neutralColor
        radius: control.Suru.units.dp(4)
        color: second.pressed
               ? Qt.darker(control.Suru.secondaryBackgroundColor, 1.1)
               : second.hovered ? control.Suru.secondaryBackgroundColor : control.Suru.backgroundColor


        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }

        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: !second.pressed ? 2 : 3
        }
    }

    background: Item {
        implicitWidth: horizontal ? control.Suru.units.gu(48) : control.Suru.units.gu(2)
        implicitHeight: horizontal ? control.Suru.units.gu(2) : control.Suru.units.gu(48)

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        x: control.leftPadding + (horizontal ? 0 : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : 0)
        width: horizontal ? control.availableWidth : implicitWidth
        height: horizontal ? implicitHeight : control.availableHeight

        scale: horizontal && control.mirrored ? -1 : 1

        Rectangle {
            x: parent.horizontal ? 0 : (parent.width - width) / 2
            y: parent.horizontal ? (parent.height - height) / 2 : 0
            width: parent.horizontal ? parent.width : control.Suru.units.dp(3)
            height: !parent.horizontal ? parent.height : control.Suru.units.dp(3)

            color: control.Suru.neutralColor
        }

        Rectangle {
            x: parent.horizontal ? control.first.position * parent.width : (parent.width - width) / 2
            y: parent.horizontal ? (parent.height - height) / 2 : control.second.visualPosition * parent.height
            width: parent.horizontal ? control.second.position * parent.width - control.first.position * parent.width : control.Suru.units.dp(3)
            height: !parent.horizontal ? control.second.position * parent.height - control.first.position * parent.height : control.Suru.units.dp(3)

            color: control.Suru.highlightColor
        }
    }
}

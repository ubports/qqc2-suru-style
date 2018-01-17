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

    implicitWidth: horizontal ? 256 : 40
    implicitHeight: horizontal ? 40 : 256

    padding: 8
    opacity: control.enabled ? 1.0 : 0.5

    first.handle: Rectangle {
        implicitHeight: 16
        implicitWidth: 16

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        x: control.leftPadding + (horizontal ? control.first.visualPosition * (control.availableWidth - width) : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : control.first.visualPosition * (control.availableHeight - height))

        border.width: first.pressed ? 1 : 0
        border.color: control.Suru.neutralColor
        radius: 4
        color: first.pressed
               ? Qt.darker(control.Suru.secondaryBackgroundColor, 1.1)
               : first.hovered ? control.Suru.secondaryBackgroundColor : control.Suru.backgroundColor

        layer.enabled: !first.pressed
        layer.effect: ElevationEffect {
            elevation: 1
        }
    }

    second.handle: Rectangle {
        implicitHeight: 16
        implicitWidth: 16

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        x: control.leftPadding + (horizontal ? control.second.visualPosition * (control.availableWidth - width) : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : control.second.visualPosition * (control.availableHeight - height))

        border.width: second.pressed ? 1 : 0
        border.color: control.Suru.neutralColor
        radius: 4
        color: second.pressed
               ? Qt.darker(control.Suru.secondaryBackgroundColor, 1.1)
               : second.hovered ? control.Suru.secondaryBackgroundColor : control.Suru.backgroundColor

        layer.enabled: !second.pressed
        layer.effect: ElevationEffect {
            elevation: 1
        }
    }

    background: Item {
        implicitWidth: horizontal ? 400 : 16
        implicitHeight: horizontal ? 16 : 400

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
            x: parent.horizontal ? control.first.position * parent.width : (parent.width - width) / 2
            y: parent.horizontal ? (parent.height - height) / 2 : control.second.visualPosition * parent.height
            width: parent.horizontal ? control.second.position * parent.width - control.first.position * parent.width : 2
            height: !parent.horizontal ? control.second.position * parent.height - control.first.position * parent.height : 2

            color: control.Suru.accentColor
        }
    }
}

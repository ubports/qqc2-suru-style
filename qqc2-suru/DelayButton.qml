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

T.DelayButton {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    leftPadding: control.Suru.units.gu(2)
    rightPadding: control.Suru.units.gu(2)
    topPadding: control.Suru.units.gu(1)
    bottomPadding: control.Suru.units.gu(1)

    property bool useSystemFocusVisuals: true

    opacity: control.enabled ? 1.0 : 0.5

    transition: Transition {
        NumberAnimation {
            duration: control.delay * (control.pressed ? 1.0 - control.progress : 0.3 * control.progress)
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: control.checked ? control.Suru.backgroundColor : control.Suru.foregroundColor

        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }
    }

    background: Rectangle {
        id: controlBg
        implicitWidth: control.Suru.units.gu(8)
        implicitHeight: control.Suru.units.gu(4)

        property color __normalColor: control.checked ? control.Suru.highlightColor : control.Suru.secondaryBackgroundColor

        color: control.down ? Qt.darker(__normalColor, 1.2)
                            : control.hovered ? Qt.darker(__normalColor, 1.1) : __normalColor
        radius: control.Suru.units.dp(4)
        border.width: control.checked ? 0 : 1
        border.color: control.Suru.neutralColor

        Item {
            width: parent.width * control.progress
            height: control.Suru.units.dp(3)
            anchors.bottom: parent.bottom

            clip: true
            Rectangle {
                visible: !control.checked
                width: parent.width + (control.progress == 1.0 ? 0 : controlBg.radius)
                height: parent.height + controlBg.radius
                radius: controlBg.radius
                color: control.Suru.highlightColor
                anchors.bottom: parent.bottom
            }
        }

        Behavior on color {
            ColorAnimation {
                duration: control.Suru.animations.FastDuration
                easing: control.Suru.animations.EasingIn
            }
        }
    }
}

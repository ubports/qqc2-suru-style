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

T.ScrollBar {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)

    visible: control.policy !== T.ScrollBar.AlwaysOff

    // TODO: arrows

    contentItem: Rectangle {
        implicitWidth: control.interactive ? control.Suru.units.gu(2) : control.Suru.units.dp(3)
        implicitHeight: control.interactive ? control.Suru.units.gu(2) : control.Suru.units.dp(3)

        color: control.pressed ? Qt.darker(control.Suru.highlightColor, 1.2) :
               control.interactive && control.hovered ? Qt.darker(control.Suru.highlightColor, 1.1) : control.Suru.highlightColor
        opacity: 0.0
        radius: control.Suru.units.dp(2)
    }

    background: Rectangle {
        implicitWidth: control.interactive ? control.Suru.units.gu(2) : 0

        color: control.Suru.neutralColor
        visible: control.size < 1.0
        opacity: 0.0
    }

    states: [
        State {
            name: "active"
            when: control.policy === T.ScrollBar.AlwaysOn || (control.active && control.size < 1.0)
        }
    ]

    transitions: [
        Transition {
            to: "active"
            ParallelAnimation {
                NumberAnimation { targets: contentItem; property: "opacity"; to: 1.0; duration: control.Suru.animations.BriskDuration; easing: control.Suru.animations.EasingIn }
                NumberAnimation { targets: background; property: "opacity"; to: .5; duration: control.Suru.animations.BriskDuration; easing: control.Suru.animations.EasingIn }
            }
        },
        Transition {
            from: "active"
            SequentialAnimation {
                PauseAnimation { duration: 3000 }
                NumberAnimation { targets: [contentItem, background]; property: "opacity"; to: 0.0; duration: control.Suru.animations.BriskDuration; easing: control.Suru.animations.EasingIn }
            }
        }
    ]
}

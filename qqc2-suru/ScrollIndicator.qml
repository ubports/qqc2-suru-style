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

T.ScrollIndicator {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)

    contentItem: Rectangle {
        id: indicator

        implicitWidth: control.Suru.units.dp(3)
        implicitHeight: control.Suru.units.dp(3)

        color: control.Suru.highlightColor
        visible: control.size < 1.0
        opacity: 0.0

        states: [
            State {
                name: "active"
                when: control.active
            }
        ]

        transitions: [
            Transition {
                to: "active"
                NumberAnimation { target: indicator; property: "opacity"; to: 1.0; duration: control.Suru.animations.BriskDuration; easing: control.Suru.animations.EasingIn }
            },
            Transition {
                from: "active"
                SequentialAnimation {
                    PauseAnimation { duration: 3000 }
                    NumberAnimation { target: indicator; property: "opacity"; to: 0.0; duration: control.Suru.animations.BriskDuration; easing: control.Suru.animations.EasingIn }
                }
            }
        ]
    }
}

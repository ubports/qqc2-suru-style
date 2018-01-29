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

T.SwipeDelegate {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    topPadding: control.Suru.units.gu(2) - control.Suru.units.dp(1)
    bottomPadding: control.Suru.units.gu(2) + control.Suru.units.dp(1)
    leftPadding: control.Suru.units.gu(2)
    rightPadding: control.Suru.units.gu(2)

    spacing: control.Suru.units.spacingLarge

    opacity: control.enabled ? 1.0 : 0.5

    swipe.transition: Transition { SmoothedAnimation { velocity: 3; easing: control.Suru.animations.EasingInOut } }

    contentItem: Text {
        leftPadding: !control.mirrored ? (control.indicator ? control.indicator.width + control.spacing : 0) : 0
        rightPadding: control.mirrored ? (control.indicator ? control.indicator.width + control.spacing : 0) : 0

        text: control.text
        font: control.font
        color: control.Suru.foregroundColor

        elide: Text.ElideRight
        visible: control.text
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitHeight: control.Suru.units.gu(7)
        color: control.Suru.backgroundColor

        HighlightFocusRectangle {
            control: control
            width: parent.width
            height: parent.height
        }

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: control.Suru.units.dp(1)
            color: control.Suru.neutralColor
        }
    }
}

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
import QtQuick.Templates 2.5 as T
import QtQuick.Controls.Suru 2.5
import "impl"

T.Drawer {
    id: control

    parent: T.ApplicationWindow.overlay

    implicitWidth: Math.max(background ? background.implicitWidth : 0, contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0, contentHeight + topPadding + bottomPadding)

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    topPadding: control.edge === Qt.BottomEdge
    leftPadding: control.edge === Qt.RightEdge
    rightPadding: control.edge === Qt.LeftEdge
    bottomPadding: control.edge === Qt.TopEdge

    enter: Transition { NumberAnimation { duration: control.Suru.animations.BriskDuration; easing: control.Suru.animations.EasingInOut } }
    exit: Transition { NumberAnimation { duration: control.Suru.animations.BriskDuration; easing: control.Suru.animations.EasingInOut } }

    background: Rectangle {
        color: control.Suru.secondaryBackgroundColor
        Rectangle {
            readonly property bool horizontal: control.edge === Qt.LeftEdge || control.edge === Qt.RightEdge
            x: control.edge === Qt.LeftEdge ? parent.width - control.Suru.units.dp(1) : 0
            y: control.edge === Qt.TopEdge ? parent.height - control.Suru.units.dp(1) : 0
            width: horizontal ? control.Suru.units.dp(1) : parent.width
            height: horizontal ? parent.height : control.Suru.units.dp(1)

            color: control.Suru.neutralColor
        }

        layer.enabled: control.position > 0
        layer.effect: ElevationEffect {
            elevation: !interactive && !dim ? 0 : 3
        }
    }
}

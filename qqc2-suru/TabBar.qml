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

T.TabBar {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentHeight + topPadding + bottomPadding)

    spacing: 1
    contentHeight: control.Suru.units.gu(6)

    contentItem: ListView {
        model: control.contentModel
        currentIndex: control.currentIndex

        spacing: control.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        snapMode: ListView.SnapToItem

        highlightMoveDuration: control.Suru.animations.BriskDuration
        highlightResizeDuration: 0
        highlightFollowsCurrentItem: true
        highlightRangeMode: ListView.ApplyRange
        preferredHighlightBegin: control.Suru.units.gu(6)
        preferredHighlightEnd: width - control.Suru.units.gu(6)

        highlight: Item {
            z: 2
            Rectangle {
                height: control.Suru.units.dp(3)
                width: parent.width
                y: control.position === T.TabBar.Footer ? 0 : parent.height - height
                color: control.Suru.highlightColor
            }
        }
    }

    background: Rectangle {
        color: control.Suru.secondaryBackgroundColor

        Rectangle {
            height: 1
            width: parent.width
            y: control.position === T.TabBar.Footer ? 0 : parent.height - height
            color: control.Suru.neutralColor
        }
    }
}
